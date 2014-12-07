#include <stdio.h>

#include "overhead_map.h"
#include "frame_buf.h"

overhead_map::overhead_map()
{
}

overhead_map::~overhead_map()
{
}

void overhead_map::set_bbox(bbox const *box)
{
  map_bbox = box;
}

void overhead_map::set_scale(float scale)
{
  map_scale = scale;
}

void overhead_map::translate_origin(int dx, int dy)
{
  map_dx = dx;
  map_dy = dy;
}

void overhead_map::draw_bbox(void)
{
  color_rgba white; white.r = 255; white.g = 255; white.b = 255; white.a = 255;

  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_top,    map_bbox->x_right, map_bbox->y_top,    &white);
  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_bottom, map_bbox->x_right, map_bbox->y_bottom, &white);
  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_top,    map_bbox->x_left,  map_bbox->y_bottom, &white);
  frame_buf_draw_line(map_bbox->x_right, map_bbox->y_top,    map_bbox->x_right, map_bbox->y_bottom, &white);
}

/*void overhead_map::draw_partition_line(partition_line const *partition, color_rgba const *c)
{
  int x1 = scale_and_translate_x(partition->x);
  int y1 = scale_and_translate_y(partition->y);
  int x2 = scale_and_translate_x(partition->x + partition->dx);
  int y2 = scale_and_translate_y(partition->y + partition->dy);

  frame_buf_draw_line(x1, y1, x2, y2, c);
}

void overhead_map::draw_node_bbox(bbox const *node_bbox, color_rgba const *c)
{
  frame_buf_draw_line(scale_and_translate_x(node_bbox->x_left),  scale_and_translate_y(node_bbox->y_top),
                      scale_and_translate_x(node_bbox->x_right), scale_and_translate_y(node_bbox->y_top),
                      c);
  frame_buf_draw_line(scale_and_translate_x(node_bbox->x_left),  scale_and_translate_y(node_bbox->y_bottom), 
                      scale_and_translate_x(node_bbox->x_right), scale_and_translate_y(node_bbox->y_bottom), 
                      c);
  frame_buf_draw_line(scale_and_translate_x(node_bbox->x_left),  scale_and_translate_y(node_bbox->y_top),    
                      scale_and_translate_x(node_bbox->x_left),  scale_and_translate_y(node_bbox->y_bottom), 
                      c);
  frame_buf_draw_line(scale_and_translate_x(node_bbox->x_right), scale_and_translate_y(node_bbox->y_top),    
                      scale_and_translate_x(node_bbox->x_right), scale_and_translate_y(node_bbox->y_bottom), 
                      c);
}*/

int overhead_map::scale_and_translate_x(int x)
{
  return (map_bbox->x_left + map_bbox->x_right)/2.0 + (x * map_scale) + map_dx;
}

int overhead_map::scale_and_translate_y(int y)
{
  return (map_bbox->y_top + map_bbox->y_bottom)/2.0 + (y * map_scale) + map_dy;
}

void overhead_map::draw_line(vertex const *v1, vertex const *v2, color_rgba const *c)
{
  int x1 = scale_and_translate_x(v1->get_x());
  int y1 = scale_and_translate_y(v1->get_y());
  int x2 = scale_and_translate_x(v2->get_x());
  int y2 = scale_and_translate_y(v2->get_y());

  frame_buf_draw_line(x1, y1, x2, y2, c);
}
