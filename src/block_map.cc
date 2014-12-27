#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "block_map.h"

/******************************************************************************
 *
 ******************************************************************************/

block_map_cell::block_map_cell(uint16_t _num_linedefs)
{
  num_linedefs = _num_linedefs;
  linedef_nums = new uint16_t[num_linedefs];
  linedefs = new linedef *[num_linedefs];
}

block_map_cell::~block_map_cell()
{
  delete[] linedef_nums;
  delete[] linedefs;
}

void block_map_cell::set_linedef_num(uint16_t n, uint16_t linedef_num)
{
  linedef_nums[n] = linedef_num;
}

uint16_t block_map_cell::get_linedef_num(uint16_t n) const
{
  return linedef_nums[n];
}

void block_map_cell::set_linedef(uint16_t n, linedef *_linedef)
{
  linedefs[n] = _linedef;
}

linedef const *block_map_cell::get_linedef(uint16_t n) const
{
  return linedefs[n];
}

/******************************************************************************
 *
 ******************************************************************************/

block_map::block_map()
{
  block_map_cells = NULL;
}

block_map::~block_map()
{
  if(block_map_cells)
  {
    for(int i=0; i<num_cols*num_rows; i++)
    {
      if(block_map_cells[i]) { delete block_map_cells[i]; }
    }
    delete[] block_map_cells;
  }
}

bool block_map::read_from_lump(wad_lump const *lump, uint16_t _num_sectors)
{
  uint8_t const *ptr;
  uint16_t *offsets;

  if(lump->get_num_bytes() < 8)
  {
    printf("ERROR: block map size: %d bytes\n", lump->get_num_bytes());
    return false;
  }

  // read the header
  ptr = lump->get_data();
  x_origin = *(( int16_t*)ptr); ptr+=2;
  y_origin = *(( int16_t*)ptr); ptr+=2;
  num_cols = *((uint16_t*)ptr); ptr+=2;
  num_rows = *((uint16_t*)ptr); ptr+=2;
  if(num_cols == 0) { printf("ERROR: block map # cols is 0\n"); return false; }
  if(num_rows == 0) { printf("ERROR: block map # rows is 0\n"); return false; }

  // read the offests
  offsets = new uint16_t[num_cols*num_rows];
  for(int i=0; i<num_cols*num_rows; i++)
  {
    offsets[i] = *((uint16_t*)ptr); ptr+=2;
  }

  // read each cell
  block_map_cells = new block_map_cell*[num_cols * num_rows];
  for(int i=0; i<num_cols*num_rows; i++)
  {
    // count the number of linedefs in the cell
    uint16_t cur_num_linedefs = 0;
    for(ptr = lump->get_data() + (2*offsets[i]); (*((uint16_t *)ptr)) != 0xffff; ptr += 2)
    {
      cur_num_linedefs++;
    }

    // then rewind and read them in
    block_map_cells[i] = new block_map_cell(cur_num_linedefs);
    ptr = lump->get_data() + (offsets[i]*2);
    for(int j=0; j<cur_num_linedefs; j++, ptr += 2)
    {
      uint16_t linedef_num = *((uint16_t *)ptr);
      if(linedef_num > 1500) // some relatively sane but high number
      {
        printf("WARNING: cell %d's %d'th linedef %d\n", i, j, linedef_num);
      }
      block_map_cells[i]->set_linedef_num(j, linedef_num);
    }
  }

  delete[] offsets;
  return true;
}
 
block_map_cell *block_map::get_cell_by_map_pos(vertex const *v) const
{
  if( (v->get_x() < x_origin) ||
      (v->get_y() < y_origin) ||
      (((v->get_x()-x_origin)/BM_CELL_SIZE) >= num_cols) ||
      (((v->get_y()-y_origin)/BM_CELL_SIZE) >= num_rows) )
  {
    return NULL;
  }

  return get_cell((v->get_x()-x_origin)/BM_CELL_SIZE, (v->get_y()-y_origin)/BM_CELL_SIZE);
}
