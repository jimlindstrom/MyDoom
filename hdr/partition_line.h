#ifndef __PARTITION_LINE_H
#define __PARTITION_LINE_H

#include <stdint.h>

#include "vertex.h"

class partition_line
{
public:
  partition_line() { }
  partition_line(int _x, int _y, int _dx, int _dy) { x=_x; y=_y; dx=_dx; dy=_dy; }

  int16_t x;
  int16_t y;
  int16_t dx;
  int16_t dy;

  bool is_point_on_left(vertex const *v) const;
};

void partition_line_test(void);

#endif
