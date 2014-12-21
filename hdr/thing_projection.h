#ifndef __THING_PROJECTION_H
#define __THING_PROJECTION_H

#include <stdint.h>

#include "column_range.h"
#include "sprite.h"
#include "games.h"

class thing_projection
{
public:
  thing_projection()
  {
    for(int i=0; i<MAX_SCREEN_WIDTH; i++) { cliptop[i] = MAX_SCREEN_HEIGHT; clipbot[i]=-1; }
  }
  bool is_backface(void) const { return (angle_r > angle_l); }
  bool is_outside_fov(void) const { return ( ( (angle_l < -horiz_fov_radius) ||
                                               (angle_l >  horiz_fov_radius) ) &&
                                             ( (angle_r < -horiz_fov_radius) ||
                                               (angle_r >  horiz_fov_radius) ) ); }
  void clip(column_range_list *col_ranges);
  void draw(void);

  bool is_visible;
  float dist_l, dist_r;
  float angle_l, angle_r;
  float sprite_angle;
  float horiz_fov_radius;
  float x_l, x_r;
  float y_t, y_b;

  int16_t x_l_c;
  int16_t x_r_c;
  int16_t y_t_c;
  int16_t y_b_c;

  sprite const *_sprite;

  int16_t cliptop[MAX_SCREEN_WIDTH];
  int16_t clipbot[MAX_SCREEN_WIDTH];
};

#endif
