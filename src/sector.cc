#include <string.h>

#include "sector.h"

sector::sector()
{
}

sector::~sector()
{
}

bool sector::read_from_lump_data(uint8_t const *lump_data)
{
  floor_height     = *((int16_t*)lump_data); lump_data += 2;
  ceiling_height   = *((int16_t*)lump_data); lump_data += 2;

  memcpy(floor_texture_name, lump_data, 8); lump_data += 8;
  floor_texture_name[8] = 0;

  memcpy(ceiling_texture_name, lump_data, 8); lump_data += 8;
  ceiling_texture_name[8] = 0;

  light_level = *((uint16_t*)lump_data); lump_data += 2;
  type        = *((uint16_t*)lump_data); lump_data += 2;
  tag_num     = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

