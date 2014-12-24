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
  char lumpname[50];
  patch_names_lump pnames;

  // read in all the patch names
  lump = wad->find_lump_by_name("PNAMES");
  if(!lump) { printf("ERROR: Could not find PNAMES lump\n"); return false; }
  pnames.read_from_lump_data(lump->get_data());

  num_wall_textures = 0;

  // read in each texture lump, just to count the # of textures
  for(int j=1; j<10; j++)
  {
    sprintf(lumpname, "TEXTURE%d", j);
    if((lump = wad->find_lump_by_name(lumpname)))
    {
      printf("reading textures from %s\n", lumpname);
      if(!tlump.read_from_lump_data(lump->get_data())) { return false; }
      num_wall_textures += tlump.get_num_textures();
    }
  }

  // alloc mem
  printf("allocating room for %d textures\n", num_wall_textures);
  wall_textures = new wall_texture[num_wall_textures];

  // now loop through again and read the textures
  int lump_idx = 0;
  for(int j=1; j<10; j++)
  {
    sprintf(lumpname, "TEXTURE%d", j);
    if((lump = wad->find_lump_by_name(lumpname)))
    {
      if(!tlump.read_from_lump_data(lump->get_data())) { return false; }
      for(int k=0; k<tlump.get_num_textures(); k++, lump_idx++)
      {
        if(!wall_textures[lump_idx].read_from_maptexture_data(tlump.get_maptexture_data(k), &pnames))
        {
          return false;
        }
      }
    }
  }

  return true;
}

void wall_textures_destroy(void)
{
  if (wall_textures) { delete[] wall_textures; }
}

wall_texture const *wall_textures_get_by_name(char const *name)
{
  for(int i=0; i<num_wall_textures; i++)
  {
    if(strcmp(wall_textures[i].get_name(), name) == 0)
    {
      return &wall_textures[i];
    }
  }

  return NULL;
}

