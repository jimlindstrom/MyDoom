#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing.h"
#include "thing_definitions.h"
#include "subsector.h"
#include "palettes.h"
#include "games.h"
#include "frame_buf.h"
#include "tests.h"

//#define DEBUG_PRINTING
#include "debug.h"

thing::thing(thing_instance const *instance)
{
  frame_ctr = 0;

  map_position.set_to(instance->get_map_position());
  facing_angle = instance->get_facing_angle();
  thing_type   = instance->get_thing_type();
  _is_deaf     = instance->is_deaf();

  defn         = thing_definition_lookup(thing_type);
  animation    = sprites_lookup_animation(defn->sprite_prefix);
}

thing::~thing()
{
}

sector const *thing::get_sector(void) const { return _subsector->get_sector(); }

uint8_t thing::get_frame_idx(void) const
{
  uint8_t num_frame_letters = strlen(defn->sequence);
  uint8_t frame_letter_idx = (games_get_frame_counter()>>2) % num_frame_letters;
  uint8_t num_attempts = 0;
  char frame_letter;
  while((frame_letter = defn->sequence[frame_letter_idx]) == '+')
  {
    frame_letter_idx = (frame_letter_idx+1) % num_frame_letters;
    if((num_attempts++) > num_frame_letters)
    {
      debug_printf("    WARNING: couldn't find valid frame index for thing\n");
      return 0;
    }
  }
  return frame_letter-'A';
}

void thing::render_player_view(camera const *_camera, clipped_segment_projections *clipped_seg_projs) const
{
  thing_projection *proj;

  proj = project(_camera);
  if(!proj)
  {
    return;
  }

  proj->clip(clipped_seg_projs);
  proj->draw();
  delete proj;
}

