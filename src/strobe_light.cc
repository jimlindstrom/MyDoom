#include <stdlib.h>
#include <stdio.h>

#include "strobe_light.h"

strobe_light::strobe_light(sector *s, uint8_t _min_on_time, uint8_t _max_on_time, uint8_t _min_off_time, uint8_t _max_off_time)
{
  _sector = s;
  min_on_time = _min_on_time;
  max_on_time = _max_on_time;
  min_off_time = _min_off_time;
  max_off_time = _max_off_time;
  max_light_level = _sector->get_light_level();
  min_light_level = _sector->get_light_level() / 4.0;
  light_is_on = true;
  frames_left = min_on_time + (random() % (max_on_time-min_on_time));
}
  
void strobe_light::act()
{
  if(frames_left < 1)
  {
    if(light_is_on) // flipping from on to off
    {
      _sector->set_light_level(min_light_level);
      frames_left = min_off_time + (random() % (max_off_time-min_off_time));
    }
    else // flipping from on to off
    {
      _sector->set_light_level(max_light_level);
      frames_left = min_on_time + (random() % (max_on_time-min_on_time));
    }
    light_is_on = !light_is_on;
  }
  else
  {
    frames_left--;
  }
}

fast_strobe_light::fast_strobe_light(sector *s)
: strobe_light(s, 25,26, 25,26)
{
}

slow_strobe_light::slow_strobe_light(sector *s)
: strobe_light(s, 50,51, 50,51)
{
}

flickering_light::flickering_light(sector *s)
: strobe_light(s, 5,70, 1,10)
{
}

