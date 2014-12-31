#ifndef __MAP_OBJECT_FACTORY_H
#define __MAP_OBJECT_FACTORY_H

#include "map_object.h"
#include "thing_instance.h"

class map_object_factory
{
public:
  static map_object *create(thing_instance const *ti);
};

#endif
