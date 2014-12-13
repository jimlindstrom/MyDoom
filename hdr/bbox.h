#ifndef __BBOX_H
#define __BBOX_H

#include <stdint.h>

#include "vertex.h"

class bbox
{
public:
  bbox() { y_top=0; y_bottom=0; x_left=0; x_right=0; }
  bbox(float yt, float yb, float xl, float xr) { y_top=yt; y_bottom=yb; x_left=xl; x_right=xr; }

  bool includes(vertex const *v) const;

  float y_top;
  float y_bottom;
  float x_left;
  float x_right;
};

#endif
