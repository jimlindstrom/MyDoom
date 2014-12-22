#ifndef __CAMERA_H
#define __CAMERA_H

#include "common.h"
#include "vertex.h"

class camera
{
public:
  void set_map_position(vertex const *v)     { map_position.set_to(v);       }
  void set_facing_angle(float _facing_angle) { facing_angle = _facing_angle; }
  void set_view_height( float _view_height)  { view_height  = _view_height;  }

  void turn_left( float rad) { facing_angle = NORMALIZE_ANGLE(facing_angle + DEG_TO_RAD(3)); }
  void turn_right(float rad) { facing_angle = NORMALIZE_ANGLE(facing_angle - DEG_TO_RAD(3)); }

  vertex const *get_map_position(void) const { return &map_position; }
  float         get_facing_angle(void) const { return facing_angle;  }
  float         get_view_height( void) const { return view_height;   }

private:
  vertex map_position; // map x,y
  float  view_height;  // map z (abs. not rel to cur sector)
  float  facing_angle; // radians
};

#endif
