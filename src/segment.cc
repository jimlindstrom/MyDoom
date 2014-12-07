#include <string.h>
#include <stdio.h>

#include "segment.h"

segment::segment()
{
  vertexes = NULL;
}

segment::~segment()
{
  if(vertexes) { delete[] vertexes; }
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

void segment::alloc_vertexes(void)
{
  if(start_vertex_num < end_vertex_num)
  {
    num_vertexes = end_vertex_num - start_vertex_num + 1;
  }
  else
  {
    num_vertexes = start_vertex_num - end_vertex_num + 1;
  }
  vertexes = new vertex const *[num_vertexes];
}

void segment::set_nth_vertex(int n, vertex const *v)
{
  vertexes[n] = v;
}

