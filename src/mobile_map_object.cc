#include "common.h"
#include "mobile_map_object.h"
#include "episode_map.h"
#include "game.h"

#define CAMERA_TURN_INCREMENT DEG_TO_RAD(3)

mobile_map_object::mobile_map_object(vertex const *_map_position, float _facing_angle, map_obj_defn const *_defn)
 : map_object(_map_position, _facing_angle, _defn)
{
  // set initially idle
  is_turning_right   = false;
  is_turning_left    = false;
  is_moving_forward  = false;
  is_moving_backward = false;
  is_strafing_right  = false;
  is_strafing_left   = false;
}

mobile_map_object::~mobile_map_object()
{
}

void mobile_map_object::tick(game *_game, episode_map *_map)
{
  map_object::tick(_game, _map);
  try_to_move(_game, _map);
}

void mobile_map_object::try_to_move(game *_game, episode_map *_map)
{
  if(is_turning_right) { _camera.turn_right(CAMERA_TURN_INCREMENT); }
  if(is_turning_left)  { _camera.turn_left( CAMERA_TURN_INCREMENT); }

  vertex new_position;
  new_position.set_to(_camera.get_map_position());
  if(is_moving_forward)
  {
    new_position.set_x(new_position.get_x() + ( defn->velocity*cos(_camera.get_facing_angle())));
    new_position.set_y(new_position.get_y() + ( defn->velocity*sin(_camera.get_facing_angle())));
  }
  if(is_moving_backward)
  {
    new_position.set_x(new_position.get_x() + (-defn->velocity*cos(_camera.get_facing_angle())));
    new_position.set_y(new_position.get_y() + (-defn->velocity*sin(_camera.get_facing_angle())));
  }
  if(is_strafing_right)
  {
    new_position.set_x(new_position.get_x() + ( defn->velocity*cos(_camera.get_facing_angle() - (M_PI/2.0))));
    new_position.set_y(new_position.get_y() + ( defn->velocity*sin(_camera.get_facing_angle() - (M_PI/2.0))));
  }
  if(is_strafing_left)
  {
    new_position.set_x(new_position.get_x() + ( defn->velocity*cos(_camera.get_facing_angle() + (M_PI/2.0))));
    new_position.set_y(new_position.get_y() + ( defn->velocity*sin(_camera.get_facing_angle() + (M_PI/2.0))));
  }

  if((is_moving_forward || is_moving_backward || is_strafing_right || is_strafing_left) &&
     _map->can_move(_camera.get_map_position(), &new_position, defn->radius))
  {
    bool blocked_by_solid_map_obj = false;
    for(int i=0; !blocked_by_solid_map_obj && i<_game->get_num_map_objects(); i++)
    {
      map_object *obj = _game->get_nth_map_object(i);
      if(obj == this) { continue; } // skip self

      float ctr_to_ctr_dist = new_position.distance_to_point(obj->get_camera()->get_map_position());
      float sum_of_radii    = defn->radius + obj->get_defn()->radius;
      bool  would_overlap   = (ctr_to_ctr_dist <= sum_of_radii);
      if(would_overlap && (obj->get_defn()->flags & MF_SOLID))
      {
        blocked_by_solid_map_obj = true;
      }
    }

    if(!blocked_by_solid_map_obj)
    {
      _camera.set_map_position(&new_position);

      // if stepping up, immediately bump the user up to new floor height. If 
      // flat/down, map_object::tick() will apply gravity next time.
      floor_height = _map->get_floor_height_at(_camera.get_map_position()); 
      if(foot_height < floor_height)
      {
        foot_height = floor_height;
        _camera.set_view_height(foot_height + defn->height);
      }
    }
  }
}

