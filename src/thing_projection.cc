#include <stdio.h>
#include <math.h>

#include "common.h"
#include "games.h"
#include "palettes.h"
#include "frame_buf.h"
#include "thing_projection.h"

//#define DEBUG_PRINTING
#include "debug.h"

void thing_projection::clip(column_range_list *col_ranges)
{
  int16_t screen_h = games_get_screen_height();
  int16_t screen_w = games_get_screen_width();

  x_l_c = MAX(0,          x_l);
  x_r_c = MIN(screen_w-1, x_r);
  y_t_c = MAX(0,          y_t);
  y_b_c = MIN(screen_h-1, y_b);

  wall_projection const *wall_proj = col_ranges->get_left_range();
  while(wall_proj)
  {
    if(wall_proj->overlaps_range(x_l_c, x_r_c))
    {
      int16_t xl = MAX(x_l_c, wall_proj->x_l);
      int16_t xr = MIN(x_r_c, wall_proj->x_r);
      for(int16_t x=xl; x<=xr; x++)
      {
        float clip_dist  = wall_proj->dist_l + (wall_proj->dist_r - wall_proj->dist_l)*(x - wall_proj->x_l)/(wall_proj->x_r - wall_proj->x_l);
        float thing_dist = dist_l + (dist_r - dist_l)*(x - x_l)/(x_r - x_l);
        if(thing_dist < clip_dist)
        {
          cliptop[x] = y_t_c;
          clipbot[x] = y_b_c;
        }
      }
    }
    wall_proj = wall_proj->next_range;
  }
}

void thing_projection::draw(void)
{
  palette const *pal = palettes_get(0); // FIXME
  color_rgba c;

  if(x_l_c == x_r_c) { return; } 
  for(int x=x_l_c; x<=x_r_c; x++)
  {
    int u =   (float)(x - x_l)/(x_r - x_l) * (_sprite->get_width() -1);
    for(int y=cliptop[x]; y<=clipbot[x]; y++)
    {
      int v = (float)(y - y_t)/(y_b - y_t) * (_sprite->get_height()-1);

      uint8_t color_idx = _sprite->get_pixel(u, v); // FIXME: do this up-front
      if(color_idx != TRANSPARENT_COLOR_IDX)
      {
        c.set_to(pal->get_color(color_idx)); // FIXME: do this up-front
        frame_buf_overlay_pixel(x, y, &c);
      }
    }
  }
}

