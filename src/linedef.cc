#include <stdlib.h>

#include "linedef.h"

linedef::linedef()
{
  vertexes = NULL;
}

linedef::~linedef()
{
  if(vertexes) { delete[] vertexes; }
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

void linedef::alloc_vertexes(void)
{
  if(start_vertex_num > end_vertex_num)
  {
    num_vertexes = end_vertex_num - start_vertex_num + 1;
  }
  else
  {
    num_vertexes = start_vertex_num - end_vertex_num + 1;
  }
  vertexes = new vertex const *[num_vertexes];
}

void linedef::set_nth_vertex(int n, vertex const *v)
{
  vertexes[n] = v;
}

