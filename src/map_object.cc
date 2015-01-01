#include "common.h"
#include "map_object.h"
#include "sprites.h"
#include "episode_map.h"
#include "game.h"

#include "debug.h"

#define GRAVITY_PER_TICK 10 // FIXME: make this accelerate, like real gravity

map_object::map_object(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn)
{
  defn     = _defn;
  health   = defn->spawn_health;
  velocity = 0; // FIXME: unused?

  change_to_meta_state(META_STATE_NORMAL);

  _camera.set_map_position(_map_position);
  _camera.set_facing_angle(_facing_angle);

  floor_height = 0;  // floor height (absolute)
  foot_height  = 0;  // foot height (absolute)
  _camera.set_view_height(foot_height + defn->height);
}

map_object::~map_object()
{
}

void map_object::tick(game *_game, episode_map *_map)
{
  // animate
  if(cur_state && (cur_state->num_ticks > 0))
  {
    cur_tick_count++;
    if(cur_tick_count >= cur_state->num_ticks)
    {
      cur_tick_count = 0;
      map_obj_meta_state_id new_meta_state_id;
      map_obj_state const *new_state;
      if(lookup_next_state(cur_state->next_state_id, &new_meta_state_id, &new_state))
      {
        cur_meta_state_id = new_meta_state_id;
        cur_state         = new_state;
        cur_state_id      = cur_state->cur_state_id;
      }
      else
      {
        cur_state = NULL;
      }
    }
  }

  // apply gravity
  floor_height = _map->get_floor_height_at(_camera.get_map_position()); 
  if(foot_height < floor_height)
  {
    foot_height = floor_height;
    _camera.set_view_height(foot_height + defn->height);
  }
  if((foot_height > floor_height) && !(defn->flags & MF_NOGRAVITY))
  {
    foot_height = MAX(foot_height - GRAVITY_PER_TICK, floor_height);
    _camera.set_view_height(foot_height + defn->height);
  }
}

void map_object::change_to_meta_state(map_obj_meta_state_id new_meta_state_id)
{
  cur_meta_state_id = new_meta_state_id;

  map_obj_state const *states;
  switch(cur_meta_state_id)
  {
    case META_STATE_NORMAL:  states = defn->normal_states;  break;
    case META_STATE_SEE:     states = defn->see_states;     break;
    case META_STATE_PAIN:    states = defn->pain_states;    break;
    case META_STATE_MELEE:   states = defn->melee_states;   break;
    case META_STATE_MISSILE: states = defn->missile_states; break;
    case META_STATE_DEATH:   states = defn->death_states;   break;
    case META_STATE_XDEATH:  states = defn->xdeath_states;  break;
    case META_STATE_RAISE:   states = defn->raise_states;   break;
    default: printf("ERROR: unknown metastate\n"); exit(0);
  }
  if(states)
  {
    cur_state = &states[0];
    if(cur_state->is_valid)
    {
      cur_state_id   = cur_state->cur_state_id;
      cur_tick_count = 0;
      cur_animation  = sprites_lookup_animation(cur_state->sprite_prefix);
    }
  }
  else
  {
    cur_state = NULL; 
  }
}

bool map_object::lookup_next_state(map_obj_state_id next_state_id, map_obj_meta_state_id *new_meta_state_id, map_obj_state const **new_state) const
{
  map_obj_state const *states;

  for(states=defn->normal_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_NORMAL; *new_state = states; return true;
    }
  }

  for(states=defn->see_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_SEE; *new_state = states; return true;
    }
  }

  for(states=defn->pain_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_PAIN; *new_state = states; return true;
    }
  }

  for(states=defn->melee_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_MELEE; *new_state = states; return true;
    }
  }

  for(states=defn->missile_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_MISSILE; *new_state = states; return true;
    }
  }

  for(states=defn->death_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_DEATH; *new_state = states; return true;
    }
  }

  for(states=defn->xdeath_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_XDEATH; *new_state = states; return true;
    }
  }

  for(states=defn->raise_states; states && states->is_valid; states++)
  {
    if(states->cur_state_id == next_state_id)
    {
      *new_meta_state_id =  META_STATE_RAISE; *new_state = states; return true;
    }
  }

  return false;
}

