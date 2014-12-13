#include <stdio.h>
#include <math.h>

#include "common.h"
#include "player.h"

player::player()
{
  // set initially idle
  is_turning_right = false;
  is_turning_left = false;
  is_moving_forward = false;
  is_moving_backward = false;
  is_strafing_right = false;
  is_strafing_left = false;
}

player::~player()
{
}

void player::draw_overhead_map(overhead_map *omap) const
{
  color_rgba red(255, 0, 0, 255);
  vertex v1, v2;

  v1.set_to(&map_position);
  v2.set_x(map_position.get_x() + 40*cos(facing_angle));
  v2.set_y(map_position.get_y() + 40*sin(facing_angle));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 10*cos(facing_angle-(M_PI/2.0)));
  v2.set_y(map_position.get_y() + 10*sin(facing_angle-(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 10*cos(facing_angle+(M_PI/2.0)));
  v2.set_y(map_position.get_y() + 10*sin(facing_angle+(M_PI/2.0)));
  omap->draw_line(&v1, &v2, &red);
}

void player::move(void)
{
  vertex n;

  if(is_turning_right)
  {
    facing_angle -= DEG_TO_RAD(5);
    if(facing_angle < -M_PI)
    {
      facing_angle += 2.0*M_PI;
    }
  }
  if(is_turning_left)
  {
    facing_angle += DEG_TO_RAD(5);
    if(facing_angle > M_PI)
    {
      facing_angle -= 2.0*M_PI;
    }
  }
  if(is_moving_forward)
  {
    n.set_x(5*cos(facing_angle));
    n.set_y(5*sin(facing_angle));
    map_position.translate(&n);
  }
  if(is_moving_backward)
  {
    n.set_x(-5*cos(facing_angle));
    n.set_y(-5*sin(facing_angle));
    map_position.translate(&n);
  }
  if(is_strafing_right)
  {
    n.set_x(5*cos(facing_angle-(M_PI/2.0)));
    n.set_y(5*sin(facing_angle-(M_PI/2.0)));
    map_position.translate(&n);
  }
  if(is_strafing_left)
  {
    n.set_x(5*cos(facing_angle+(M_PI/2.0)));
    n.set_y(5*sin(facing_angle+(M_PI/2.0)));
    map_position.translate(&n);
  }
}
