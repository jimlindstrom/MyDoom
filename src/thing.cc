#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing.h"
#include "thing_definitions.h"
#include "subsector.h"
#include "palettes.h"
#include "games.h"
#include "frame_buf.h"

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

  // figure out which sprite to use
  proj->sprite_angle = _camera->get_map_position()->angle_to_point(&map_position) - facing_angle + DEG_TO_RAD(90);
  if(proj->sprite_angle <      0.0) { proj->sprite_angle += 2.0*M_PI; }
  if(proj->sprite_angle > 2.0*M_PI) { proj->sprite_angle -= 2.0*M_PI; }
  proj->_sprite = get_cur_sprite(proj); // NOTE: requires proj->sprite_angle be filled in
  if(!proj->_sprite) { delete proj; return NULL; }

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

sprite const *thing::get_cur_sprite(thing_projection const *proj) const
{
  int sprite_angle_idx = 1 + MIN(8, MAX(0, (int)(proj->sprite_angle / DEG_TO_RAD(45.0))));
  debug_printf("    sprite angle: %.1f, idx: %d\n", RAD_TO_DEG(proj->sprite_angle), sprite_angle_idx);

  if(!animation) { return NULL; }
  if(animation->get_num_frames()==0) { return NULL; }

  uint8_t cur_frame_idx = get_frame_idx();
  sprite_animation_frame const *cur_frame = animation->get_frame(cur_frame_idx);
  if(!cur_frame) { return NULL; }

  sprite const *cur_sprite;
  if(cur_frame->get_num_angles() > sprite_angle_idx)
  {
    cur_sprite = cur_frame->get_sprite(sprite_angle_idx);
  }
  else
  {
    cur_sprite = cur_frame->get_sprite(0);
  }
  return cur_sprite;
}

