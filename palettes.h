#ifndef __PALETTES_H
#define __PALETTES_H

#include "wad_file.h"
#include "palette.h"

bool palettes_init(wad_file const *wad);
palette const *palettes_get(int idx);
void palettes_destroy(void);

#endif
