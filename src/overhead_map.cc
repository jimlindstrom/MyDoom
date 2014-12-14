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

void overhead_map::darken_background(void)
{
  color_rgba bg; bg.r = 40; bg.g = 40; bg.b = 40; bg.a = 187;

  for(int x=map_bbox->x_left; x<=map_bbox->x_right; x++)
  {
    for(int y=map_bbox->y_top; y<=map_bbox->y_bottom; y++)
    {
      frame_buf_overlay_pixel(x, y, &bg);
    }
  }
}

void overhead_map::draw_bbox(void)
{
  color_rgba white; white.r = 255; white.g = 255; white.b = 255; white.a = 255;

  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_top,    map_bbox->x_right, map_bbox->y_top,    &white);
  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_bottom, map_bbox->x_right, map_bbox->y_bottom, &white);
  frame_buf_draw_line(map_bbox->x_left,  map_bbox->y_top,    map_bbox->x_left,  map_bbox->y_bottom, &white);
  frame_buf_draw_line(map_bbox->x_right, map_bbox->y_top,    map_bbox->x_right, map_bbox->y_bottom, &white);
}

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
