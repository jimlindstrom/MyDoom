#include <string.h>
#include <stdio.h>

#include "segment.h"

segment::segment()
{
}

segment::~segment()
{
}

bool segment::read_from_lump_data(uint8_t const *lump_data)
{
  start_vertex_num = *((uint16_t*)lump_data); lump_data += 2;
  end_vertex_num   = *((uint16_t*)lump_data); lump_data += 2;
  angle            = *(( int16_t*)lump_data); lump_data += 2;
  linedef_num      = *((uint16_t*)lump_data); lump_data += 2;
  direction        = *((uint16_t*)lump_data); lump_data += 2;
  offset           = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

void segment::set_linedef(linedef const *ld)
{
  _linedef = ld;
}

void segment::render_player_view(player const *_player, overhead_map *omap) const
{
  color_rgba red(255, 0, 0, 255);
  omap->draw_line(start_vertex, end_vertex, &red);
}
