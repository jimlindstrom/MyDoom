#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include "mobile_map_object.h"

class projectile : public mobile_map_object
{
public:
  projectile(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn);
  ~projectile();

  void tick(game *_game, episode_map *_map); // override parent

private:
};

#endif
