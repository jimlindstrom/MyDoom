#ifndef __THING_FACTORY_H
#define __THING_FACTORY_H

#include "thing.h"

class thing_factory
{
public:
  static thing *create(thing_instance const *ti);
};

#endif
