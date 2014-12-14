#include <stdlib.h>
#include <stdio.h>

#include "palettes.h"
#include "patches.h"
#include "wad_file.h"
#include "patch.h"

static int32_t num_patches = 0;
static patch *patches = NULL;

bool patches_init(wad_file const *wad)
{
  wad_lump const *patch_lump = NULL;
  int i;

  num_patches = 0;
  for(patch_lump = wad->get_next_lump(wad->find_lump_by_name("P_START"));
      patch_lump && !patch_lump->is_named("P_END");
      patch_lump = wad->get_next_lump(patch_lump))
  {
    if (patch_lump->get_num_bytes() > 0)
    {
      num_patches++;
    }
  }

  patches = new patch[num_patches];

  i=0;
  for(patch_lump = wad->get_next_lump(wad->find_lump_by_name("P_START"));
      patch_lump && !patch_lump->is_named("P_END");
      patch_lump = wad->get_next_lump(patch_lump))
  {
    if (patch_lump->get_num_bytes() > 0)
    {
      patches[i].set_name(patch_lump->get_name());

      patches[i].set_from_lump_data(patch_lump->get_data());
      i++;
    }
  }

  //patches[0].print_html_file("/tmp/patch0.html", palettes_get(0));

  return true;
}

void patches_destroy(void)
{
  if (patches) { delete[] patches; }
}

patch const *patches_get_by_name(char const *name)
{
  for(int i=0; i<num_patches; i++)
  {
    if(strcmp(patches[i].get_name(), name) == 0)
    {
      return &patches[i];
    }
  }

  return NULL;
}
