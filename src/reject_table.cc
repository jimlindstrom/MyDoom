#include <string.h>
#include <stdio.h>

#include "reject_table.h"

reject_table::reject_table()
{
  data = NULL;
}

reject_table::~reject_table()
{
  if(data) { delete[] data; }
}

bool reject_table::read_from_lump(wad_lump const *lump, uint16_t _num_sectors)
{
  num_sectors = _num_sectors;
  data = new uint8_t[lump->get_num_bytes()];
  memcpy(data, lump->get_data(), lump->get_num_bytes());

  return true;
}

bool reject_table::is_visible(int sector_num1, int sector_num2) const
{
  printf("WARNING: not implemented reject_table::is_visible()\n");
  // FIXME: see http://doom.wikia.com/wiki/Reject
  return true;
}

