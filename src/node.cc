#include <string.h>

#include "node.h"

node::node()
{
}

node::~node()
{
}

bool node::read_from_lump_data(uint8_t const *lump_data)
{
  partition.x          = *(( int16_t*)lump_data); lump_data += 2;
  partition.y          = *(( int16_t*)lump_data); lump_data += 2;
  partition.dx         = *(( int16_t*)lump_data); lump_data += 2;
  partition.dy         = *(( int16_t*)lump_data); lump_data += 2;

  right._bbox.y_top    = *(( int16_t*)lump_data); lump_data += 2;
  right._bbox.y_bottom = *(( int16_t*)lump_data); lump_data += 2;
  right._bbox.x_left   = *(( int16_t*)lump_data); lump_data += 2;
  right._bbox.x_right  = *(( int16_t*)lump_data); lump_data += 2;

  left._bbox.y_top     = *(( int16_t*)lump_data); lump_data += 2;
  left._bbox.y_bottom  = *(( int16_t*)lump_data); lump_data += 2;
  left._bbox.x_left    = *(( int16_t*)lump_data); lump_data += 2;
  left._bbox.x_right   = *(( int16_t*)lump_data); lump_data += 2;

  right.child_num      = *((uint16_t*)lump_data); lump_data += 2;
  left.child_num       = *((uint16_t*)lump_data); lump_data += 2;

  right.child_type     = right.child_num & NODE_CHILD_TYPE_MASK;
  right.child_num      = right.child_num & NODE_CHILD_NUM_MASK;

  left.child_type      = left.child_num & NODE_CHILD_TYPE_MASK;
  left.child_num       = left.child_num & NODE_CHILD_NUM_MASK;

  return true;
}

