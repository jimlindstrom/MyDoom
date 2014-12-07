#include <string.h>

#include "subsector.h"

subsector::subsector()
{
  segments = NULL;
}

subsector::~subsector()
{
  if(segments) { delete[] segments; }
}

bool subsector::read_from_lump_data(uint8_t const *lump_data)
{
  num_segments      = *((uint16_t*)lump_data); lump_data += 2;
  first_segment_num = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

void subsector::allocate_segments(void)
{
  segments = new segment const *[num_segments];
}

void subsector::set_nth_segment(int n, segment const *_segment)
{
  segments[n] = _segment;
}

