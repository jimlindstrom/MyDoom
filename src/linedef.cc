#include <stdlib.h>
#include <stdio.h>

#include "linedef.h"
#include "common.h"

//#define DEBUG_PRINTING
#include "debug.h"

linedef::linedef()
{
  left_sidedef = NULL;
  right_sidedef = NULL;
}

linedef::~linedef()
{
}

bool linedef::read_from_lump_data(uint8_t const *lump_data)
{
  start_vertex_num  = *((uint16_t*)lump_data); lump_data += 2;
  end_vertex_num    = *((uint16_t*)lump_data); lump_data += 2;
  flags             = *((uint16_t*)lump_data); lump_data += 2;
  special_type      = *((uint16_t*)lump_data); lump_data += 2;
  sector_tag        = *((uint16_t*)lump_data); lump_data += 2;
  right_sidedef_num = *((uint16_t*)lump_data); lump_data += 2;
  left_sidedef_num  = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

void linedef::set_left_sidedef(sidedef const *_sidedef)
{
  left_sidedef = _sidedef;
}

void linedef::set_right_sidedef(sidedef const *_sidedef)
{
  right_sidedef = _sidedef;
}

void linedef::set_start_vertex(vertex const *v)
{
  start_vertex = v;
}

void linedef::set_end_vertex(vertex const *v)
{
  end_vertex = v;
}

int16_t linedef::get_ceiling(int direction) const
{
  return get_sidedef(direction)->get_sector()->get_ceiling_height();
}

int16_t linedef::get_floor(int direction) const
{
  return get_sidedef(direction)->get_sector()->get_floor_height();
}

void linedef::render(int direction, float ldx_l, float ldx_r, 
                     int x_l, int x_r, 
                     float y0_l, float dy_l, float y0_r, float dy_r,
                     float dist_l, float dist_r,
                     uint16_t light_level,
                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  wall_texture const *tex;
  int16_t x_offset, y_offset;
  float yt_l, yb_l, yt_r, yb_r;
  int16_t ld_h;
  sidedef const *_sd = get_sidedef(direction);

  // if one-sided -> it's a solid wall
  if(is_one_sided())
  {
    if((tex = _sd->get_mid_texture()))
    {
      yt_l = y0_l + (get_ceiling(direction) * dy_l);
      yb_l = y0_l + (get_floor(direction)   * dy_l);
      yt_r = y0_r + (get_ceiling(direction) * dy_r);
      yb_r = y0_r + (get_floor(direction)   * dy_r);
      ld_h = get_ceiling(direction) - get_floor(direction);

      if(!lower_is_unpegged() || ld_h==0) // if one-sided -> it's top-pegged (top of texture hangs at the ceiling)  
      {
        y_offset = 0;
      }
      else /*if(lower_is_unpegged())*/    // if lower-unpegged -> it's bottom-pegged (bottom of texture sits on the floor)
      {
        y_offset = ld_h - (tex->get_height() % ld_h); // FIXME: off by 1?
      }
      x_offset  = _sd->get_x_offset();
      y_offset += _sd->get_y_offset();

      debug_printf("        LD-1M:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_ceiling(direction), get_floor(direction), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, dist_l, dist_r, x_offset, y_offset, light_level, vp, floor, ceiling, true, true);
    }
  }
  // if two-sided, it's a bridge between two sectors
  else if(is_two_sided())
  {
    // UPPER TEXTURE
    yt_l = y0_l + (get_ceiling(direction  ) * dy_l);
    yb_l = y0_l + (get_ceiling(1-direction) * dy_l);
    yt_r = y0_r + (get_ceiling(direction  ) * dy_r);
    yb_r = y0_r + (get_ceiling(1-direction) * dy_r);
    ld_h = get_ceiling(direction) - get_ceiling(1-direction);

    if((tex = get_sidedef(direction)->get_upper_texture()))
    {
      if(!upper_is_unpegged() && ld_h>0)   // upper texture is pegged to the lowest ceiling
      {
        y_offset = ld_h - (tex->get_height() % ld_h); // FIXME: off by 1?
      } 
      else /*if(upper_is_unpegged())*/     // if upper-unpegged -> upper texture pegged to the highest ceiling
      {
        y_offset = 0;
      } // x,y offsets are applied next, after pegging
      x_offset  = _sd->get_x_offset();
      y_offset += _sd->get_y_offset();

      debug_printf("        LD-2U:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_ceiling(direction), get_ceiling(1-direction), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, dist_l, dist_r, x_offset, y_offset, light_level, vp, NULL, ceiling, true, false);
    }
    else
    {
      debug_printf("        LD-2U: (clip only)\n");
      //int16_t h=games_get_screen_height();

      for(int x=x_l; x<=x_r; x++)
      {
        float yt = yt_l + (yt_r-yt_l)*(x-x_l)/(x_r-x_l);
        float dist = dist_l + (dist_r-dist_l)*(x-x_l)/(x_r-x_l);
        //float yb = yb_l + (yb_r-yb_l)*(x-x_l)/(x_r-x_l);
        if(ceiling)
        {
          // top of ceiling = one pixel lower than the [bottom of the lowest ceiling]
          // bot of ceiling = one pixel above the wall (or [ceil], if lower) (or [floor], if higher)
          int16_t ceil_yt = vp->get_ceiling_clip(x)+1;
          int16_t ceil_yb = MIN(vp->get_floor_clip(x)-1, yt-1);
          if(ceil_yt  <= ceil_yb ) { ceiling->update_clip(x, ceil_yb,  ceil_yt ); }
        }
      }
    }

    // LOWER TEXTURE
    yt_l = y0_l + (get_floor(1-direction) * dy_l);
    yb_l = y0_l + (get_floor(direction  ) * dy_l);
    yt_r = y0_r + (get_floor(1-direction) * dy_r);
    yb_r = y0_r + (get_floor(direction  ) * dy_r);
    ld_h = get_floor(1-direction) - get_floor(direction);

    if((tex = get_sidedef(direction)->get_lower_texture()))
    {
      if(!lower_is_unpegged() || ld_h==0)    // lower texture is pegged to the highest floor
      {
        y_offset = 0;
      }
      else /*if(lower_is_unpegged())*/       // if lower-unpegged -> lower texture pegged to the lowest floor
      {
        y_offset = ld_h - (tex->get_height() % ld_h); // FIXME: off by 1?
      } // x,y offsets are applied next, after pegging
      x_offset  = _sd->get_x_offset();
      y_offset += _sd->get_y_offset();

      debug_printf("        LD-2L:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_floor(1-direction), get_floor(direction), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, dist_l, dist_r, x_offset, y_offset, light_level, vp, floor, NULL, false, true);
    }
    else
    {
      debug_printf("        LD-2L: (clip only)\n");
      // FIXME: this is the outer loop of tex->render. It's needed in order to still do clipping
      //int16_t h=games_get_screen_height();

      for(int x=x_l; x<=x_r; x++)
      {
        //float yt = yt_l + (yt_r-yt_l)*(x-x_l)/(x_r-x_l);
        float yb = yb_l + (yb_r-yb_l)*(x-x_l)/(x_r-x_l);
        float dist = dist_l + (dist_r-dist_l)*(x-x_l)/(x_r-x_l);
        if(floor)
        {
          // top of floor be: one pixel below the wall (or [floor], if higher) (or [ceil], if lower)
          // bot of floor be: one pixel higher than the [top of the tallest floor]
          int16_t floor_yt = MAX(vp->get_ceiling_clip(x)+1, yb-1);
          int16_t floor_yb = vp->get_floor_clip(x)-1;
          if(floor_yt <= floor_yb) { floor  ->update_clip(x, floor_yb, floor_yt); }
        }
      }
    }

    if((tex = get_sidedef(direction)->get_mid_texture())) // Right now this gets used for masked see-thru walls
    {
      yt_l = y0_l + (get_ceiling(direction) * dy_l);
      yb_l = y0_l + (get_floor(direction)   * dy_l);
      yt_r = y0_r + (get_ceiling(direction) * dy_r);
      yb_r = y0_r + (get_floor(direction)   * dy_r);
      ld_h = get_ceiling(direction) - get_floor(direction);

      // if middle texture is set
      //   -> it is clipped by the lowest ceiling and the highest floor
      //   -> it follows same alignment logi as single-sided linedef, but does not repeat vertically (FIXME)
      if(!lower_is_unpegged() || ld_h==0) // if one-sided -> it's top-pegged (top of texture hangs at the ceiling)  
      {
        y_offset = 0;
      }
      else /*if(lower_is_unpegged())*/    // if lower-unpegged -> it's bottom-pegged (bottom of texture sits on the floor)
      {
        y_offset = ld_h - (tex->get_height() % ld_h); // FIXME: off by 1?
      }
      x_offset  = _sd->get_x_offset();
      y_offset += _sd->get_y_offset();

      debug_printf("        LD-2M:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_ceiling(direction), get_floor(direction), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, dist_l, dist_r, x_offset, y_offset, light_level, vp, floor, NULL, false, true);
    }
  }
}
