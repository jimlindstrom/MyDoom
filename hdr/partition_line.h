#ifndef __PARTITION_LINE_H
#define __PARTITION_LINE_H

#include <stdint.h>

#include "vertex.h"

class partition_line
{
public:
  partition_line() { }
  partition_line(float _x, float _y, float _dx, float _dy) { x=_x; y=_y; dx=_dx; dy=_dy; }

  float x;
  float y;
  float dx;
  float dy;

  bool is_point_on_left(vertex const *v) const;
};

void partition_line_test(void);

#endif
