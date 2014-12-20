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

int16_t linedef::get_ceiling_z(int direction) const
{
  return get_sidedef(direction)->get_sector()->get_ceiling_height();
}

int16_t linedef::get_floor_z(int direction) const
{
  return get_sidedef(direction)->get_sector()->get_floor_height();
}

void linedef::calc_upper_y_values(int direction, wall_projection *wall) const
{
  wall->yt_l = wall->y0_l + (get_ceiling_z(direction  ) * wall->dy_l);
  wall->yb_l = wall->y0_l + (get_ceiling_z(1-direction) * wall->dy_l);
  wall->yt_r = wall->y0_r + (get_ceiling_z(direction  ) * wall->dy_r);
  wall->yb_r = wall->y0_r + (get_ceiling_z(1-direction) * wall->dy_r);
  wall->ld_h = get_ceiling_z(direction) - get_ceiling_z(1-direction);
}

void linedef::calc_mid_y_values(  int direction, wall_projection *wall) const
{
  wall->yt_l = wall->y0_l + (get_ceiling_z(direction) * wall->dy_l);
  wall->yb_l = wall->y0_l + (get_floor_z(  direction) * wall->dy_l);
  wall->yt_r = wall->y0_r + (get_ceiling_z(direction) * wall->dy_r);
  wall->yb_r = wall->y0_r + (get_floor_z(  direction) * wall->dy_r);
  wall->ld_h = get_ceiling_z(direction) - get_floor_z(direction);
}

void linedef::calc_lower_y_values(int direction, wall_projection *wall) const
{
  wall->yt_l = wall->y0_l + (get_floor_z(1-direction) * wall->dy_l);
  wall->yb_l = wall->y0_l + (get_floor_z(direction  ) * wall->dy_l);
  wall->yt_r = wall->y0_r + (get_floor_z(1-direction) * wall->dy_r);
  wall->yb_r = wall->y0_r + (get_floor_z(direction  ) * wall->dy_r);
  wall->ld_h = get_floor_z(1-direction) - get_floor_z(direction);
}

int16_t linedef::get_upper_ty_peg_offset(int16_t ld_h, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(!upper_is_unpegged() && ld_h>0)   // upper texture is pegged to the lowest ceiling
  {
    ty_peg_offset = ld_h - (tex_h % ld_h);
  } 
  return ty_peg_offset;
}

int16_t linedef::get_mid_ty_peg_offset(int16_t ld_h, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(lower_is_unpegged() && ld_h>0)// if lower-unpegged -> it's bottom-pegged (bottom of texture sits on the floor)
  {
    ty_peg_offset = ld_h - (tex_h % ld_h);
  }
  return ty_peg_offset;
}

int16_t linedef::get_lower_ty_peg_offset(int16_t ld_h, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(lower_is_unpegged() && ld_h>0) // if lower-unpegged -> lower texture pegged to the lowest floor
  {
    ty_peg_offset = ld_h - (tex_h % ld_h);
  }
  return ty_peg_offset;
}

void linedef::render(int direction, wall_projection *wall) const
{
  sidedef const *_sd = get_sidedef(direction);

  // if one-sided -> it's a solid wall
  if(is_one_sided())
  {
    calc_mid_y_values(direction, wall);
    if((wall->tex = _sd->get_mid_texture()))
    {
      debug_printf("        LD-1M\n");
      wall->tx_offset = _sd->get_tx_offset();
      wall->ty_offset = _sd->get_ty_offset() + get_mid_ty_peg_offset(wall->ld_h, wall->tex->get_height());
      wall->render_1sided_mid();
    }
  }

  // if two-sided, it's a bridge between two sectors
  else if(is_two_sided())
  {
    // UPPER TEXTURE
    calc_upper_y_values(direction, wall);
    if((wall->tex = get_sidedef(direction)->get_upper_texture()))
    {
      debug_printf("        LD-2U\n");
      wall->tx_offset = _sd->get_tx_offset();
      wall->ty_offset = _sd->get_ty_offset() + get_upper_ty_peg_offset(wall->ld_h, wall->tex->get_height());
      wall->render_2sided_upper();
    }
    else
    {
      debug_printf("        LD-2U: (clip only)\n");
      wall->clip_2sided_upper();
    }

    // LOWER TEXTURE
    calc_lower_y_values(direction, wall);
    if((wall->tex = get_sidedef(direction)->get_lower_texture()))
    {
      debug_printf("        LD-2L\n");
      wall->tx_offset = _sd->get_tx_offset();
      wall->ty_offset = _sd->get_ty_offset() + get_lower_ty_peg_offset(wall->ld_h, wall->tex->get_height());
      wall->render_2sided_lower();
    }
    else
    {
      debug_printf("        LD-2L: (clip only)\n");
      wall->clip_2sided_lower();
    }

    // MID TEXTURE
    calc_mid_y_values(direction, wall);
    if((wall->tex = get_sidedef(direction)->get_mid_texture())) // Right now this gets used for masked see-thru walls
    {
      // if middle texture is set
      //   -> it is clipped by the lowest ceiling and the highest floor (FIXME)
      //   -> it follows same alignment logi as single-sided linedef, but does not repeat vertically (FIXME)
      debug_printf("        LD-2M\n");
      wall->tx_offset = _sd->get_tx_offset();
      wall->ty_offset = _sd->get_ty_offset() + get_mid_ty_peg_offset(wall->ld_h, wall->tex->get_height());
      wall->render_2sided_lower();
    }
  }
}
