#include <string.h>
#include <stdio.h>
#include <math.h>

#include "node.h"
#include "common.h"

//#define DEBUG_PRINTING
#include "debug.h"

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

void node::render_player_view(column_range_list *col_ranges, 
                              projector const *_projector, player const *_player, 
                              vis_planes *vp, 
                              thing *things, int16_t num_things, vis_things *vt) const
{
  node_child_link const *closer_child;
  node_child_link const *farther_child;
  vertex const *v;

  debug_printf("node %d\n", node_num);
  debug_printf("  partition: (%.1f,%.1f) + (%.1f,%.1f)\n", partition.x,  partition.y, partition.dx, partition.dy);
  debug_printf("  children: ");
  if(left .is_node()) { debug_printf("node %d, ",      left ._node->node_num);           }
  else                { debug_printf("subsector %d, ", left ._subsector->subsector_num); }
  if(right.is_node()) { debug_printf("node %d\n",      right._node->node_num);           }
  else                { debug_printf("subsector %d\n", right._subsector->subsector_num); }
  v = _player->get_map_position();
  if(partition.is_point_on_left(v))
  {
    debug_printf("  player is on left\n");
    closer_child  = &left;
    farther_child = &right;
  }
  else
  {
    debug_printf("  player is on right\n");
    closer_child  = &right;
    farther_child = &left;
  }

  // render the closer_child
  if(closer_child->is_node())    { closer_child ->_node     ->render_player_view(col_ranges, _projector, _player, vp, things, num_things, vt); }
  else                           { closer_child ->_subsector->render_player_view(col_ranges, _projector, _player, vp, things, num_things, vt); }
  
  // render the farther_child, only if bbox overlaps or if open space in between
  debug_printf("node %d (far side)\n", node_num);
  bool right_bbox_includes_v = farther_child->_bbox.includes(v);
  bool undrawn_cols_toward_right_bbox = undrawn_columns_toward_bbox(&(farther_child->_bbox), col_ranges, _projector, _player);
  if(right_bbox_includes_v || undrawn_cols_toward_right_bbox) // FIXME: by doing these inline, we could skip the 2nd test
  {
    if(right_bbox_includes_v)
    { 
      debug_printf("  far bbox [%.1f..%.1f, %.1f..%.1f] includes v\n", 
             farther_child->_bbox.x_left, farther_child->_bbox.x_right,
             farther_child->_bbox.y_top,  farther_child->_bbox.y_bottom); 
    }
    if(undrawn_cols_toward_right_bbox)
    { 
      debug_printf("  undrawn cols toward far bbox\n"); 
    }
    if(farther_child->is_node()) { farther_child->_node     ->render_player_view(col_ranges, _projector, _player, vp, things, num_things, vt); }
    else                         { farther_child->_subsector->render_player_view(col_ranges, _projector, _player, vp, things, num_things, vt); }
  }
  else { debug_printf("  skipping.\n"); }
}

bool node::undrawn_columns_toward_bbox(bbox const *_bbox, column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  vertex v[4];
  v[0].set_xy(_bbox->x_left,  _bbox->y_top   );
  v[1].set_xy(_bbox->x_left,  _bbox->y_bottom);
  v[2].set_xy(_bbox->x_right, _bbox->y_top   );
  v[3].set_xy(_bbox->x_right, _bbox->y_bottom);

  float angle[4], angle_left = -M_PI, angle_right = M_PI;
  debug_printf("  angles: [");
  for(int i=0; i<4; i++)
  {
    angle[i] = NORMALIZE_ANGLE(_player->get_map_position()->angle_to_point(&v[i]) - _player->get_facing_angle());
    debug_printf("%.1f%s", RAD_TO_DEG(angle[i]), (i==3)?"":",");
    angle_left  = MAX(angle_left,  angle[i]);
    angle_right = MIN(angle_right, angle[i]);
  }
  angle_left  = _projector->clip_horiz_angle_to_fov(angle_left );
  angle_right = _projector->clip_horiz_angle_to_fov(angle_right);
  debug_printf("] -> [%.1f,%.1f]\n", RAD_TO_DEG(angle_left), RAD_TO_DEG(angle_right));

  int16_t x_left  = _projector->project_horiz_angle_to_x(angle_left);
  int16_t x_right = _projector->project_horiz_angle_to_x(angle_right);
  debug_printf("  testing holes in x: [%d, %d]\n", x_left, x_right);

  return col_ranges->any_unclipped_columns_in_range(x_left, x_right);
}

subsector const *node::get_subsector_containing(vertex const *v) const
{
  node_child_link const *closer_child;

  if(partition.is_point_on_left(v))
  {
    closer_child  = &left;
  }
  else
  {
    closer_child  = &right;
  }

  if(closer_child->is_node())
  {
    return closer_child->_node->get_subsector_containing(v);
  }
  else
  {
    return closer_child ->_subsector; 
  }
}
