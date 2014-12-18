#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing.h"
#include "subsector.h"
#include "palettes.h"
#include "games.h"
#include "frame_buf.h"

#define DEBUG_PRINTING
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

void thing::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  color_rgba c;
  palette const *pal = palettes_get(0); // FIXME
  int16_t screen_w=games_get_screen_width(), screen_h=games_get_screen_height();

  float angle_c = _player->get_map_position()->angle_to_point(&map_position) - _player->get_facing_angle();
  if     (angle_c >  M_PI) { angle_c -= 2.0*M_PI; }
  else if(angle_c < -M_PI) { angle_c += 2.0*M_PI; }

  float dist_c  = _player->get_map_position()->distance_to_point(&map_position);

  float angle_l = angle_c + atan2(defn->radius, dist_c);
  float angle_r = angle_c - atan2(defn->radius, dist_c);

  bool is_backface = (angle_r > angle_l);
  if(is_backface) { return; }
  bool is_outside_fov = ( ( (angle_l < -_projector->get_horiz_fov_radius()) ||
                            (angle_l >  _projector->get_horiz_fov_radius()) ) &&
                          ( (angle_r < -_projector->get_horiz_fov_radius()) ||
                            (angle_r >  _projector->get_horiz_fov_radius()) ) );
  if(is_outside_fov) { return; }
  
  debug_printf("  rendering \"%s\"\n", defn->description);
  debug_printf("    angles: [%1.f, %.1f, %.1f] dist: %.1f\n", 
              RAD_TO_DEG(angle_l), RAD_TO_DEG(angle_c), RAD_TO_DEG(angle_r), dist_c);

  // FIXME: this skips over clipping

  float x_l = _projector->project_horiz_angle_to_x(angle_l);
  float x_r = _projector->project_horiz_angle_to_x(angle_r);

  if(!animation) { /*debug_printf("    NULL animation!\n");*/ return; }
  if(animation->get_num_frames()==0) { /*debug_printf("    no frames!\n");*/ return; }
  sprite_animation_frame const *cur_frame = animation->get_frame(games_get_frame_counter() % animation->get_num_frames());
  if(!cur_frame) { /*debug_printf("    NULL frame!\n");*/ return; }
  sprite const *cur_sprite = cur_frame->get_sprite(0);
  if(!cur_sprite) /*{ debug_printf("    NULL sprite!\n");*/ return; }

  float y0, dy;
  float rel_height = _player->get_view_height() - (cur_sprite->get_height() - get_sector()->get_floor_height());
  _projector->project_z_to_y(-rel_height, dist_c, &y0, &dy);

  float h = (x_r-x_l) * cur_sprite->get_height() / cur_sprite->get_width();
  float y_t = y0;
  float y_b = y0 + (h * -dy);

  debug_printf("    x:[%.1f,%.1f] y:[%.1f,%.1f]\n", x_l, x_r, y_t, y_b);

  int16_t x_l_c = MAX(0, x_l);
  int16_t x_r_c = MIN(screen_w-1, x_r);
  int16_t y_t_c = MAX(0, y_t);
  int16_t y_b_c = MIN(screen_h-1, y_b);

  if(x_l_c == x_r_c) { return; } 
  for(int x=x_l_c; x<=x_r_c; x++)
  {
    int u = (float)(x - x_l_c)/(x_r_c - x_l_c) * (cur_sprite->get_width()-1);
    for(int y=y_t_c; y<=y_b_c; y++)
    {
      int v = (float)(y - y_t)/(y_b - y_t) * (cur_sprite->get_height()-1);

      c.set_to(pal->get_color(cur_sprite->get_pixel(u, v)));
      frame_buf_draw_pixel(x, y, &c);
    }
  }
}

