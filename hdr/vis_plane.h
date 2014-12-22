#ifndef __VIS_PLANE_H
#define __VIS_PLANE_H

#include <stdint.h>

#include "flat.h"
#include "games.h"
#include "projector.h"
#include "camera.h"

#define VIS_PLANE_FLOOR_TYPE	1
#define VIS_PLANE_CEILING_TYPE	2

class vis_plane
{
public:
  vis_plane();
  ~vis_plane();

  void init(int16_t _height, flat const *_tex, uint16_t _light_level);

  bool matches(int16_t _height, flat const *_tex, uint16_t _light_level);

  bool can_be_extended_to(int16_t new_x_l, int16_t new_x_r);
  void extend_to(int16_t new_x_l, int16_t new_x_r);

  int16_t get_height() const { return height; }
  flat const *get_tex(void) const { return tex; }
  uint16_t get_light_level(void) const { return light_level; }
  int16_t get_x_l(void) const { return x_l; }
  int16_t get_x_r(void) const { return x_r; }
  int16_t get_y_t(int x) const { return y_t[x]; }
  int16_t get_y_b(int x) const { return y_b[x]; }

  void update_clip(int16_t x, int16_t yb, int16_t yt);

  void draw(camera const *_camera);

private:
  int16_t height;
  flat const *tex;
  uint16_t light_level;
  int16_t x_l, x_r;
  int16_t y_t[MAX_SCREEN_WIDTH];
  int16_t y_b[MAX_SCREEN_WIDTH];
  
};

#endif
