#include <stdlib.h>
#include <stdio.h>

#include "linedef.h"
#include "common.h"

#define TOP_PEGGED    1
#define BOTTOM_PEGGED 2

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

void linedef::render(float ldx_l, float ldx_r, int x_l, int x_r, float y0_l, float dy_l, float y0_r, float dy_r) const
{
  // if one-sided -> it's a solid wall
  if(is_one_sided())
  {
    int alignment = TOP_PEGGED; // if one-sided -> it's top-pegged (top of texture hangs at the ceiling)
    if(lower_is_unpegged())
    {
      // if lower-unpegged -> it's bottom-pegged (bottom of texture sits on the floor)
      alignment = BOTTOM_PEGGED;
    }
  }
  // if two-sided, it's a bridge between two sectors
  else if(is_two_sided())
  {
    //   -> upper texture is pegged to the lowest ceiling
    //   -> lower texture is pegged to the highest floor
    // if upper-unpegged -> upper texture pegged to the highest ceiling
    // if lower-unpegged -> lower texture pegged to the lowest floor
    // x,y offsets are applied next, after pegging
    // if middle texture is set
    //   -> it is clipped by the lowest ceiling and the highest floor
    //   -> it follows same alignment logi as single-sided linedef, but does not repeat vertically
  }

  float yt_l = y0_l + (get_lowest_ceiling() * dy_l);
  float yb_l = y0_l + (get_highest_floor()  * dy_l);
  float yt_r = y0_r + (get_lowest_ceiling() * dy_r);
  float yb_r = y0_r + (get_highest_floor()  * dy_r);
  int16_t ld_h = get_lowest_ceiling() - get_highest_floor();

  printf("        LDx:[%.2f,%.2f], x:[%d,%d], h:[%d,%d], y_t:[%.1f,%.1f], y_b:[%.1f,%.1f]\n",
         ldx_l, ldx_r, x_l, x_r, get_highest_floor(), get_lowest_ceiling(), yt_l, yt_r, yb_l, yb_r);
  if(left_sidedef)  // FIXME: how to know which one to use??
  {
    left_sidedef ->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r);
  }
  else if(right_sidedef)
  {
    right_sidedef->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r);
  }
}
