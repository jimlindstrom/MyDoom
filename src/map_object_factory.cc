#include "map_object_factory.h"
#include "player.h"

map_object *map_object_factory::create(thing_instance const *ti)
{
  map_obj_defn const **defn;

  for(defn = map_obj_being_defns; *defn; defn++)
  {
    if((*defn)->doomednum == ti->get_thing_type())
    {
      return new map_object(ti->get_map_position(), ti->get_facing_angle(), *defn);
    }
  }

  for(defn = map_obj_inert_defns; *defn; defn++)
  {
    if((*defn)->doomednum == ti->get_thing_type())
    {
      return new map_object(ti->get_map_position(), ti->get_facing_angle(), *defn);
    }
  }

  return NULL;
}
