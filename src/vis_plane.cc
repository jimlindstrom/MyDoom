#include <stdlib.h>
#include <stdio.h>

#include "vis_plane.h"
#include "frame_buf.h"
#include "palettes.h"
#include "lighting.h"
#include "wall_textures.h" // FIXME: shouldn't be needed. Just for temporarily looking up the sky texture
#include "common.h"

#define UNINITIALIZED -1

//#define DEBUG_PRINTING
#include "debug.h"

vis_plane::vis_plane()
{
  int16_t w=games_get_screen_width(), h=games_get_screen_height();

  x_l = w;
  x_r = -1;
  for(int i=0; i<w; i++)
  {
     y_t[i] = UNINITIALIZED; 
     y_b[i] = h+1; 
  }
}

vis_plane::~vis_plane()
{
}

void vis_plane::init(int16_t _height, flat_animation const *_tex, uint16_t _light_level)
{
  height = _height;
  tex = _tex;
  light_level = _light_level;
}

bool vis_plane::matches(int16_t _height, flat_animation const *_tex, uint16_t _light_level)
{
  return (height == _height) &&
         (tex == _tex) &&
         (light_level == _light_level);
}

/* 
 * Algorithm:
 * When Doom draws a flat, it looks for a compatible visplane, one with the 
 * same properties (lighting, height, texture). When two compatible visplanes 
 * are found, the union and intersection of their two spans are computed, and 
 * if any part of the intersection of the spans has been drawn by other flats 
 * already, then Doom creates a new visplane.
 *
 * (http://www.johnromero.com/lee_killough/editing/visplane.shtml)
 */
bool vis_plane::can_be_extended_to(int16_t new_x_l, int16_t new_x_r)
{
  int16_t inter_x_l = MAX(x_l, new_x_l);
  int16_t inter_x_r = MIN(x_r, new_x_r);

  for(int16_t x=inter_x_l; x<=inter_x_r; x++)
  {
    if(y_t[x] != UNINITIALIZED)
    {
      return false;
    }
  }
  return true;
}

void vis_plane::extend_to(int16_t new_x_l, int16_t new_x_r)
{
  int16_t union_x_l = MIN(x_l, new_x_l);
  int16_t union_x_r = MAX(x_r, new_x_r);
  x_l = union_x_l;
  x_r = union_x_r;
}

void vis_plane::update_clip(int16_t x, int16_t yb, int16_t yt)
{
  y_t[x] = yt;
  y_b[x] = yb;
}

void vis_plane::draw(camera const *_camera)
{
  int16_t h=games_get_screen_height();
  int16_t w=games_get_screen_width();

  debug_printf("    visplane (0x%08x) x:[%d,%d]", (uint32_t)this, x_l, x_r);

  // special effect for drawing sky
  if(tex->is_fake_sky())
  {
    wall_texture const *sky = wall_textures_get_by_name("SKY1");
    if(!sky) { printf("error: couldn't find sky flat!\n"); exit(0); }

    for(int16_t x=MAX(0,x_l); x<=MIN(x_r,w-1); x++)
    {
      if(y_t[x]>=0 || y_b[x]<h)
      {
        float view_angle = _projector->unproject_x_to_horiz_angle(x) + _camera->get_facing_angle();
        while(view_angle > (M_PI/2)) { view_angle -= (M_PI/2); }
        while(view_angle <        0) { view_angle += (M_PI/2); }
        float sky_x = view_angle * 255.0 / (M_PI/2.0);

        int16_t y_t_c = MAX(0, y_t[x]);
        int16_t y_b_c = MIN(y_b[x], h-1);
  
        debug_printf("  x=%d, y:[%d,%d]\n", x, y_t_c, y_b_c);
        for(int16_t y=y_t_c; y<=y_b_c; y++)
        {
          float sky_y = y * 128.0 / (h-1);
          color_rgb const *c_rgb = sky->get_pixel(sky_x, sky_y);
          color_rgba c; c.set_to(c_rgb);
          frame_buf_draw_pixel(x, y, &c);
        }
      }
    }
  }

  // regular vis_plane rendering
  else
  {
    int16_t h=games_get_screen_height();
    int16_t w=games_get_screen_width();
    palette const *pal = palettes_get(0); // FIXME: use the right palette
  
    debug_printf("    visplane (0x%08x) x:[%d,%d]", (uint32_t)this, x_l, x_r);
  
    float rel_z = _camera->get_view_height() - height;
    for(int16_t x=MAX(0,x_l); x<=MIN(x_r,w-1); x++)
    {
      if(y_t[x]>=0 || y_b[x]<h)
      {
        float view_angle = _projector->unproject_x_to_horiz_angle(x) + _camera->get_facing_angle();
        float sin_view_angle = sin(view_angle);
        float cos_view_angle = cos(view_angle);
        int16_t y_t_c = MAX(0, y_t[x]);
        int16_t y_b_c = MIN(y_b[x], h-1);
  
        debug_printf("  x=%d, y:[%d,%d]\n", x, y_t_c, y_b_c);
        for(int16_t y=y_t_c; y<=y_b_c; y++)
        {
          /*
           * screen_y = -1000*map_z/[(map_x^2)+(map_y^2)]^0.5 + (screen_h/2)
           * screen_y - (screen_h/2) = -1000*map_z / [(map_x^2)+(map_y^2)]^0.5 
           * [(map_x^2)+(map_y^2)]^0.5  = -1000*map_z / [screen_y - (screen_h/2)]
           * (map_x^2)+(map_y^2)  = [-1000*map_z / [screen_y - (screen_h/2)]]^2
           * (map_x^2) + (map_y^2)  = map_z^2 * 1000^2 / [screen_y - (screen_h/2)]^2
           */
          float cur_dist = 1000 * rel_z / (y - (h/2.0));
          int map_y = (-cur_dist * sin_view_angle) - _camera->get_map_position()->get_y();
          int map_x = (-cur_dist * cos_view_angle) - _camera->get_map_position()->get_x();
          float pct_darkened = DIST_TO_PCT_DARKENED(cur_dist);
  
          uint8_t color_idx;
          //color_idx = tex->get_cur_flat()->get_pixel(map_x % FLAT_WIDTH, map_y % FLAT_HEIGHT);
          color_idx   = tex->get_cur_flat()->get_pixel(map_x & (FLAT_WIDTH-1), map_y & (FLAT_HEIGHT-1)); // because w,h are powers of 2
 
          color_rgba c;
          c.set_to(pal->get_color(color_idx)); // FIXME: do this up-front
          c.darken_by(pct_darkened);
          frame_buf_draw_pixel(x, y, &c);
        }
      }
    }
  }
}
