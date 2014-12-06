#ifndef __REJECT_TABLE_H
#define __REJECT_TABLE_H

#include <stdint.h>

#include "wad_lump.h"

#define REJECT_TABLE_NUM_BYTES 4 // size on disk (in the lump)

class reject_table
{
public:
  reject_table();
  ~reject_table();

  bool read_from_lump(wad_lump const *lump, uint16_t num_sectors);

  bool is_visible(int sector_num1, int sector_num2) const;

private:
  uint16_t num_sectors;
  uint8_t *data;
};

#endif
