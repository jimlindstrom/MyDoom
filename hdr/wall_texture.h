#ifndef __WALL_TEXTURE_H
#define __WALL_TEXTURE_H

#include <stdint.h>

class wall_patch
{
public:
  uint16_t originx;  // A short int defining the horizontal offset of the patch relative to the upper-left of the texture
  uint16_t originy;  // A short int defining the vertical offset of the patch relative to the upper-left of the texture
  uint16_t patch;    // A short int defining the patch number (as listed in PNAMES) to draw
  uint16_t stepdir;  // ?
  uint16_t colormap; // ?
};

class wall_texture
{
public:
  wall_texture();
  ~wall_texture();

  bool read_from_maptexture_data(uint8_t const *data);

  bool is_valid(void);

private:
  char name[9]; // An ASCII string defining the name of the map texture. Only the characters A-Z (uppercase), 
                // 0-9, and [ ] - _ should be used in lump names. When a string is less than 8 bytes long, it 
                // should be null-padded to the eighth byte.
  uint32_t masked;  // A boolean (0=false, 1=true) defining ?
  uint16_t width;   // A short integer defining the total width of the map texture.
  uint16_t height;  // A short integer defining the total height of the map texture.
  uint16_t num_patches; // the number of map patches that make up this map texture
  wall_patch *patches;
};

#endif
