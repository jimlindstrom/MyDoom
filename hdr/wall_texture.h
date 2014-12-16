#ifndef __WALL_TEXTURE_H
#define __WALL_TEXTURE_H

#include <stdint.h>

#include "color.h"
#include "patch.h"
#include "patch_names_lump.h"
#include "vis_planes.h"

class wall_patch
{
public:
  int16_t  originx;    // A short int defining the horizontal offset of the patch relative to the upper-left of the texture
  int16_t  originy;    // A short int defining the vertical offset of the patch relative to the upper-left of the texture
  uint16_t patch_num;  // A short int defining the patch number (as listed in PNAMES) to draw
  uint16_t stepdir;    // FIXME: ?
  uint16_t colormap;   // FIXME: ?
  patch const *_patch;
};

class wall_texture
{
public:
  wall_texture();
  ~wall_texture();

  bool read_from_maptexture_data(uint8_t const *data, patch_names_lump const *pnames);

  char const *get_name(void) { return &name[0]; }

  bool is_valid(void);

  void render(float ldx_l, float ldx_r, int ld_h, int x_l, int x_r, float yt_l, float yb_l, float yt_r, float yb_r,
              int16_t x_offset, int16_t y_offset, vis_planes *vp, vis_plane *floor, vis_plane *ceiling, bool clip_ceil, bool clip_floor) const;

private:
  char name[9]; // An ASCII string defining the name of the map texture. Only the characters A-Z (uppercase), 
                // 0-9, and [ ] - _ should be used in lump names. When a string is less than 8 bytes long, it 
                // should be null-padded to the eighth byte.
  uint32_t masked;  // A boolean (0=false, 1=true) defining ? (FIXME)
  uint16_t width;   // A short integer defining the total width of the map texture.
  uint16_t height;  // A short integer defining the total height of the map texture.
  uint16_t num_patches; // the number of map patches that make up this map texture
  wall_patch *patches;

  color_rgb *pixels;

  void pre_render(void);
};

#endif
