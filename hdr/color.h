#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

class color_rgb
{
public:
  color_rgb() { r=0; g=0; b=0; }
  color_rgb(int _r, int _g, int _b) { r=_r; g=_g; b=_b; }

  void set_to(color_rgb const *c) { r=c->r; g=c->g; b=c->b; }
  void darken_by(float pct) { r *= (1.0-pct); g *= (1.0-pct); b *= (1.0-pct); }

  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class color_rgba
{
public:
  color_rgba() { r=0; g=0; b=0; a=255; }
  color_rgba(int _r, int _g, int _b, int _a) { r=_r; g=_g; b=_b; a=_a; }

  void set_to(color_rgba const *c) { r=c->r; g=c->g; b=c->b; a=c->a; }
  void set_to(color_rgb const *c) { r=c->r; g=c->g; b=c->b; a=255; }

  void darken_by(float pct) { r *= (1.0-pct); g *= (1.0-pct); b *= (1.0-pct); }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

#endif
