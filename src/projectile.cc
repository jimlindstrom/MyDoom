#include <stdio.h>
#include <math.h>

#include "common.h"
#include "projectile.h"
#include "episode_map.h"
#include "game.h"

#define DIST_EPSILON 1.0

projectile::projectile(vertex const *_map_position, float _facing_angle, float _foot_height, map_obj_defn const *_defn, float shooter_radius)
 : mobile_map_object(_map_position, _facing_angle, _foot_height, _defn)
{
  set_is_moving_forward(true); // projecitles are initially moving ahead

  // don't blow up the shooter: start the missile just beyond its radius
  float initial_dist = shooter_radius + defn->radius + DIST_EPSILON;
  vertex new_position;
  new_position.set_x(_camera.get_map_position()->get_x() + ( initial_dist*cos(_camera.get_facing_angle())));
  new_position.set_y(_camera.get_map_position()->get_y() + ( initial_dist*sin(_camera.get_facing_angle())));
  _camera.set_map_position(&new_position);
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
      handle_hit_something_solid(_game, _map);
    }
    break;

  case META_STATE_DEATH:
    // when we run out of frames in explosion state, delete the projectile
    if(!cur_state) 
    {
      _game->kill_map_object(this); // FIXME: it'd be better to return false and have the caller do this.
    }
    break;

  default:
    break;
  }
}

void projectile::handle_hit_something_solid(game *_game, episode_map *_map)
{
  // stop moving forward
  set_is_moving_forward(false);

  // figure out where we WOULD have been if we hadn't hit something 
  vertex new_position; 
  new_position.set_to(_camera.get_map_position());
  new_position.set_x(new_position.get_x() + ( defn->velocity*cos(_camera.get_facing_angle())));
  new_position.set_y(new_position.get_y() + ( defn->velocity*sin(_camera.get_facing_angle())));

  // see if we hit any map objects. (maybe not. we could have just hit a wall.)
  for(int i=0; i<_game->get_num_map_objects(); i++)
  {
    map_object *obj = _game->get_nth_map_object(i);
    if(obj == this) { continue; } // skip self

    float ctr_to_ctr_dist = new_position.distance_to_point(obj->get_camera()->get_map_position());
    float sum_of_radii    = defn->radius + obj->get_defn()->radius;
    bool  would_overlap   = (ctr_to_ctr_dist <= sum_of_radii);
    if(would_overlap && (obj->get_defn()->flags & MF_SHOOTABLE))
    {
      obj->handle_hit_by_projectile(_game, defn->damage);
    }
  }

  change_to_meta_state(META_STATE_DEATH);
}
