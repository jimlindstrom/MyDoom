#ifndef __THINGS_H
#define __THINGS_H

#include "wad_file.h"
#include "thing.h"

bool things_init(wad_file const *wad);
void things_destroy(void);

#endif
