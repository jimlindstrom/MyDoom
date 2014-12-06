#include "linedef.h"

linedef::linedef()
{
}

linedef::~linedef()
{
}

bool linedef::read_from_lump_data(uint8_t const *lump_data)
{
  start_vertex  = *((uint16_t*)lump_data); lump_data += 2;
  end_vertex    = *((uint16_t*)lump_data); lump_data += 2;
  flags         = *((uint16_t*)lump_data); lump_data += 2;
  special_type  = *((uint16_t*)lump_data); lump_data += 2;
  sector_tag    = *((uint16_t*)lump_data); lump_data += 2;
  right_sidedef = *((uint16_t*)lump_data); lump_data += 2;
  left_sidedef  = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

