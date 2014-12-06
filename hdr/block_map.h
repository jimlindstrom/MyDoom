#ifndef __BLOCK_MAP_H
#define __BLOCK_MAP_H

#include <stdint.h>

#include "wad_lump.h"

#define BLOCK_MAP_NUM_BYTES 4 // size on disk (in the lump)

class block_map
{
public:
  block_map();
  ~block_map();

  bool read_from_lump(wad_lump const *lump, uint16_t num_sectors);

private:
  int16_t x_origin;
  int16_t y_origin;
  int16_t num_cols;
  int16_t num_rows;
};

#endif
