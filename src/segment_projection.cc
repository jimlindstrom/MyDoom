#include "common.h"
#include "segment_projection.h"

bool segment_projection::is_backface(void) const
{
  #define ANGLE_EPSILON (5.0) // just small enough to avoid weird near-infinity isssues (FIXME: make this be Z_MIN)
  return (ang_r > ang_l) || ((ang_l - ang_r) > DEG_TO_RAD(180.0 - ANGLE_EPSILON));
}

bool segment_projection::is_outside_fov(float horiz_fov_radius) const
{
  return ( ( (ang_l < -horiz_fov_radius) && (ang_r < -horiz_fov_radius) ) ||
           ( (ang_l >  horiz_fov_radius) && (ang_r >  horiz_fov_radius) ) );
}

float segment_projection::get_texture_x_offset(int16_t x)
{
  float t = u_l_c + (delta_u() * (x - x_l_c) / delta_x());
  return unclipped_offset + (unclipped_length * t);
}
