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

void linedef::set_z_values(int direction, clipped_segment_projection *wall) const
{
  if(is_one_sided())
  {
    wall->mid.z_t   = get_ceiling_z(direction);
    wall->mid.z_b   = get_floor_z(  direction);
  }
  else if(is_two_sided())
  {
    wall->upper.z_t = get_ceiling_z(direction  );
    wall->upper.z_b = get_ceiling_z(1-direction);
  
    wall->mid.z_t   = get_ceiling_z(1-direction);
    wall->mid.z_b   = get_floor_z(  1-direction);
  
    wall->lower.z_t = get_floor_z(1-direction);
    wall->lower.z_b = get_floor_z(direction  );
  }
}

int16_t linedef::get_upper_ty_peg_offset(int16_t dz, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(!upper_is_unpegged() && dz>0)   // upper texture is pegged to the lowest ceiling
  {
    ty_peg_offset = dz - (tex_h % dz);
  } 
  return ty_peg_offset;
}

int16_t linedef::get_mid_ty_peg_offset(int16_t dz, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(lower_is_unpegged() && dz>0)// if lower-unpegged -> it's bottom-pegged (bottom of texture sits on the floor)
  {
    ty_peg_offset = dz - (tex_h % dz);
  }
  return ty_peg_offset;
}

int16_t linedef::get_lower_ty_peg_offset(int16_t dz, int16_t tex_h) const
{
  int16_t ty_peg_offset = 0;
  if(lower_is_unpegged() && dz>0) // if lower-unpegged -> lower texture pegged to the lowest floor
  {
    ty_peg_offset = dz - (tex_h % dz);
  }
  return ty_peg_offset;
}

void linedef::set_textures(int direction, clipped_segment_projection *wall) const
{
  sidedef const *_sd = get_sidedef(direction);

  // if one-sided -> it's a solid wall
  if(is_one_sided())
  {
    wall->is_one_sided = true; // FIXME: why is this set? who cares and why?
    if((wall->mid.tex = _sd->get_mid_texture()))
    {
      debug_printf("        LD-1M\n");
      wall->mid.tx_offset   = _sd->get_tx_offset();
      wall->mid.ty_offset   = _sd->get_ty_offset() + get_mid_ty_peg_offset(  wall->mid.get_dz(),   wall->mid.tex->get_height()  );
    }
  }

  // if two-sided, it's a bridge between two sectors
  else if(is_two_sided())
  {
    wall->is_one_sided = false; // FIXME: why is this set? who cares and why?
    if((wall->upper.tex = get_sidedef(direction)->get_upper_texture()))
    {
      debug_printf("        LD-2U\n");
      wall->upper.tx_offset = _sd->get_tx_offset();
      wall->upper.ty_offset = _sd->get_ty_offset() + get_upper_ty_peg_offset(wall->upper.get_dz(), wall->upper.tex->get_height());
    }
    if((wall->lower.tex = get_sidedef(direction)->get_lower_texture()))
    {
      debug_printf("        LD-2L\n");
      wall->lower.tx_offset = _sd->get_tx_offset();
      wall->lower.ty_offset = _sd->get_ty_offset() + get_lower_ty_peg_offset(wall->lower.get_dz(), wall->lower.tex->get_height());
    }
    if((wall->mid.tex   = get_sidedef(direction)->get_mid_texture())  )
    {
      debug_printf("        LD-2M\n");
      wall->mid.tx_offset   = _sd->get_tx_offset();
      wall->mid.ty_offset   = _sd->get_ty_offset() + get_mid_ty_peg_offset(  wall->mid.get_dz(),   wall->mid.tex->get_height()  );
    }
  }
}
