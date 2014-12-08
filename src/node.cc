#include <string.h>
#include <stdio.h>

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

void node::render_player_view(player const *_player, overhead_map *omap) const
{
  bool undrawn_columns_toward_child = false; // FIXME: not implemented yet.
  node_child_link const *leftmost_child;
  node_child_link const *rightmost_child;
  vertex const *v;

  v = _player->get_map_position();
  if(!partition.is_point_on_left(v)) // FIXME: why is this backwards?
  {
    leftmost_child  = &left;
    rightmost_child = &right;
  }
  else
  {
    leftmost_child  = &right;
    rightmost_child = &left;
  }

  // render the leftmost_child
  if(leftmost_child->is_node())    { leftmost_child ->_node     ->render_player_view(_player, omap); }
  else                             { leftmost_child ->_subsector->render_player_view(_player, omap); }
  
  // render the rightmost_child, only if bbox overlaps or if open space in between
  if(rightmost_child->_bbox.includes(v) || undrawn_columns_toward_child)
  {
    if(rightmost_child->is_node()) { rightmost_child->_node     ->render_player_view(_player, omap); }
    else                           { rightmost_child->_subsector->render_player_view(_player, omap); }
  }
}

