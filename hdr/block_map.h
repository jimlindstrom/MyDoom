#ifndef __BLOCK_MAP_H
#define __BLOCK_MAP_H

#include <stdint.h>

#include "vertex.h"
#include "linedef.h"
#include "wad_lump.h"

#define BLOCK_MAP_NUM_BYTES 4 // size on disk (in the lump)

class block_map_cell
{
public:
  block_map_cell(uint16_t num_linedefs);
  ~block_map_cell();

  uint16_t get_num_linedefs(void) const { return num_linedefs; }

  void set_linedef_num(uint16_t n, uint16_t linedef_num);
  uint16_t get_linedef_num(uint16_t n) const;

  void set_linedef(uint16_t n, linedef *_linedef);
  linedef const *get_linedef(uint16_t n) const;

private:
  uint16_t num_linedefs;
  uint16_t *linedef_nums;
  linedef **linedefs;
};

#define BM_CELL_SIZE 128

class block_map
{
public:
  block_map();
  ~block_map();

  uint16_t get_num_rows(void) const { return num_rows; }
  uint16_t get_num_cols(void) const { return num_cols; }
  block_map_cell *get_cell_rw(uint16_t col, uint16_t row) { return block_map_cells[(row*num_cols)+col]; }
  block_map_cell *get_cell(uint16_t col, uint16_t row) const { return block_map_cells[(row*num_cols)+col]; }
  block_map_cell *get_cell_by_map_pos(vertex const *v) const;

  bool read_from_lump(wad_lump const *lump, uint16_t num_sectors);

private:
  int16_t  x_origin;
  int16_t  y_origin;
  uint16_t num_cols;
  uint16_t num_rows;
  block_map_cell **block_map_cells;
};

#endif
