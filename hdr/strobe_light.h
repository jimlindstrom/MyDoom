#ifndef __STROBE_LIGHT_H
#define __STROBE_LIGHT_H

#include "sector.h"
#include "actor.h"

class strobe_light : public actor
{
public:
  strobe_light(sector *s, uint8_t _min_on_time, uint8_t _max_on_time, uint8_t _min_off_time, uint8_t _max_off_time);
  
  void act();

private:
  sector *_sector;
  uint8_t max_on_time, min_on_time;
  uint8_t max_off_time, min_off_time;
  int16_t max_light_level, min_light_level;
  int16_t frames_left;
  bool light_is_on;
};

class fast_strobe_light : public strobe_light { public: fast_strobe_light(sector *s); };
class slow_strobe_light : public strobe_light { public: slow_strobe_light(sector *s); };
class flickering_light  : public strobe_light { public: flickering_light( sector *s); };

#endif
