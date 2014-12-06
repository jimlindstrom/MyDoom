#include <string.h>

#include "sidedef.h"

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

