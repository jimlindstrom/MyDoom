#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdint.h>

#include "overhead_map.h"

class episode_map; // forward declaration

class player
{
public:
  player();
  ~player();

  void set_map_position(vertex const *v) { map_position.set_to(v); }
  void set_facing_angle(float _facing_angle) { facing_angle = _facing_angle; }

  vertex const *get_map_position(void) const { return &map_position; }
  float get_facing_angle(void) const { return facing_angle; }
  float get_view_height(void) const { return floor_height + rel_view_height; }

  void draw_overhead_map(overhead_map *omap) const;

  void set_is_turning_right(bool val) { is_turning_right = val; }
  void set_is_turning_left(bool val) { is_turning_left = val; }
  void set_is_moving_forward(bool val) { is_moving_forward = val; }
  void set_is_moving_backward(bool val) { is_moving_backward = val; }
  void set_is_strafing_right(bool val) { is_strafing_right = val; }
  void set_is_strafing_left(bool val) { is_strafing_left = val; }

  void move(episode_map const *_map);

private:
  vertex map_position;

  float  floor_height;    // floor height in cur sector
  float  rel_view_height; // head height (above floor)

  float  facing_angle;

  bool   is_turning_right;
  bool   is_turning_left;
  bool   is_moving_forward;
  bool   is_moving_backward;
  bool   is_strafing_right;
  bool   is_strafing_left;
};

#endif
