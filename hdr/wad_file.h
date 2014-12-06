#ifndef __WAD_FILE_H
#define __WAD_FILE_H

#include <stdint.h>
#include <stdlib.h>

#include "wad_header.h"
#include "wad_lump.h"

#define NUM_REQUIRED_LUMP_NAMES 4
static char const *required_lump_names[NUM_REQUIRED_LUMP_NAMES] =
{
  "F_START",
  "F_END",
  "S_START",
  "S_END",
};

class wad_file
{
public:
  wad_file();
  ~wad_file();

  bool read(char const *filename);

  wad_lump const *get_first_lump(void) const;
  wad_lump const *find_lump_by_name(char const *name) const;
  wad_lump const *get_next_lump(wad_lump const *cur_lump) const;

private:
  wad_header header;

  int num_lumps;
  wad_lump *lumps;

  bool read_lumps(FILE *f);
  bool has_required_lumps();
};

#endif // #ifndef __WAD_FILE_H
