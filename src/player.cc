#include <stdio.h>
#include <math.h>

#include "player.h"

#define DEG_TO_RAD(d)  (d*M_PI/180.0) // FIXME: don't use this. slow.

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
  v2.set_x(map_position.get_x() + 40*cos(DEG_TO_RAD(facing_angle)));
  v2.set_y(map_position.get_y() + 40*sin(DEG_TO_RAD(facing_angle)));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 10*cos(DEG_TO_RAD(facing_angle-90)));
  v2.set_y(map_position.get_y() + 10*sin(DEG_TO_RAD(facing_angle-90)));
  omap->draw_line(&v1, &v2, &red);

  v2.set_x(map_position.get_x() + 10*cos(DEG_TO_RAD(facing_angle+90)));
  v2.set_y(map_position.get_y() + 10*sin(DEG_TO_RAD(facing_angle+90)));
  omap->draw_line(&v1, &v2, &red);
}

void player::move(void)
{
  vertex n;

  if(is_turning_right)
  {
    facing_angle -= 5;
    if(facing_angle < -180)
    {
      facing_angle += 360;
    }
    printf("facing angle: %d\n", facing_angle);
  }
  if(is_turning_left)
  {
    facing_angle += 5;
    if(facing_angle > 180)
    {
      facing_angle -= 360;
    }
    printf("facing angle: %d\n", facing_angle);
  }
  if(is_moving_forward)
  {
    n.set_x(5*cos(DEG_TO_RAD(facing_angle)));
    n.set_y(5*sin(DEG_TO_RAD(facing_angle)));
    map_position.translate(&n);
  }
  if(is_moving_backward)
  {
    n.set_x(-5*cos(DEG_TO_RAD(facing_angle)));
    n.set_y(-5*sin(DEG_TO_RAD(facing_angle)));
    map_position.translate(&n);
  }
  if(is_strafing_right)
  {
    n.set_x(5*cos(DEG_TO_RAD(facing_angle-90)));
    n.set_y(5*sin(DEG_TO_RAD(facing_angle-90)));
    map_position.translate(&n);
  }
  if(is_strafing_left)
  {
    n.set_x(5*cos(DEG_TO_RAD(facing_angle+90)));
    n.set_y(5*sin(DEG_TO_RAD(facing_angle+90)));
    map_position.translate(&n);
  }
}
