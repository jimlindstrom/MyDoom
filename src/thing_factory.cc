#include "thing_factory.h"

thing *thing_factory::create(thing_instance const *ti)
{
  switch(ti->get_thing_type())
  {
  default:
    return new thing(ti);
  }

  return NULL;
}
