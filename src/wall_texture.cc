#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "patches.h"
#include "wall_texture.h"

wall_texture::wall_texture()
{
  name[0] = NULL;
  patches = NULL;
}

wall_texture::~wall_texture()
{
  if(patches) { delete[] patches; }
}

bool wall_texture::read_from_maptexture_data(uint8_t const *data, patch_names_lump const *pnames)
{
  char const *patch_name;

  memcpy(name, data, 8);             data += 8;
  name[8] = NULL;

  masked         = *((uint32_t*)data); data += 4;
  width          = *((uint16_t*)data); data += 2;
  height         = *((uint16_t*)data); data += 2;
                                       data += 4; // ignored
  num_patches    = *((uint16_t*)data); data += 2;

  patches = new wall_patch[num_patches];
  for(int i=0; i<num_patches; i++)
  {
    patches[i].originx   = *((uint16_t*)data); data += 2;
    patches[i].originy   = *((uint16_t*)data); data += 2;
    patches[i].patch_num = *((uint16_t*)data); data += 2;
    patches[i].stepdir   = *((uint16_t*)data); data += 2;
    patches[i].colormap  = *((uint16_t*)data); data += 2;

    patch_name = pnames->get_patch_name_by_num(patches[i].patch_num);
    patches[i]._patch = patches_get_by_name(patch_name);
  }

  return is_valid();
}

bool wall_texture::is_valid(void)
{
  if(strlen(name)<1)
  {
    printf("ERROR: wall texture has no name\n");
    return false;
  }

  if(width<0 || width>2000 || height<0 || height>2000) // arbitrary guesses at sane values
  {
    printf("ERROR: wall texture crazy dimensions: %dx%d\n", width, height);
    return false;
  }

  return true;
}

