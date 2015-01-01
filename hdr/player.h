#ifndef __PLAYER_H
#define __PLAYER_H

#include "overhead_map.h"
#include "weapon.h"
#include "mobile_map_object.h"

class player : public mobile_map_object
{
public:
  player(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn);
  ~player();

  void tick(game *_game, episode_map *_map); // override parent

  void draw_overhead_map_marker(overhead_map *omap) const;

  void set_weapon(int idx, weapon *w);
  void select_weapon(int idx);
  void draw_weapon(void) const;
  void fire_weapon(void);

private:
  void check_for_pickups(game *_game, episode_map *_map);
  void animate_weapon(void);
  void pickup_item(map_object *obj);

  weapon *weapons[NUM_WEAPONS];
  int selected_weapon_idx;
};

#endif
