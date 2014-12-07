#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "episode_maps.h"
#include "episode_map.h"
#include "wad_file.h"

static int num_episode_maps;
static episode_map *episode_maps;

bool is_episode_name(char const *lump_name)
{
  return ( (lump_name[0] == 'E') &&
           (lump_name[1] >= '0') &&
           (lump_name[1] <= '9') &&
           (lump_name[2] == 'M') &&
           (lump_name[3] >= '0') &&
           (lump_name[3] <= '9') &&
           (lump_name[4] ==  0 ) );
}

bool episode_maps_init(wad_file const *wad)
{
  wad_lump const *lump = NULL;
  int i=0;

  num_episode_maps = 0;
  for(lump = wad->get_first_lump();
      lump;
      lump = wad->get_next_lump(lump))
  {
    if(is_episode_name(lump->get_name()))
    {
      num_episode_maps++;
    }
  }

  episode_maps = new episode_map[num_episode_maps];

  for(lump = wad->get_first_lump();
      lump;
      lump = wad->get_next_lump(lump))
  {
    if(is_episode_name(lump->get_name()))
    {
      episode_maps[i].read_from_lump(wad, lump);
      i++;
    }
  }

  return true;
}

void episode_maps_destroy(void)
{
  if(episode_maps) { delete[] episode_maps; }
}

episode_map const *episode_maps_get_by_name(char const *name)
{
  for(int i=0; i<num_episode_maps; i++)
  {
    if(strcmp(episode_maps[i].get_name(), name) == 0)
    {
      return &episode_maps[i];
    }
  }
  return NULL;
}
