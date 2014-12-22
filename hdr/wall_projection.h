#ifndef __WALL_PROJECION_H
#define __WALL_PROJECION_H

#include <stdint.h>
#include "wall_texture.h"
#include "vis_planes.h"
#include "vis_plane.h"

class wall_projection
{
public:
  bool overlaps_range(int16_t x1, int16_t x2) const { return !((x1>x_r) || (x2<x_l)); }

  void project_vertically(projector const *_projector, player const *_player);

  void render_1sided(void) const;
  void render_2sided(void) const;

  // filled in by column_range_list::clip_segment
  wall_projection *next_range;
  int16_t x_l,    x_r;
  float   dist_l, dist_r;

  // filled in by segment::render
  float   ldx_l,  ldx_r;
  float   y0_l,   y0_r;
  float   dy_l,   dy_r;

  uint16_t light_level;
  vis_planes *vp;
  vis_plane *floor, *ceiling;
  bool clip_floor, clip_ceiling;

  // filled in by linedef::render
  bool is_one_sided;
  typedef struct {
    float yt_l, yt_r;
    float yb_l, yb_r;
    int16_t ld_h;
    wall_texture const *tex;
    int16_t tx_offset, ty_offset;
  } wall_part;
  wall_part upper, mid, lower;
};

#endif // #ifndef __WALL_PROJECION_H
