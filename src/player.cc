#include <stdio.h>
#include <math.h>

#include "common.h"
#include "player.h"
#include "episode_map.h"
#include "game.h"

player::player(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn)
 : mobile_map_object(_map_position, _facing_angle, 0, _defn)
{
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

void player::tick(game *_game, episode_map *_map)
{
  mobile_map_object::tick(_game, _map);
  check_for_pickups(_game, _map);
  animate_weapon();
}

void player::check_for_pickups(game *_game, episode_map *_map)
{
  int num_objs_to_delete = 0;
  map_object *objs_to_delete[500];

  for(int i=0; i<_game->get_num_map_objects(); i++)
  {
    map_object *obj = _game->get_nth_map_object(i);
    if(obj == this) { continue; } // skip self

    if(overlaps(obj)) // FIXME: only need to do this if in same/adjacent block
    {
      if(obj->get_defn()->flags & MF_SPECIAL)
      {
        pickup_item(obj);
        objs_to_delete[num_objs_to_delete++] = obj;
      }
      if(obj->get_defn()->flags & MF_PICKUP)
      {
        pickup_item(obj);
        objs_to_delete[num_objs_to_delete++] = obj;
      }
    }
  }

  for(int i=0; i<num_objs_to_delete; i++)
  {
    _game->kill_map_object(objs_to_delete[i]);
  }
}

void player::pickup_item(map_object *obj)
{
  // FIXME: not implemented
  // SEE: P_TouchSpecialThing (p_inter.c, line 339 of 918)
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
  //if(weapons[selected_weapon_idx] &&
  //   weapons[selected_weapon_idx]->get_ammo() > 0)
  //{
    weapons[selected_weapon_idx]->handle_event(EVENT_WEAPON_FIRE);
  //}
}

void player::animate_weapon(void)
{
  if(weapons[selected_weapon_idx])
  {
    weapons[selected_weapon_idx]->tick();
  }
}

