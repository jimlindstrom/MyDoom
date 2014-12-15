#include <stdio.h>
#include <math.h>

#include "common.h"
#include "player.h"
#include "episode_map.h"

player::player()
{
  // set initially idle
  is_turning_right = false;
  is_turning_left = false;
  is_moving_forward = false;
  is_moving_backward = false;
  is_strafing_right = false;
  is_strafing_left = false;

  floor_height = 0;
  rel_view_height = 35; // height above floor
}

player::~player()
{
}

void player::draw_overhead_map_marker(overhead_map *omap) const
{
  color_rgba red(255, 0, 0, 255);
  vertex v1, v2;

  v1.set_to(&map_position);
  v2.set_x(map_position.get_x() + 75*cos(facing_angle));
  v2.set_y(map_position.get_y() + 75*sin(facing_angle));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 20*cos(facing_angle-(M_PI/2.0)));
  v2.set_y(map_position.get_y() + 20*sin(facing_angle-(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 20*cos(facing_angle+(M_PI/2.0)));
  v2.set_y(map_position.get_y() + 20*sin(facing_angle+(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);
}

void player::move(episode_map const *_map)
{
  vertex new_position;

  new_position.set_to(&map_position);

  if(is_turning_right)
  {
    facing_angle -= DEG_TO_RAD(5);
    if(facing_angle < -M_PI) { facing_angle += 2.0*M_PI; }
  }
  if(is_turning_left)
  {
    facing_angle += DEG_TO_RAD(5);
    if(facing_angle > M_PI) { facing_angle -= 2.0*M_PI; }
  }
  if(is_moving_forward)
  {
    new_position.set_x(new_position.get_x() + (5*cos(facing_angle)));
    new_position.set_y(new_position.get_y() + (5*sin(facing_angle)));
  }
  if(is_moving_backward)
  {
    new_position.set_x(new_position.get_x() + (-5*cos(facing_angle)));
    new_position.set_y(new_position.get_y() + (-5*sin(facing_angle)));
  }
  if(is_strafing_right)
  {
    new_position.set_x(new_position.get_x() + (5*cos(facing_angle-(M_PI/2.0))));
    new_position.set_y(new_position.get_y() + (5*sin(facing_angle-(M_PI/2.0))));
  }
  if(is_strafing_left)
  {
    new_position.set_x(new_position.get_x() + (5*cos(facing_angle+(M_PI/2.0))));
    new_position.set_y(new_position.get_y() + (5*sin(facing_angle+(M_PI/2.0))));
  }

  if(_map->can_move(&map_position, &new_position, &floor_height))
  {
    map_position.set_to(&new_position);
  }
}
