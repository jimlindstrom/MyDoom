#ifndef __PLAYER_H
#define __PLAYER_H

#include "camera.h"
#include "overhead_map.h"
#include "weapon.h"

class episode_map; // forward declaration

class player
{
public:
  player();
  ~player();

  camera const *get_camera(void) const { return &_camera; }
  void reset_camera(vertex const *pos, float ang) { _camera.set_map_position(pos); _camera.set_facing_angle(ang); }

  void draw_overhead_map_marker(overhead_map *omap) const;

  void set_weapon(int idx, weapon *w);
  void select_weapon(int idx);
  void draw_weapon(void) const;
  void fire_weapon(void);
  void animate_weapon(void);

  void set_is_turning_right(  bool val) { is_turning_right   = val; }
  void set_is_turning_left(   bool val) { is_turning_left    = val; }
  void set_is_moving_forward( bool val) { is_moving_forward  = val; }
  void set_is_moving_backward(bool val) { is_moving_backward = val; }
  void set_is_strafing_right( bool val) { is_strafing_right  = val; }
  void set_is_strafing_left(  bool val) { is_strafing_left   = val; }

  void move(episode_map const *_map);

private:
  camera _camera;
  float  floor_height;    // floor height in cur sector
  float  rel_view_height; // head height (above floor)

  bool   is_turning_right;
  bool   is_turning_left;
  bool   is_moving_forward;
  bool   is_moving_backward;
  bool   is_strafing_right;
  bool   is_strafing_left;

  weapon *weapons[NUM_WEAPONS];
  int selected_weapon_idx;
};

#endif
