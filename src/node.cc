#include <string.h>
#include <stdio.h>

#include "node.h"

#define MAX(x,y) ((x)>(y) ? (x) : (y))
#define MIN(x,y) ((x)>(y) ? (x) : (y))

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

void node::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, overhead_map *omap) const
{
  node_child_link const *leftmost_child;
  node_child_link const *rightmost_child;
  vertex const *v;

  v = _player->get_map_position();
  if(partition.is_point_on_left(v))
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
  if(leftmost_child->is_node())    { leftmost_child ->_node     ->render_player_view(col_ranges, _projector, _player, omap); }
  else                             { leftmost_child ->_subsector->render_player_view(col_ranges, _projector, _player, omap); }
  
  // render the rightmost_child, only if bbox overlaps or if open space in between
  if(rightmost_child->_bbox.includes(v) || undrawn_columns_toward_bbox(&(rightmost_child->_bbox), col_ranges, _projector, _player))
  {
    if(rightmost_child->is_node()) { rightmost_child->_node     ->render_player_view(col_ranges, _projector, _player, omap); }
    else                           { rightmost_child->_subsector->render_player_view(col_ranges, _projector, _player, omap); }
  }
}

bool node::undrawn_columns_toward_bbox(bbox const *_bbox, column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  return false;
  vertex v[4];
  v[0].set_x(_bbox->x_left);  v[0].set_y(_bbox->y_top);
  v[1].set_x(_bbox->x_left);  v[1].set_y(_bbox->y_bottom);
  v[2].set_x(_bbox->x_right); v[2].set_y(_bbox->y_top);
  v[3].set_x(_bbox->x_right); v[3].set_y(_bbox->y_bottom);

  float angle[4], angle_left = 180, angle_right = -180;
  for(int i=0; i<4; i++)
  {
    angle[i] = _player->get_map_position()->angle_to_point(&v[i]) - _player->get_facing_angle();
    if     (angle[i] >  180) { angle[i] -= 360; }
    else if(angle[i] < -180) { angle[i] += 360; }
    angle_left  = MIN(angle_left,  angle[i]);
    angle_right = MAX(angle_right, angle[i]);
  }

  int x_left  = _projector->project_horiz_angle_to_x(angle_left);
  int x_right = _projector->project_horiz_angle_to_x(angle_right);

  return col_ranges->any_unclipped_columns_in_range(x_left, x_right);
}
