#include <stdlib.h>
#include <stdio.h>

#include "patch_names_lump.h"
#include "texture_lump.h"
#include "wall_textures.h"
#include "wad_file.h"
#include "wall_texture.h"

static int32_t num_wall_textures = 0;
static wall_texture *wall_textures = NULL;

bool wall_textures_init(wad_file const *wad)
{
  wad_lump const *lump = NULL;
  texture_lump tlump;
  patch_names_lump pnames;

  lump = wad->find_lump_by_name("PNAMES");
  if(!lump)
  {
    printf("ERROR: Could not find TEXTURE1 lump\n");
    return false;
  }
  pnames.read_from_lump_data(lump->get_data());

  lump = wad->find_lump_by_name("TEXTURE1");
  if(!lump)
  {
    printf("ERROR: Could not find TEXTURE1 lump\n");
    return false;
  }
  if(!tlump.read_from_lump_data(lump->get_data()))
  {
    return false;
  }

  num_wall_textures = tlump.get_num_textures();
  wall_textures = new wall_texture[num_wall_textures];
  for(int i=0; i<num_wall_textures; i++)
  {
    if(!wall_textures[i].read_from_maptexture_data(tlump.get_maptexture_data(i), &pnames))
    {
      return false;
    }
  }

  //lump = wad->find_lump_by_name("TEXTURE2"); // FIXME??

  return true;
}

void wall_textures_destroy(void)
{
  if (wall_textures) { delete[] wall_textures; }
}

