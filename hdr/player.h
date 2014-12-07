#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdint.h>

#include "overhead_map.h"

class player
{
public:
  player();
  ~player();

  void set_x(int16_t _x) { x = _x; }
  void set_y(int16_t _y) { y = _y; }
  void set_facing_angle(int16_t _facing_angle) { facing_angle = _facing_angle; }

  int16_t get_x(void) const { return x; }
  int16_t get_y(void) const { return y; }
  int16_t get_facing_angle(void) const { return facing_angle; }

  void draw_overhead_map(overhead_map *omap) const;

private:
  int16_t x, y;
  int16_t facing_angle;
};

#endif
