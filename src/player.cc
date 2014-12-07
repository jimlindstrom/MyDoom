#include <math.h>

#include "player.h"

#define DEG_TO_RAD(d)  (d*M_PI/180.0) // FIXME: don't use this. slow.

player::player()
{
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

