#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include "mobile_map_object.h"

class projectile : public mobile_map_object
{
public:
  projectile(vertex const *_map_position, float _facing_angle, float _foot_height, map_obj_defn const *_defn, float shooter_radius);
  ~projectile();

  virtual void tick(game *_game, episode_map *_map); // override parent

private:
  void handle_hit_something_solid(game *_game, episode_map *_map);
};

#endif
