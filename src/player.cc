#include <stdio.h>
#include <math.h>

#include "common.h"
#include "player.h"
#include "episode_map.h"

#define CAMERA_TURN_INCREMENT DEG_TO_RAD(3)

player::player()
{
  // set initially idle
  is_turning_right   = false;
  is_turning_left    = false;
  is_moving_forward  = false;
  is_moving_backward = false;
  is_strafing_right  = false;
  is_strafing_left   = false;

  // initialize camera
  floor_height    = 0;  // floor height (abs)
  rel_view_height = 35; // eyeball height (rel) above floor
  _camera.set_view_height(floor_height + rel_view_height);

  selected_weapon_idx = 0;
}

player::~player()
{
}

void player::draw_overhead_map_marker(overhead_map *omap) const
{
  color_rgba red(255, 0, 0, 255);
  vertex v1, v2;

  v1.set_to(_camera.get_map_position());
  v2.set_x(_camera.get_map_position()->get_x() + 75*cos(_camera.get_facing_angle()));
  v2.set_y(_camera.get_map_position()->get_y() + 75*sin(_camera.get_facing_angle()));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(_camera.get_map_position()->get_x() + 20*cos(_camera.get_facing_angle()-(M_PI/2.0)));
  v2.set_y(_camera.get_map_position()->get_y() + 20*sin(_camera.get_facing_angle()-(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(_camera.get_map_position()->get_x() + 20*cos(_camera.get_facing_angle()+(M_PI/2.0)));
  v2.set_y(_camera.get_map_position()->get_y() + 20*sin(_camera.get_facing_angle()+(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);
}

void player::move(episode_map const *_map)
{
  if(is_turning_right) { _camera.turn_right(CAMERA_TURN_INCREMENT); }
  if(is_turning_left)  { _camera.turn_left( CAMERA_TURN_INCREMENT); }

  vertex new_position;
  new_position.set_to(_camera.get_map_position());
  if(is_moving_forward)
  {
    new_position.set_x(new_position.get_x() + (6*cos(_camera.get_facing_angle())));
    new_position.set_y(new_position.get_y() + (6*sin(_camera.get_facing_angle())));
  }
  if(is_moving_backward)
  {
    new_position.set_x(new_position.get_x() + (-6*cos(_camera.get_facing_angle())));
    new_position.set_y(new_position.get_y() + (-6*sin(_camera.get_facing_angle())));
  }
  if(is_strafing_right)
  {
    new_position.set_x(new_position.get_x() + (6*cos(_camera.get_facing_angle()-(M_PI/2.0))));
    new_position.set_y(new_position.get_y() + (6*sin(_camera.get_facing_angle()-(M_PI/2.0))));
  }
  if(is_strafing_left)
  {
    new_position.set_x(new_position.get_x() + (6*cos(_camera.get_facing_angle()+(M_PI/2.0))));
    new_position.set_y(new_position.get_y() + (6*sin(_camera.get_facing_angle()+(M_PI/2.0))));
  }

  if(_map->can_move(_camera.get_map_position(), &new_position, &floor_height))
  {
    _camera.set_map_position(&new_position);
    _camera.set_view_height(floor_height + rel_view_height);
  }
}

void player::set_weapon(int idx, weapon *w)
{
  weapons[idx] = w;
}

void player::select_weapon(int idx)
{
  selected_weapon_idx = idx;
}

void player::draw_weapon(void) const
{
  if(weapons[selected_weapon_idx]) { weapons[selected_weapon_idx]->draw(); }
}

void player::fire_weapon(void)
{
  if(weapons[selected_weapon_idx] &&
     weapons[selected_weapon_idx]->get_ammo() > 0)
  {
    weapons[selected_weapon_idx]->set_state(WEAPON_STATE_ATTACK);
  }
}

