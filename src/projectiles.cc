#include "projectiles.h"

/******************************************************************************
 * PLASMA
 ******************************************************************************/

thing_definition plasma_defn = { -1, "", "", -1, "PLSS", "A", "", ""};

plasma::plasma(vertex const *_pos, float _facing_angle)
{
  map_position.set_to(_pos);
  // FIXME: what about z?
  facing_angle = _facing_angle;
  frame_ctr    = 0;
  thing_type   = -1;
  _is_deaf     = true;
  defn         = &plasma_defn;
  animation    = sprites_lookup_animation(defn->sprite_prefix);
}

void plasma::tick(void)
{
  vertex new_position;
  new_position.set_x(map_position.get_x() + (4*cos(facing_angle)));
  new_position.set_y(map_position.get_y() + (4*sin(facing_angle)));
  map_position.set_to(&new_position);
}

/******************************************************************************
 * MISSILE
 ******************************************************************************/

thing_definition missile_defn = { -1, "", "", -1, "MISL", "A", "", ""};

missile::missile(vertex const *_pos, float _facing_angle)
{
  map_position.set_to(_pos);
  // FIXME: what about z?
  facing_angle = _facing_angle;
  frame_ctr    = 0;
  thing_type   = -1;
  _is_deaf     = true;
  defn         = &missile_defn;
  animation    = sprites_lookup_animation("PLSS");
  animation    = sprites_lookup_animation(defn->sprite_prefix);
}

void missile::tick(void)
{
  vertex new_position;
  new_position.set_x(map_position.get_x() + (4*cos(facing_angle)));
  new_position.set_y(map_position.get_y() + (4*sin(facing_angle)));
  map_position.set_to(&new_position);
}
