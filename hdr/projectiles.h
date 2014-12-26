#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include "thing.h"

class plasma : public thing
{
public:
  plasma(vertex const *_pos, float _facing_angle);
  ~plasma() { }

  void tick(void);
};

class missile : public thing
{
public:
  missile(vertex const *_pos, float _facing_angle);
  ~missile() { }

  void tick(void);
};

#endif