thing_projection *thing::project(camera const *_camera) const
{
  thing_projection *proj = new thing_projection;

  // figure out sprite rotation angle
  proj->sprite_angle = get_rotation_angle(_camera) ;
  int sprite_angle_idx = round(proj->sprite_angle / DEG_TO_RAD(45.0));
  sprite_angle_idx = (sprite_angle_idx+8+8)%8;
  proj->is_flipped = false;

  // figure out which sprite to use
  if(!animation) { /*printf("WARNING: thing (\"%s\") has no animation\n", defn->description);*/ return NULL; }
  if(animation->get_num_frames()==0) { printf("WARNING: thing (\"%s\") has sprite animation with no frames\n", defn->description); return NULL; }
  uint8_t cur_frame_idx = get_frame_idx();
  sprite_animation_frame const *cur_frame = animation->get_frame(cur_frame_idx);
  if(!cur_frame) { printf("WARNING: thing (\"%s\") has no current frame\n", defn->description); return NULL; }

  debug_printf("    sprite \"%s\" angle: %.1f, idx: %d, # angles: %d\n", 
               defn->description, RAD_TO_DEG(proj->sprite_angle), sprite_angle_idx, cur_frame->get_num_angles());
  int adj_sprite_angle_idx;
  switch(cur_frame->get_num_angles())
  {
    case 1:  adj_sprite_angle_idx = 0;                     break;
    case 8:  adj_sprite_angle_idx = sprite_angle_idx;      break;
    case 9:  adj_sprite_angle_idx = sprite_angle_idx + 1;  break;
    default: adj_sprite_angle_idx = sprite_angle_idx;
             printf("WARNING: \"%s\" has %d frames\n", defn->description, cur_frame->get_num_angles()); 
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
    printf("WARNING: thing (\"%s\") has no sprite\n", defn->description);
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
  float angle_c = NORMALIZE_ANGLE(_camera->get_map_position()->angle_to_point(&map_position) - _camera->get_facing_angle());
  float dist_c  = _camera->get_map_position()->distance_to_point(&map_position);
  float angle_delta = atan2(proj->_sprite->get_width()/2.0, dist_c);
  proj->angle_l = angle_c + angle_delta;
  proj->angle_r = angle_c - angle_delta;
  proj->horiz_fov_radius = _projector->get_horiz_fov_radius();
  proj->dist_l = dist_c; // FIXME: do some trig here. this is an approximation
  proj->dist_r = dist_c; // FIXME: do some trig here. this is an approximation
  if(proj->is_backface())    { delete proj; return NULL; }
  if(proj->is_outside_fov()) { delete proj; return NULL; }
  debug_printf("  rendering \"%s\"\n", defn->description);
  debug_printf("    angles: [%1.f, %.1f, %.1f] dist: %.1f\n", 
              RAD_TO_DEG(proj->angle_l), RAD_TO_DEG(proj->angle_c), RAD_TO_DEG(proj->angle_r), dist_c);
  proj->x_l = _projector->project_horiz_angle_to_x(proj->angle_l);
  proj->x_r = _projector->project_horiz_angle_to_x(proj->angle_r);

  // project vertically
  float y0, dy;
  float rel_height = _camera->get_view_height() - get_sector()->get_floor_height(); // FIXME: assumes it sits on floor
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

float thing::get_rotation_angle(camera const *_camera) const
{
  float rot_angle = DEG_TO_RAD(180) 
                  + _camera->get_map_position()->angle_to_point(&map_position)
                  - facing_angle
                  + 0.001;
  while(rot_angle <       0.0) { rot_angle += 2.0*M_PI; }
  while(rot_angle >= 2.0*M_PI) { rot_angle -= 2.0*M_PI; }
  return rot_angle;
}

void thing::tick(void)
{
}

/******************************************************************************
 * TESTS
 ******************************************************************************/

class simple_thing : public thing
{
public:
  simple_thing(int _thing_type, vertex const *v, float _facing_angle)
  {
    frame_ctr = 0;
    map_position.set_to(v);
    facing_angle = _facing_angle;
    thing_type   = _thing_type;
    _is_deaf     = false;
    defn         = thing_definition_lookup(thing_type);
    animation    = sprites_lookup_animation(defn->sprite_prefix);
  }
};

/*                
 *    T→ ←C
 *
 * C->T: 180  C: -180  T: 0
 * A: 0
 */
void thing_project_head_on_bkwd_facing_toward_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(180));

  // thing at (-1,0), facing straight back
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(-100,0);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(0));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 179, 181);

  // project the thing
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
void thing_project_head_on_facing_toward_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // thing at (1,0), facing straight back
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(180));

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

  // project the thing
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
void thing_project_head_on_facing_away_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // thing at (1,0), facing straight back
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(0));

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

  // project the thing
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
void thing_project_head_on_facing_left_test(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // thing at (1,0), facing straight up
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,0);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(90));

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

  // project the thing
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
void thing_project_at_45_facing_180(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // thing at (1,1), facing straight back
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,100);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(180));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 44, 46);

  // project the thing
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
void thing_project_at_neg45_facing_180(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(0);

  // thing at (1,-1), facing straight back
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,-100);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(180));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -46, -44);

  // project the thing
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
void thing_project_facing_up_thing_at_45_facing_down(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(90));

  // thing  at (1,1), facing down
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(100,100);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(270));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), 44, 46);

  // project the thing
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
void thing_project_facing_down_thing_at_neg_135_facing_down(void)
{
  // camera at origin, facing ahead (down the x=1 line)
  vertex c_pos(0,0);
  camera c;
  c.set_map_position(&c_pos);
  c.set_facing_angle(DEG_TO_RAD(270));

  // thing  at (-1,-1), facing down
  int thing_type = 3002; // demon (has 8 rotations)
  vertex t_pos(-100,-100);
  simple_thing s(thing_type, &t_pos, DEG_TO_RAD(270));

  // double-check the angle math
  float view_ang  = c_pos.angle_to_point(&t_pos);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(view_ang), -136, -134);

  // project the thing
  float ang = s.get_rotation_angle(&c);
  TEST_ASSERT_WITHIN(RAD_TO_DEG(ang), 134, 136);
}

void thing_tests(void)
{
  //game_init();
  thing_project_head_on_facing_toward_test();
  thing_project_head_on_facing_away_test();
  thing_project_head_on_bkwd_facing_toward_test();
  thing_project_head_on_facing_left_test();
  thing_project_at_45_facing_180();
  thing_project_at_neg45_facing_180();
  thing_project_facing_up_thing_at_45_facing_down();
  thing_project_facing_down_thing_at_neg_135_facing_down();
  //game_destroy();
}

