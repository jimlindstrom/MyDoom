#ifndef __CLIPPED_SEGMENT_PROJECION_H
#define __CLIPPED_SEGMENT_PROJECION_H

#include <stdint.h>
#include "wall_texture.h"
#include "vis_planes.h"
#include "vis_plane.h"

class clipped_segment_projection
{
public:
  bool overlaps_range(int16_t x1, int16_t x2) const { return !((x1>x_r) || (x2<x_l)); }
  int16_t get_sprite_clip_top(int16_t x) const { return sprite_clip_top[x]; }
  int16_t get_sprite_clip_bot(int16_t x)  const{ return sprite_clip_bot[x]; }

  void project_vertically(camera const *_camera);

  void render(vis_planes *vp, vis_plane *floor, vis_plane *ceiling);

// FIXME: make these private

  // filled in by clipped_segment_projections::clip_segment()
  clipped_segment_projection *next_csp; // FIXME: this should be in a container class like node_child_link
  int16_t x_l,    x_r;     // screen x
  float   dist_l, dist_r;  // distance from player to edge (overhead perspective. ignores z)

  // filled in by segment::render()
  float   ldx_l,  ldx_r;   // linedef x val (aka texture x value at left and right)

  // filled in by segment::render()
  float view_ang;          // in radians
  uint16_t light_level;    // 0..255
  bool clip_floor, clip_ceiling;

  // filled in by linedef::set_textures()
  bool is_one_sided;

  class wall_part {
  public:
    int16_t get_dz(void) const { return z_t - z_b; }

    // filled in by linedef::set_z_values()
    int16_t z_t,  z_b;       // z (distance from bottom of level up to bottom,top of wall

    // filled in by project_vertically()
    float   yt_l, yt_r;      // screen y at top of wall
    float   yb_l, yb_r;      // screen y at bottom of wall

    // filled in by linedef::set_textures()
    wall_texture const *tex;
    int16_t tx_offset, ty_offset; // texture offset, for pixel (0,0) of wall segment
  };
  wall_part upper, mid, lower;

private:
  // filled in when rendering
  int16_t sprite_clip_top[MAX_SCREEN_WIDTH]; // FIXME: gratuitous. dynamically allocate for (x_r-x_l+1)
  int16_t sprite_clip_bot[MAX_SCREEN_WIDTH]; // FIXME: gratuitous. dynamically allocate for (x_r-x_l+1)

  void render_1sided(vis_planes *vp, vis_plane *floor, vis_plane *ceiling);
  void render_2sided(vis_planes *vp, vis_plane *floor, vis_plane *ceiling);
};

#endif // #ifndef __CLIPPED_SEGMENT_PROJECION_H
