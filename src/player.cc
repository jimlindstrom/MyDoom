#include "player.h"

player::player()
{
}

player::~player()
{
}

void player::draw_overhead_map(overhead_map *omap) const
{
  color_rgba red(255,   0,   0, 255);
  vertex v1, v2;

  v1.set_x(x-10);
  v1.set_y(y   );
  v2.set_x(x+10);
  v2.set_y(y   );
  omap->draw_line(&v1, &v2, &red);

  v1.set_x(x   );
  v1.set_y(y-10);
  v2.set_x(x   );
  v2.set_y(y+10);
  omap->draw_line(&v1, &v2, &red);
}

