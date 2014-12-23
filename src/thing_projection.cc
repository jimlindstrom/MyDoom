#include <stdio.h>
#include <math.h>

#include "common.h"
#include "games.h"
#include "palettes.h"
#include "lighting.h"
#include "frame_buf.h"
#include "thing_projection.h"

//#define DEBUG_PRINTING
#include "debug.h"

void thing_projection::clip(clipped_segment_projections *clipped_seg_projs)
{
  int16_t screen_h = games_get_screen_height();
  int16_t screen_w = games_get_screen_width();
  bool have_tried_nonsolid_walls = false;

  x_l_c = MAX(0,          x_l);
  x_r_c = MIN(screen_w-1, x_r);
  y_t_c = MAX(0,          y_t);
  y_b_c = MIN(screen_h-1, y_b);

  clipped_segment_projection const *clipped_seg_proj = clipped_seg_projs->get_left_solid_csp();
  while(clipped_seg_proj)
  {
    if(clipped_seg_proj->overlaps_range(x_l_c, x_r_c))
    {
      int16_t xl = MAX(x_l_c, clipped_seg_proj->x_l);
      int16_t xr = MIN(x_r_c, clipped_seg_proj->x_r);
      for(int16_t x=xl; x<=xr; x++)
      {
        float clip_dist  = clipped_seg_proj->dist_l + ( (clipped_seg_proj->dist_r - clipped_seg_proj->dist_l) *
                                                        (x                        - clipped_seg_proj->x_l   ) /
                                                        (clipped_seg_proj->x_r    - clipped_seg_proj->x_l   ) );
        float thing_dist = dist_l + (dist_r - dist_l)*(x - x_l)/(x_r - x_l);
        // First, check whether the thing is nearer than the closest solid wall
        if(thing_dist < clip_dist) // thing is closer than player
        {
            cliptop[x] = y_t_c;
            clipbot[x] = y_b_c;
        }
        // Then check whether it's occluded by any visplanes
        if(clip_dist < thing_dist) // wall is closer than thing
        {
          if(clipped_seg_proj->upper.tex && (clipped_seg_proj->upper.z_t > clipped_seg_proj->upper.z_b))
          {
            cliptop[x] = MAX(cliptop[x], clipped_seg_proj->get_sprite_clip_top(x));
          }
          if(clipped_seg_proj->lower.tex && (clipped_seg_proj->lower.z_t > clipped_seg_proj->lower.z_b))
          {
            clipbot[x] = MIN(clipbot[x], clipped_seg_proj->get_sprite_clip_bot(x));
          }
        }
      }
    }

    // next
    clipped_seg_proj = clipped_seg_proj->next_csp;
    if(!clipped_seg_proj && !have_tried_nonsolid_walls)
    {
      have_tried_nonsolid_walls = true;
      clipped_seg_proj = clipped_seg_projs->get_first_nonsolid_csp();
    }
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

    float clip_dist  = dist_l + ( (dist_r - dist_l) *
                                  (x      - x_l   ) /
                                  (x_r    - x_l   ) );
    float pct_darkened1 = DIST_TO_PCT_DARKENED(clip_dist);  // Darken for distance
    float pct_darkened2 = ((255-sector_light_level)/255.0); // Darken for sector light level
    float pct_darkened = 1.0 - ((1.0-pct_darkened1)*(1.0-pct_darkened2));

    for(int y=cliptop[x]; y<=clipbot[x]; y++)
    {
      int v = (float)(y - y_t)/(y_b - y_t) * (_sprite->get_height()-1);

      uint8_t color_idx = _sprite->get_pixel(u, v); // FIXME: do this up-front
      if(color_idx != TRANSPARENT_COLOR_IDX)
      {
        c.set_to(pal->get_color(color_idx)); // FIXME: do this up-front
        c.darken_by(pct_darkened);
        frame_buf_overlay_pixel(x, y, &c);
      }
    }
  }
}

