#ifndef __EPISODE_MAP_H
#define __EPISODE_MAP_H

#include "wad_file.h"
#include "wad_lump.h"

#include "thing.h"
#include "linedef.h"
#include "sidedef.h"
#include "vertex.h"
#include "segment.h"
#include "subsector.h"
#include "node.h"
#include "sector.h"
#include "reject_table.h"
#include "block_map.h"

class episode_map
{
public:
  episode_map();
  ~episode_map();

  bool read_from_lump(wad_file const *wad, wad_lump const *lump);

  char const *get_name(void) const { return name; }

  void draw_overhead_map(int screen_width, int screen_height) const;

private:
  char *name;

  int num_things;
  thing *things;

  int num_linedefs;
  linedef *linedefs;

  int num_sidedefs;
  sidedef *sidedefs;

  int num_vertexes;
  vertex *vertexes;

  int num_segments;
  segment *segments;

  int num_subsectors;
  subsector *subsectors;

  int num_nodes;
  node *nodes;

  int num_sectors;
  sector *sectors;

  reject_table reject_tbl;
  block_map    _block_map;

  bool read_things(wad_lump const *lump);
  bool read_linedefs(wad_lump const *lump);
  bool read_sidedefs(wad_lump const *lump);
  bool read_vertexes(wad_lump const *lump);
  bool read_segments(wad_lump const *lump);
  bool read_subsectors(wad_lump const *lump);
  bool read_nodes(wad_lump const *lump);
  bool read_sectors(wad_lump const *lump);

  void link_nodes_to_children(void);
  void link_subsectors_to_segments(void);
  void link_segments_to_children(void);
  void link_linedefs_to_children(void);
  void link_sidedefs_to_children(void);
};

#endif
