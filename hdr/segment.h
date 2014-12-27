#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <stdint.h>

#include "vertex.h"
#include "vector.h"

class segment
{
public:
  segment() ;
  segment(vertex const *vl, vertex const *vr);
  ~segment();

  vertex const *get_vertex_l(void) const { return vertex_l; }
  vertex const *get_vertex_r(void) const { return vertex_r; }

  void set_vertex_l(vertex const *v) { vertex_l = v; }
  void set_vertex_r(vertex const *v) { vertex_r = v; }
  void add_vertex_l(vertex       *v) { vertex_l = _vertex_l = v; } // will be garbage-collected later
  void add_vertex_r(vertex       *v) { vertex_r = _vertex_r = v; } // will be garbage-collected later

  bool is_vertical(void) const;
  bool is_horizontal(void) const;

  float get_length(void) const;
  float get_slope(void) const;
  void get_slope_and_y_intercept(float *slope, float *y_intercept) const;

  bool get_intersection_with_vector(vector const *vec, vertex *ver, float *u) const; // u=0 -> left vertex, u=1 -> right vertex
  bool get_intersection_with_segment(segment const *s2, vertex *ver, float *u1, float *u2) const;

  void clip_to_vectors(vector const *l_l_delta, vector const *l_r_delta,
                       vertex *v_l_c, vertex *v_r_c,
                       float *u_l_c, float *u_r_c) const;

  // subtract new_origin, then rotate by -new_ang. caller delete's returned seg
  segment *transform_origin(vertex const *new_origin, float new_ang) const; 

protected:
  vertex const *vertex_r;
  vertex const *vertex_l;
  vertex *_vertex_r; // to be garbage-collected upon delete
  vertex *_vertex_l; // to be garbage-collected upon delete
};

void segment_tests(void);

#endif
