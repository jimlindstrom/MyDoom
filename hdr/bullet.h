#ifndef __BULLET_H
#define __BULLET_H

#include "projectile.h"

class bullet : public projectile
{
public:
  bullet(vertex const *_map_position, float _facing_angle, float _height, map_obj_defn const *_defn, float shooter_radius);
  ~bullet();

  void tick(game *_game, episode_map *_map); // override parent
};

#endif
