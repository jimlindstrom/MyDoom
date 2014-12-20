#ifndef __WALL_PROJECION_H
#define __WALL_PROJECION_H

#include <stdint.h>
#include "wall_texture.h"
#include "vis_planes.h"
#include "vis_plane.h"

class wall_projection
{
public:
  void clip_2sided_upper(void) const;
  void clip_2sided_lower(void) const;

  void render_1sided_mid(  void) const;
  void render_2sided_upper(void) const;
  void render_2sided_mid(  void) const;
  void render_2sided_lower(void) const;

  // filled in by segment::render
  float ldx_l, ldx_r;
  int x_l, x_r;
  float y0_l, dy_l, y0_r, dy_r;
  float dist_l, dist_r;
  uint16_t light_level;
  vis_planes *vp;
  vis_plane *floor, *ceiling;

  // filled in by linedef::render
  float yt_l, yb_l, yt_r, yb_r;
  int16_t ld_h;
  wall_texture const *tex;
  int16_t tx_offset, ty_offset;
};

#endif // #ifndef __WALL_PROJECION_H
