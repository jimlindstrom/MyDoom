#include <string.h>
#include <stdio.h>

#include "sidedef.h"

//#define DEBUG_PRINTING
#include "debug.h"

sidedef::sidedef()
{
}

sidedef::~sidedef()
{
}

bool sidedef::read_from_lump_data(uint8_t const *lump_data)
{
  x_offset = *((int16_t*)lump_data); lump_data += 2;
  y_offset = *((int16_t*)lump_data); lump_data += 2;

  memcpy(upper_texture_name, lump_data, 8);
  upper_texture_name[8] = 0;
  lump_data += 8;

  memcpy(lower_texture_name, lump_data, 8);
  lower_texture_name[8] = 0;
  lump_data += 8;

  memcpy(mid_texture_name, lump_data, 8);
  mid_texture_name[8] = 0;
  lump_data += 8;

  sector_num = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

void sidedef::render(float ldx_l, float ldx_r, int ld_h, int x_l, int x_r, float yt_l, float yb_l, float yt_r, float yb_r,
                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  if(mid_texture)
  {
    debug_printf("        SD rendering mid: \"%s\"\n", mid_texture_name);
    mid_texture->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, vp, floor, ceiling);
  }
  if(upper_texture)
  {
    debug_printf("        SD rendering upper: \"%s\"\n", upper_texture_name);
    upper_texture->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, vp, floor, ceiling);
  }
  if(lower_texture)
  {
    debug_printf("        SD rendering lower: \"%s\"\n", lower_texture_name);
    lower_texture->render(ldx_l, ldx_r, ld_h, x_l, x_r, yt_l, yb_l, yt_r, yb_r, vp, floor, ceiling);
  }
}

