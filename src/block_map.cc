#include <string.h>
#include <stdio.h>

#include "block_map.h"

block_map::block_map()
{
}

block_map::~block_map()
{
}

bool block_map::read_from_lump(wad_lump const *lump, uint16_t _num_sectors)
{
  uint8_t const *ptr;
  uint16_t *offsets;

  printf("WARNING: block_map::read_from_lump() not fully implemented\n");
  return true;
  // FIXME: http://doom.wikia.com/wiki/Blockmap

  ptr = lump->get_data();

  x_origin = *((int16_t*)ptr); ptr += 2;
  y_origin = *((int16_t*)ptr); ptr += 2;
  num_cols = *((int16_t*)ptr); ptr += 2;
  num_rows = *((int16_t*)ptr); ptr += 2;

  offsets = new uint16_t[num_cols*num_rows];
  for(int i=0; i<num_cols*num_rows; i++)
  {
    offsets[i] = *((int16_t*)ptr); ptr += 2;
  }

  delete[] offsets;
  return true;
}

