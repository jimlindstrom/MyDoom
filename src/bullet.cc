#include "bullet.h"
#include "map_obj_defn_inerts.h"
#include "map_obj_defn_projectiles.h"
#include "game.h"

bullet::bullet(vertex const *_map_position, float _facing_angle, float _height, map_obj_defn const *_defn, float shooter_radius)
 : projectile(_map_position, _facing_angle, _height, _defn, shooter_radius)
{
}

bullet::~bullet()
{
}

void bullet::tick(game *_game, episode_map *_map)
{
  map_obj_meta_state_id  old_meta_state_id = cur_meta_state_id;
  vertex old_map_position;
  float old_facing_angle, old_view_height;

  old_map_position.set_to(_camera.get_map_position());
  old_facing_angle      = _camera.get_facing_angle();
  old_view_height       = _camera.get_view_height();

  // travel at lightspeed, until you run into something (which changes cur_state)
  while(cur_state && (cur_meta_state_id == old_meta_state_id))
  {
    old_map_position.set_to(_camera.get_map_position());
    old_facing_angle      = _camera.get_facing_angle();
    old_view_height       = _camera.get_view_height();
    projectile::tick(_game, _map);
  }

  map_object *puff = new map_object(&old_map_position, 
                                    old_facing_angle, 
                                    old_view_height-20, 
                                    &puff_defn);
  _game->spawn_map_object(puff);
}

