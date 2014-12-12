#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdint.h>

#include "vertex.h"

class vector
{
public:
  vector() { }
  ~vector() { }

  vertex const *get_vertex_1(void) const { return vertex_1; }
  vertex const *get_vertex_2(void) const { return vertex_2; }

  void set_vertex_1(vertex const *v) { vertex_1 = v; }
  void set_vertex_2(vertex const *v) { vertex_2 = v; }

  bool is_vertical(void) const;
  bool is_horizontal(void) const;

  float get_slope(void) const;
  void get_slope_and_y_intercept(float *slope, float *y_intercept) const;

protected:
  vertex const *vertex_1;
  vertex const *vertex_2;
};

void vector_tests(void);

#endif
