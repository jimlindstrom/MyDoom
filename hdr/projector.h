#ifndef __PROJECTOR_H
#define __PROJECTOR_H

#include <stdint.h>

class projector
{
public:
  projector();

  void set_screen_size(uint16_t _screen_width, uint16_t _screen_height);

  int16_t get_horiz_fov_radius() const;
  int16_t project_horiz_angle_to_x(float angle) const;

private:
  uint16_t screen_width;
  uint16_t screen_height;
  float x_proj_scale;
};

#endif
