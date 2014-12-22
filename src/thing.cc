#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing.h"
#include "subsector.h"
#include "palettes.h"
#include "games.h"
#include "frame_buf.h"

//#define DEBUG_PRINTING
#include "debug.h"

thing::thing()
{
  frame_ctr = 0;
}

thing::~thing()
{
}

sector const *thing::get_sector(void) const { return _subsector->get_sector(); }

bool thing::read_from_lump_data(uint8_t const *lump_data)
{
  map_position.set_x(*(( int16_t*)lump_data)); lump_data += 2;
  map_position.set_y(*(( int16_t*)lump_data)); lump_data += 2;
  facing_angle     = (*(( int16_t*)lump_data))/256.0 ; lump_data += 2;
  thing_type       = *((uint16_t*)lump_data) ; lump_data += 2;
  flags            = *((uint16_t*)lump_data) ; lump_data += 2;

  // convert angle from degrees to radians
  facing_angle = DEG_TO_RAD(facing_angle+90);

  // get the definition (description, etc.)
  defn = thing_definition_lookup(thing_type);

  animation = sprites_lookup_animation(defn->sprite_prefix);

  return true;
}

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

void thing::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  thing_projection proj;

  project(_projector, _player, &proj);
  if(proj.is_visible)
  {
    proj.clip(col_ranges);
    proj.draw();
  }
}

void thing::project(projector const *_projector, player const *_player, thing_projection *proj) const
{
  proj->is_visible = false;

  // figure out which sprite to use
  proj->sprite_angle = _player->get_map_position()->angle_to_point(&map_position) - facing_angle + DEG_TO_RAD(90);
  if(proj->sprite_angle <      0.0) { proj->sprite_angle += 2.0*M_PI; }
  if(proj->sprite_angle > 2.0*M_PI) { proj->sprite_angle -= 2.0*M_PI; }
  proj->_sprite = get_cur_sprite(proj); // NOTE: requires proj->sprite_angle be filled in
  if(!proj->_sprite) { return; }

  // project horizontally
  float angle_c = _player->get_map_position()->angle_to_point(&map_position) - _player->get_facing_angle();
  if     (angle_c >  M_PI) { angle_c -= 2.0*M_PI; }
  else if(angle_c < -M_PI) { angle_c += 2.0*M_PI; }
  float dist_c  = _player->get_map_position()->distance_to_point(&map_position);
  float angle_delta = atan2(proj->_sprite->get_width()/2.0, dist_c);
  proj->angle_l = angle_c + angle_delta;
  proj->angle_r = angle_c - angle_delta;
  proj->horiz_fov_radius = _projector->get_horiz_fov_radius();
  proj->dist_l = dist_c; // FIXME: do some trig here. this is an approximation
  proj->dist_r = dist_c; // FIXME: do some trig here. this is an approximation
  if(proj->is_backface())    { return; }
  if(proj->is_outside_fov()) { return; }
  debug_printf("  rendering \"%s\"\n", defn->description);
  debug_printf("    angles: [%1.f, %.1f, %.1f] dist: %.1f\n", 
              RAD_TO_DEG(proj->angle_l), RAD_TO_DEG(proj->angle_c), RAD_TO_DEG(proj->angle_r), dist_c);
  proj->x_l = _projector->project_horiz_angle_to_x(proj->angle_l);
  proj->x_r = _projector->project_horiz_angle_to_x(proj->angle_r);

  // project vertically
  float y0, dy;
  float rel_height = _player->get_view_height() - get_sector()->get_floor_height(); // FIXME: assumes it sits on floor
  _projector->project_z_to_y(-rel_height, dist_c, &y0, &dy);
  float h = (proj->x_r - proj->x_l) * proj->_sprite->get_height() / proj->_sprite->get_width();
  proj->y_t = y0-h;
  proj->y_b = y0;
  proj->z_t = get_sector()->get_floor_height() + h;
  proj->z_b = get_sector()->get_floor_height();
  debug_printf("    x:[%.1f,%.1f], h:%.1f, y0:%.1f, dy:%.1f, y:[%.1f,%.1f]\n", proj->x_l, proj->x_r, h, y0, dy, proj->y_t, proj->y_b);
  debug_printf("    aspect ratio: %.3f\n", (proj->x_r - proj->x_l)/(proj->y_b - proj->y_t));

  proj->is_visible = true;
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

