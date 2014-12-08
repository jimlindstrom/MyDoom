#ifndef __BBOX_H
#define __BBOX_H

#include <stdint.h>

#include "vertex.h"

class bbox
{
public:
  bbox() { y_top=0; y_bottom=0; x_left=0; x_right=0; }
  bbox(int yt, int yb, int xl, int xr) { y_top=yt; y_bottom=yb; x_left=xl; x_right=xr; }

  bool includes(vertex const *v) const;

  int16_t y_top;
  int16_t y_bottom;
  int16_t x_left;
  int16_t x_right;
};

#endif
