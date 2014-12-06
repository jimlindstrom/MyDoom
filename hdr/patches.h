#ifndef __PATCHES_H
#define __PATCHES_H

#include "wad_file.h"
#include "patch.h"

bool patches_init(wad_file const *wad);
void patches_destroy(void);

patch const *patches_get_by_name(char const *name);

#endif
