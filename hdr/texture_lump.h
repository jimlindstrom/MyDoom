#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <stdint.h>

class texture_lump
{
public:
  texture_lump();
  ~texture_lump();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint32_t get_num_textures() const { return num_textures; }
  uint32_t get_offset(int n) const { return offsets[n]; }
  uint8_t const *get_maptexture_data(int n) const { return maptexture_data[n]; }

private:

  uint32_t num_textures;
  uint32_t *offsets;
  uint8_t **maptexture_data;
};

#endif
