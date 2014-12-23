#ifndef __FLATS_H
#define __FLATS_H

#include "wad_file.h"
#include "flat.h"

bool flats_init(wad_file const *wad);
void flats_destroy(void);
void flats_animate(void);
flat_animation const *flats_find_by_name(char const *name);

#endif
