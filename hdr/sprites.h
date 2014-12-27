#ifndef __SPRITES_H
#define __SPRITES_H

#include "wad_file.h"
#include "sprite_animation.h"

bool sprites_init(wad_file const *wad);
void sprites_destroy(void);
sprite_animation *sprites_lookup_animation(char const *prefix);

#endif
