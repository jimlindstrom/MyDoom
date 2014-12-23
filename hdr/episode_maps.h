#ifndef __EPISODE_MAPS_H
#define __EPISODE_MAPS_H

#include "wad_file.h"
#include "episode_map.h"

bool episode_maps_init(wad_file const *wad);
void episode_maps_destroy(void);
episode_map *episode_maps_get_by_name(char const *name);

#endif