sector const *map_object::get_sector(void) const
{
  return _subsector->get_sector();
}

void map_object::render_player_view(camera const *view_camera, clipped_segment_projections *clipped_seg_projs) const
{
  if(!cur_state) { return; } 
  map_object_projection *proj;

  proj = project(view_camera);
  if(!proj)
  {
    return;
  }

  proj->clip(clipped_seg_projs);
  proj->draw();
  delete proj;
}

map_object_projection *map_object::project(camera const *view_camera) const
{
  map_object_projection *proj = new map_object_projection;

  // figure out sprite rotation angle
  proj->sprite_angle = get_rotation_angle(view_camera) ;
  int sprite_angle_idx = round(proj->sprite_angle / DEG_TO_RAD(45.0));
  sprite_angle_idx = (sprite_angle_idx+8+8)%8;
  proj->is_flipped = false;

  // figure out which sprite to use
  if(!cur_animation) { /*printf("WARNING: map_object (\"%s\") has no animation\n", defn->description);*/ return NULL; }
  if(cur_animation->get_num_frames()==0) { printf("WARNING: map_object has sprite animation with no frames\n"); return NULL; }
  uint8_t cur_frame_idx = cur_state->sprite_frame;
  sprite_animation_frame const *cur_frame = ((sprite_animation *)cur_animation)->get_frame(cur_frame_idx);
  if(!cur_frame) { printf("WARNING: map_object has no current frame\n"); return NULL; }

  debug_printf("    sprite angle: %.1f, idx: %d, # angles: %d\n", 
               RAD_TO_DEG(proj->sprite_angle), sprite_angle_idx, cur_frame->get_num_angles());
  int adj_sprite_angle_idx;
  switch(cur_frame->get_num_angles())
  {
    case 1:  adj_sprite_angle_idx = 0;                     break;
    case 8:  adj_sprite_angle_idx = sprite_angle_idx;      break;
    case 9:  adj_sprite_angle_idx = sprite_angle_idx + 1;  break;
    default: adj_sprite_angle_idx = sprite_angle_idx;
             printf("WARNING: map obj has %d frames\n", cur_frame->get_num_angles()); 
  }

  if(cur_frame->get_num_angles() > adj_sprite_angle_idx)
  {
    proj->_sprite = cur_frame->get_sprite(adj_sprite_angle_idx);
    if(proj->_sprite &&
       (proj->_sprite->get_num_orientations() > 1))
    {
      if(adj_sprite_angle_idx == proj->_sprite->get_rotation_idx(0))
      {
        debug_printf("      cur ang: %d. Sprite rots: [%d], %d\n", 
                     adj_sprite_angle_idx, proj->_sprite->get_rotation_idx(0), proj->_sprite->get_rotation_idx(1));
      }
      else if(adj_sprite_angle_idx == proj->_sprite->get_rotation_idx(1))
      {
        debug_printf("      cur ang: %d. Sprite rots: %d, [%d] (FLIPPED)\n", 
                     adj_sprite_angle_idx, proj->_sprite->get_rotation_idx(0), proj->_sprite->get_rotation_idx(1));
        proj->is_flipped = true;
      }
      else
      {
        debug_printf("      cur ang: %d. Sprite rots: %d, %d. MATCHES NEITHER!!!\n", 
                     adj_sprite_angle_idx, proj->_sprite->get_rotation_idx(0), proj->_sprite->get_rotation_idx(1));
      }
    }
  }
  else
  {
    proj->_sprite = cur_frame->get_sprite(0);
  }
  if(!proj->_sprite)
  {
    printf("WARNING: map_object has no sprite\n");
    printf("    sprite angle: %.1f deg\n", RAD_TO_DEG(proj->sprite_angle));
    printf("    idx: %d\n", sprite_angle_idx);
    printf("    frame idx: %d\n", cur_frame_idx);
    printf("    num frames: %d\n", cur_frame->get_num_angles());
    delete proj;
    return NULL;
  }

  // set lighting
  proj->sector_light_level = get_sector()->get_light_level();

  // project horizontally
  float angle_c = NORMALIZE_ANGLE(view_camera->get_map_position()->angle_to_point(_camera.get_map_position()) - view_camera->get_facing_angle());
  float dist_c  = view_camera->get_map_position()->distance_to_point(_camera.get_map_position());
  float angle_delta = atan2(proj->_sprite->get_width()/2.0, dist_c);
  proj->angle_l = angle_c + angle_delta;
  proj->angle_r = angle_c - angle_delta;
  proj->horiz_fov_radius = _projector->get_horiz_fov_radius();
  proj->dist_l = dist_c; // FIXME: do some trig here. this is an approximation
  proj->dist_r = dist_c; // FIXME: do some trig here. this is an approximation
  if(proj->is_backface())    { delete proj; return NULL; }
  if(proj->is_outside_fov()) { delete proj; return NULL; }
  debug_printf("  rendering map obj\n");
  debug_printf("    angles: [%1.f, %.1f, %.1f] dist: %.1f\n", 
              RAD_TO_DEG(proj->angle_l), RAD_TO_DEG(proj->angle_c), RAD_TO_DEG(proj->angle_r), dist_c);
  proj->x_l = _projector->project_horiz_angle_to_x(proj->angle_l);
  proj->x_r = _projector->project_horiz_angle_to_x(proj->angle_r);

  // project vertically
  float y0, dy;
  float rel_height = view_camera->get_view_height() - get_sector()->get_floor_height(); // FIXME: assumes it sits on floor
  _projector->project_z_to_y(-rel_height, dist_c, &y0, &dy);
  float h = (proj->x_r - proj->x_l) * proj->_sprite->get_height() / proj->_sprite->get_width();
  proj->y_t = y0-h;
  proj->y_b = y0;
  proj->z_t = get_sector()->get_floor_height() + h;
  proj->z_b = get_sector()->get_floor_height();
  debug_printf("    x:[%.1f,%.1f], h:%.1f, y0:%.1f, dy:%.1f, y:[%.1f,%.1f]\n", proj->x_l, proj->x_r, h, y0, dy, proj->y_t, proj->y_b);
  debug_printf("    aspect ratio: %.3f\n", (proj->x_r - proj->x_l)/(proj->y_b - proj->y_t));

  return proj;
}

