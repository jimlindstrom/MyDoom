#include <stdlib.h>
#include <string.h>

#include "texture_lump.h"

texture_lump::texture_lump()
{
  offsets = NULL;
  maptexture_data = NULL;
}

texture_lump::~texture_lump()
{
  if(offsets) 
  {
    delete[] offsets;
  }
  if(maptexture_data)
  {
    for(int i=0; i<num_textures; i++)
    {
      delete[] maptexture_data[i];
    }
    delete[] maptexture_data;
  }
}

bool texture_lump::read_from_lump_data(uint8_t const *lump_data)
{
  num_textures = *((uint32_t *)lump_data); lump_data += 4;

  offsets = new uint32_t[num_textures];
  for(int i=0; i<num_textures; i++)
  {
    offsets[i] = *((uint32_t *)lump_data); lump_data += 4;
  }

  maptexture_data = new uint8_t*[num_textures];
  for(int i=0; i<num_textures; i++)
  {
    int num_patches = *((uint16_t*)(lump_data+20));
    int maptexture_num_bytes = 22+(10*num_patches);
    maptexture_data[i] = new uint8_t[maptexture_num_bytes];
    memcpy(maptexture_data[i], lump_data, maptexture_num_bytes);
    lump_data += maptexture_num_bytes;
  }

  return true;
}

