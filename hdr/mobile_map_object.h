#ifndef __MOBILE_MAP_OBJECT_H
#define __MOBILE_MAP_OBJECT_H

#include "map_object.h"

class mobile_map_object : public map_object
{
public:
  mobile_map_object(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn);
  virtual ~mobile_map_object();

  virtual void tick(game *_game, episode_map *_map);

  void set_is_turning_right(  bool val) { is_turning_right   = val; }
  void set_is_turning_left(   bool val) { is_turning_left    = val; }
  void set_is_moving_forward( bool val) { is_moving_forward  = val; }
  void set_is_moving_backward(bool val) { is_moving_backward = val; }
  void set_is_strafing_right( bool val) { is_strafing_right  = val; }
  void set_is_strafing_left(  bool val) { is_strafing_left   = val; }

protected:
  bool   is_turning_right;
  bool   is_turning_left;
  bool   is_moving_forward;
  bool   is_moving_backward;
  bool   is_strafing_right;
  bool   is_strafing_left;

  // FIXME: move this up a level?
  float  floor_height;    // floor height in cur sector
};


#endif