float map_object::get_rotation_angle(camera const *view_camera) const
{
  float rot_angle = DEG_TO_RAD(180) 
                  + view_camera->get_map_position()->angle_to_point(_camera.get_map_position())
                  - _camera.get_facing_angle()
                  + 0.001;
  while(rot_angle <       0.0) { rot_angle += 2.0*M_PI; }
  while(rot_angle >= 2.0*M_PI) { rot_angle -= 2.0*M_PI; }
  return rot_angle;
}

bool map_object::overlaps(map_object const *obj) const
{
  float ctr_to_ctr_dist = _camera.get_map_position()->distance_to_point(obj->get_camera()->get_map_position());
  float sum_of_radii    = defn->radius + obj->get_defn()->radius;
  return (ctr_to_ctr_dist <= sum_of_radii);
}

/******************************************************************************
 * TESTS
 ******************************************************************************/

#if 0
class simple_map_object : public map_object
{
public:
  simple_map_object(int _map_object_type, vertex const *v, float _facing_angle)
  {
    frame_ctr = 0;
    map_position.set_to(v);
    facing_angle = _facing_angle;
    map_object_type   = _map_object_type;
    _is_deaf     = false;
    defn         = map_object_definition_lookup(map_object_type);
    animation    = sprites_lookup_animation(defn->sprite_prefix);
  }
};

