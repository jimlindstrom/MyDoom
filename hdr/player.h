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
  void set_facing_angle(int16_t _facing_angle) { facing_angle = _facing_angle; }

  vertex const *get_map_position(void) const { return &map_position; }
  int16_t get_facing_angle(void) const { return facing_angle; }

  void draw_overhead_map(overhead_map *omap) const;

private:
  vertex  map_position;
  int16_t facing_angle;
};

#endif
