#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdint.h>

#include "overhead_map.h"

class player
{
public:
  player();
  ~player();

  void set_map_position(vertex const *v) { map_position.set_to(v); }
  void set_facing_angle(float _facing_angle) { facing_angle = _facing_angle; }
  void set_view_height(float h) { view_height = h; }

  vertex const *get_map_position(void) const { return &map_position; }
  float get_facing_angle(void) const { return facing_angle; }
  float get_view_height(void) const { return view_height; } 

  void draw_overhead_map(overhead_map *omap) const;

  void set_is_turning_right(bool val) { is_turning_right = val; }
  void set_is_turning_left(bool val) { is_turning_left = val; }
  void set_is_moving_forward(bool val) { is_moving_forward = val; }
  void set_is_moving_backward(bool val) { is_moving_backward = val; }
  void set_is_strafing_right(bool val) { is_strafing_right = val; }
  void set_is_strafing_left(bool val) { is_strafing_left = val; }

  void move(void);

private:
  vertex map_position;
  float  view_height; // map z
  float  facing_angle;

  bool   is_turning_right;
  bool   is_turning_left;
  bool   is_moving_forward;
  bool   is_moving_backward;
  bool   is_strafing_right;
  bool   is_strafing_left;
};

#endif
