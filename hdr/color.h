#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

class color_rgba
{
public:
  color_rgba() { r=0; g=0; b=0; a=255; }
  color_rgba(int _r, int _g, int _b, int _a) { r=_r; g=_g; b=_b; a=_a; }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

class color_rgb
{
public:
  color_rgb() { r=0; g=0; b=0; }
  color_rgb(int _r, int _g, int _b) { r=_r; g=_g; b=_b; }

  uint8_t r;
  uint8_t g;
  uint8_t b;
};

#endif
