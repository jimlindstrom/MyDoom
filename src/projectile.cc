#include <stdio.h>
#include <math.h>

#include "common.h"
#include "projectile.h"
#include "episode_map.h"
#include "game.h"

projectile::projectile(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn)
 : mobile_map_object(_map_position, _facing_angle, _defn)
{
  set_is_moving_forward(true); // projecitles are initially moving ahead
}

projectile::~projectile()
{
}

void projectile::tick(game *_game, episode_map *_map)
{
  vertex old_position;
  old_position.set_to(_camera.get_map_position());

  mobile_map_object::tick(_game, _map);

  switch(cur_meta_state_id)
  {
  case META_STATE_NORMAL:
    // when we run into something solid, explode
    if(old_position.distance_to_point(_camera.get_map_position()) < 1.0)
    {
      set_is_moving_forward(false);
      change_to_meta_state(META_STATE_DEATH);
    }
    break;

  case META_STATE_DEATH:
    // when we run out of frames in explosion state, delete the projectile
    if(!cur_state) 
    {
      _game->kill_map_object(this);
    }
    break;

  default:
    break;
  }
}
