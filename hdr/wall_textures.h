#ifndef __WALL_TEXTURES_H
#define __WALL_TEXTURES_H

#include "wad_file.h"
#include "wall_texture.h"

bool wall_textures_init(wad_file const *wad);
void wall_textures_destroy(void);
wall_texture const *wall_textures_get_by_name(char const *name);

#endif
