#include <string.h>
#include <stdio.h>
#include <math.h>

#include "node.h"
#include "common.h"

static uint16_t next_node_num = 0; // for debug printing

node::node()
{
}

node::~node()
{
}

bool node::read_from_lump_data(uint8_t const *lump_data)
{
  node_num             = next_node_num++; // for debug printing

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

  printf("node %d\n", node_num);
  printf("  partition: (%.1f,%.1f) + (%.1f,%.1f)\n", partition.x,  partition.y, partition.dx, partition.dy);
  v = _player->get_map_position();
  if(partition.is_point_on_left(v))
  {
    printf("  player is on left\n");
    leftmost_child  = &left;
    rightmost_child = &right;
  }
  else
  {
    printf("  player is on right\n");
    leftmost_child  = &right;
    rightmost_child = &left;
  }

  // render the leftmost_child
  if(leftmost_child->is_node())    { leftmost_child ->_node     ->render_player_view(col_ranges, _projector, _player, omap); }
  else                             { leftmost_child ->_subsector->render_player_view(col_ranges, _projector, _player, omap); }
  
  // render the rightmost_child, only if bbox overlaps or if open space in between
  printf("node %d (far side)\n", node_num);
  bool right_bbox_includes_v = rightmost_child->_bbox.includes(v);
  bool undrawn_cols_toward_right_bbox = undrawn_columns_toward_bbox(&(rightmost_child->_bbox), col_ranges, _projector, _player);
  if(right_bbox_includes_v || undrawn_cols_toward_right_bbox) // FIXME: by doing these inline, we could skip the 2nd test
  {
    if(right_bbox_includes_v)
    { 
      printf("  far bbox [%.1f..%.1f, %.1f..%.1f] includes v\n", 
             rightmost_child->_bbox.x_left,
             rightmost_child->_bbox.x_right,
             rightmost_child->_bbox.y_top,
             rightmost_child->_bbox.y_bottom); 
    }
    if(undrawn_cols_toward_right_bbox)
    { 
      printf("  undrawn cols toward far bbox\n"); 
    }
    if(rightmost_child->is_node()) { rightmost_child->_node     ->render_player_view(col_ranges, _projector, _player, omap); }
    else                           { rightmost_child->_subsector->render_player_view(col_ranges, _projector, _player, omap); }
  }
}

bool node::undrawn_columns_toward_bbox(bbox const *_bbox, column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  vertex v[4];
  v[0].set_x(_bbox->x_left);  v[0].set_y(_bbox->y_top);
  v[1].set_x(_bbox->x_left);  v[1].set_y(_bbox->y_bottom);
  v[2].set_x(_bbox->x_right); v[2].set_y(_bbox->y_top);
  v[3].set_x(_bbox->x_right); v[3].set_y(_bbox->y_bottom);

  float angle[4], angle_left = -M_PI, angle_right = M_PI;
  printf("  angles: [");
  for(int i=0; i<4; i++)
  {
    angle[i] = _player->get_map_position()->angle_to_point(&v[i]) - _player->get_facing_angle();
    if     (angle[i] >  M_PI) { angle[i] -= 2.0*M_PI; }
    else if(angle[i] < -M_PI) { angle[i] += 2.0*M_PI; }
    printf("%.1f%s", RAD_TO_DEG(angle[i]), (i==3)?"":",");
    angle_left  = MAX(angle_left,  angle[i]);
    angle_right = MIN(angle_right, angle[i]);
  }
  printf("] -> [%.1f,%.1f]\n", RAD_TO_DEG(angle_left), RAD_TO_DEG(angle_right));

  int x_left  = _projector->project_horiz_angle_to_x(angle_left);
  int x_right = _projector->project_horiz_angle_to_x(angle_right);

  return col_ranges->any_unclipped_columns_in_range(x_left, x_right);
}
