#include <string.h>

#include "subsector.h"

subsector::subsector()
{
}

subsector::~subsector()
{
}

bool subsector::read_from_lump_data(uint8_t const *lump_data)
{
  num_segments      = *((uint16_t*)lump_data); lump_data += 2;
  first_segment_num = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

