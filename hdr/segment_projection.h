#ifndef __SEGMENT_PROJECTION_H
#define __SEGMENT_PROJECTION_H

#include "vertex.h"

class segment_projection
{
public:
  bool is_backface(void) const;
  bool is_outside_fov(float horiz_fov_radius) const;

  float delta_x(void) const { return x_r_c - x_l_c; }
  float delta_u(void) const { return u_r_c - u_l_c; }

  bool is_zero_width(void) const { return (delta_x() < 0.0); }

  float get_texture_x_offset(int16_t x);

// FIXME: Make these private
  float unclipped_length;        // the length of the original, unclipped wad_segment
  float unclipped_offset;        // dist from the start of the line segment to the start of the unclipped wad_segment

  bool  is_opaque;               // true if solid wall or closed door.
  bool  clip_floor, clip_ceiling;// in vis_planes

  float  ang_l,    ang_r;        // raw angles to left and right vertex
  vertex v_l_c,    v_r_c;        // vertex where left and right side end, or are clipped by horizontal FOV
  float  u_l_c,    u_r_c;        // percentage from l->r where v_l_c and v_r_c fall along the segent
  float  ang_l_c,  ang_r_c;      // angles to v_l_c and v_r_c
  float  x_l_c,    x_r_c;        // 2D projection to screen x of ang_l_c and ang_r_c
  float  dist_l_c, dist_r_c;     // map distance from player to left and right clipped edges
};

#endif
