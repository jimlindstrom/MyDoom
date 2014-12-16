#include <stdlib.h>
#include <stdio.h>

#include "linedef.h"
#include "common.h"

#define DEBUG_PRINTING
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

int16_t linedef::get_highest_ceiling(void) const
{
  int16_t h = -32767;
  if(left_sidedef && left_sidedef->get_sector())
  {
    h = MAX(h, left_sidedef->get_sector()->get_ceiling_height());
  }
  if(right_sidedef && right_sidedef->get_sector())
  {
    h = MAX(h, right_sidedef->get_sector()->get_ceiling_height());
  }
  return h;
}

int16_t linedef::get_lowest_ceiling(void) const
{
  int16_t h = 32767;
  if(left_sidedef && left_sidedef->get_sector())
  {
    h = MIN(h, left_sidedef->get_sector()->get_ceiling_height());
  }
  if(right_sidedef && right_sidedef->get_sector())
  {
    h = MIN(h, right_sidedef->get_sector()->get_ceiling_height());
  }
  return h;
}

int16_t linedef::get_highest_floor(void) const
{
  int16_t h = -32767;
  if(left_sidedef && left_sidedef->get_sector())
  {
    h = MAX(h, left_sidedef->get_sector()->get_floor_height());
  }
  if(right_sidedef && right_sidedef->get_sector())
  {
    h = MAX(h, right_sidedef->get_sector()->get_floor_height());
  }
  return h;
}

int16_t linedef::get_lowest_floor(void) const
{
  int16_t h = 32767;
  if(left_sidedef && left_sidedef->get_sector())
  {
    h = MIN(h, left_sidedef->get_sector()->get_floor_height());
  }
  if(right_sidedef && right_sidedef->get_sector())
  {
    h = MIN(h, right_sidedef->get_sector()->get_floor_height());
  }
  return h;
}

void linedef::render(int direction, float ldx_l, float ldx_r, int x_l, int x_r, float y0_l, float dy_l, float y0_r, float dy_r,
                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  wall_texture const *tex;
  int16_t x_offset, y_offset;
  sidedef const *_sd = get_sidedef(direction);

  // if one-sided -> it's a solid wall
  if(is_one_sided())
  {
    if((tex = _sd->get_mid_texture()))
    {
      float yt_l = y0_l + (get_lowest_ceiling() * dy_l);
      float yb_l = y0_l + (get_highest_floor()  * dy_l);
      float yt_r = y0_r + (get_lowest_ceiling() * dy_r);
      float yb_r = y0_r + (get_highest_floor()  * dy_r);
      int16_t ld_h = get_lowest_ceiling() - get_highest_floor();

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

      debug_printf("        LD-M:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_highest_floor(), get_lowest_ceiling(), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, x_offset, y_offset, vp, floor, ceiling, true, true);
    }
  }
  // if two-sided, it's a bridge between two sectors
  else if(is_two_sided())
  {
    if((tex = get_sidedef(direction)->get_upper_texture()))
    {
      float yt_l = y0_l + (get_highest_ceiling() * dy_l);
      float yb_l = y0_l + (get_lowest_ceiling()  * dy_l);
      float yt_r = y0_r + (get_highest_ceiling() * dy_r);
      float yb_r = y0_r + (get_lowest_ceiling()  * dy_r);
      int16_t ld_h = get_highest_ceiling() - get_lowest_ceiling();

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

      debug_printf("        LD-U:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_highest_ceiling(), get_lowest_ceiling(), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, x_offset, y_offset, vp, NULL, ceiling, true, false);
    }

    if((tex = get_sidedef(direction)->get_lower_texture()))
    {
      float yt_l = y0_l + (get_highest_floor() * dy_l);
      float yb_l = y0_l + (get_lowest_floor()  * dy_l);
      float yt_r = y0_r + (get_highest_floor() * dy_r);
      float yb_r = y0_r + (get_lowest_floor()  * dy_r);
      int16_t ld_h = get_highest_floor() - get_lowest_floor();

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

      debug_printf("        LD-L:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_highest_floor(), get_lowest_floor(), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, x_offset, y_offset, vp, floor, NULL, false, true);
    }

    if((tex = get_sidedef(direction)->get_mid_texture()))
    {
      float yt_l = y0_l + (get_lowest_ceiling() * dy_l);
      float yb_l = y0_l + (get_highest_floor()  * dy_l);
      float yt_r = y0_r + (get_lowest_ceiling() * dy_r);
      float yb_r = y0_r + (get_highest_floor()  * dy_r);
      int16_t ld_h = get_lowest_ceiling() - get_highest_floor();

      // if middle texture is set
      //   -> it is clipped by the lowest ceiling and the highest floor
      //   -> it follows same alignment logi as single-sided linedef, but does not repeat vertically (FIXME)
      x_offset  = _sd->get_x_offset();
      y_offset  = _sd->get_y_offset();

      debug_printf("        LD-L:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f], ofs:[%d,%d]\n",
                   ldx_l, ldx_r, x_l, x_r, get_highest_floor(), get_lowest_floor(), yt_l, yt_r, yb_l, yb_r, x_offset, y_offset);
      tex->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, x_offset, y_offset, vp, floor, NULL, false, true);
    }
  }
}
