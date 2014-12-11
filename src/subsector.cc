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

void subsector::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, overhead_map *omap) const
{
  for(int i=0; i<num_segments; i++)
  {
    segments[i]->render_player_view(col_ranges, _projector, _player, omap);
  }
}