/*                
 *    T→ ←C
 *
 * C->T: 180  C: -180  T: 0
 * A: 0
 */
void map_object_project_head_on_bkwd_facing_toward_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(180));

  // map_object at (-1,0), facing straight back
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(-100,0);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(0));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 179, 181);

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  if(RAD_TO_DEG(ang) > 350)
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 359, 361);
  }
  else
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), -1, 1);
  }
}

/*                
 *    C→ ←T
 *
 * C->T: 0  C: 0  T: 180 
 * A: 0
 */
void map_object_project_head_on_facing_toward_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // map_object at (1,0), facing straight back
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(180));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  if(RAD_TO_DEG(view_ang) > 350)
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 359, 361);
  }
  else
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -1, 1);
  }

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  if(RAD_TO_DEG(ang) > 350)
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 359, 361);
  }
  else
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), -1, 1);
  }
}

/*                
 *    C→ T→
 *
 * C->T: 0  C: 0  T: 0
 * A: 180
 */
void map_object_project_head_on_facing_away_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // map_object at (1,0), facing straight back
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(0));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  if(RAD_TO_DEG(view_ang) > 350)
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 359, 361);
  }
  else
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -1, 1);
  }

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 179, 181);
}

/*                
 *        ↑
 *    C→  T
 *
 * C->T: 0  C: 0  T: 90
 * A: 90
 */
void map_object_project_head_on_facing_left_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // map_object at (1,0), facing straight up
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(90));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  if(RAD_TO_DEG(view_ang) > 350)
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 359, 361);
  }
  else
  {
    TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -1, 1);
  }

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang) , 89, 91);
}

/*                
 *       ←T
 *       
 *    C→
 *
 * C->T: 45  C: 0  T: -180 
 * A: 45
 */
void map_object_project_at_45_facing_180(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // map_object at (1,1), facing straight back
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,100);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(180));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 44, 46);

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 44, 46);
}

/*                
 *    C→
 *       
 *       ←T
 *
 * C->T: -45  C: 0  T: -180 
 * A: 315 == 360-45
 */
void map_object_project_at_neg45_facing_180(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // map_object at (1,-1), facing straight back
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,-100);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(180));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -46, -44);

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 314, 316);  //360-45
}

/*                
 *        T
 *    ↑   ↓
 *    C
 *
 * C->T: 45  C: 90  T: -90 
 * A: 315 == 360-45
 */
void map_object_project_facing_up_map_object_at_45_facing_down(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(90));

  // map_object  at (1,1), facing down
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,100);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(270));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 44, 46);

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 314, 316); // 360-45
}

/*                
 *        C
 *        ↓
 *    T
 *    ↓
 *
 * C->T: -135  C: -90  T: -90 
 * A: 135
 */
void map_object_project_facing_down_map_object_at_neg_135_facing_down(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(270));

  // map_object  at (-1,-1), facing down
  int map_object_type = 3002; // demon (has 8 rotations)
  vertex t_pos(-100,-100);
  simple_map_object s(map_object_type, &t_pos, DEG_TO_RAD(270));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -136, -134);

  // project the map_object
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 134, 136);
}
#endif

void map_object_tests(void)
{
#if 0
  map_object_project_head_on_facing_toward_test();
  map_object_project_head_on_facing_away_test();
  map_object_project_head_on_bkwd_facing_toward_test();
  map_object_project_head_on_facing_left_test();
  map_object_project_at_45_facing_180();
  map_object_project_at_neg45_facing_180();
  map_object_project_facing_up_map_object_at_45_facing_down();
  map_object_project_facing_down_map_object_at_neg_135_facing_down();
#endif
}
