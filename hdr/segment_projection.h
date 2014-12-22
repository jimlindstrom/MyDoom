#ifndef __SEGMENT_PROJECTION_H
#define __SEGMENT_PROJECTION_H

#include "vertex.h"

class segment_projection
{
public:
  float delta_x(void) const { return x_r_c - x_l_c; }
  float delta_u(void) const { return u_r_c - u_l_c; }

  bool  is_visible;
  bool  store_clipping;          // in column_ranges
  bool  clip_floor, clip_ceiling;// in vis_planes

  float  ang_l,    ang_r;        // raw angles to left and right vertex
  vertex v_l_c,    v_r_c;        // vertex where left and right side end, or are clipped by horizontal FOV
  float  u_l_c,    u_r_c;        // percentage from l->r where v_l_c and v_r_c fall along the segent
  float  ang_l_c,  ang_r_c;      // angles to v_l_c and v_r_c
  float  x_l_c,    x_r_c;        // 2D projection to screen x of ang_l_c and ang_r_c
  float  dist_l_c, dist_r_c;     // map distance from player to left and right clipped edges
};

#endif
