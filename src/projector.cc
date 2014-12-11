#include <math.h>
#include <stdio.h>
#include "projector.h"

projector::projector()
{
}

void projector::set_screen_size(uint16_t _screen_width, uint16_t _screen_height)
{
  screen_width = _screen_width;
  screen_height = _screen_height;

  x_proj_scale = (screen_width/2.0) / tan(get_horiz_fov_radius()*M_PI/180.0);
}

int16_t projector::get_horiz_fov_radius() const
{
  return 60;
} 

int16_t projector::project_horiz_angle_to_x(float angle) const
{
  return ((0.5*screen_width) + (x_proj_scale*tan(angle*M_PI/180.0)));
}


