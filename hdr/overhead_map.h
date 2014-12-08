#ifndef __OVERHEAD_MAP_H
#define __OVERHEAD_MAP_H

#include "color.h"
#include "vertex.h"
#include "bbox.h"

class overhead_map
{
public:
  overhead_map();
  ~overhead_map();

  void set_bbox(bbox const *map_bbox);
  void set_scale(float scale);
  void translate_origin(int dx, int dy);

  void draw_bbox(void);
  void draw_line(vertex const *v1, vertex const *v2, color_rgba const *c);

private:
  bbox const *map_bbox;
  float map_scale;
  int map_dx, map_dy;

  int scale_and_translate_x(int x);
  int scale_and_translate_y(int y);
};

#endif
