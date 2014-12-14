#ifndef __SIDEDEF_H
#define __SIDEDEF_H

#include <stdint.h>

#include "sector.h"
#include "wall_texture.h"

#define SIDEDEF_NUM_BYTES 30 // size on disk (in the lump)

class sidedef
{
public:
  sidedef();
  ~sidedef();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_x_offset(void) const { return x_offset; };
  int16_t get_y_offset(void) const { return y_offset; };
  char const *get_upper_texture_name(void) const { return upper_texture_name; };
  char const *get_lower_texture_name(void) const { return lower_texture_name; };
  char const *get_mid_texture_name(void) const { return mid_texture_name; };
  uint16_t get_sector_num(void) const { return sector_num; }

  void set_sector(sector const *s) { _sector = s; }
  void set_upper_texture(wall_texture const *t) { upper_texture = t; }
  void set_lower_texture(wall_texture const *t) { lower_texture = t; }
  void set_mid_texture(wall_texture const *t) { mid_texture = t; }

  sector const *get_sector(void) const { return _sector; }

  void render(float ldx_l, float ldx_r, int ld_h, int x_l, int x_r, float yt_l, float yb_l, float yt_r, float yb_r) const;

private:
  int16_t  x_offset;
  int16_t  y_offset;
  char     upper_texture_name[9]; // 8 + NULL
  char     lower_texture_name[9]; // 8 + NULL
  char     mid_texture_name[9];   // 8 + NULL
  uint16_t sector_num;            // Sector number this sidedef 'faces'

  sector const *_sector;
  wall_texture const *upper_texture;
  wall_texture const *lower_texture;
  wall_texture const *mid_texture;
};

#endif
