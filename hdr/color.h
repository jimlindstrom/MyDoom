#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

class color_rgba
{
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

class color_rgb
{
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

#endif
