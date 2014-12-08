#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <stdint.h>

#include "player.h"
#include "vertex.h"
#include "linedef.h"

#define SEGMENT_NUM_BYTES 12 // size on disk (in the lump)

class segment
{
public:
  segment();
  ~segment();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_start_vertex_num(void) const { return start_vertex_num; }
  uint16_t get_end_vertex_num(void) const { return end_vertex_num; }
  int16_t  get_angle(void) const { return angle; }
  uint16_t get_linedef_num(void) const { return linedef_num; }
  uint16_t get_direction(void) const { return direction; }
  uint16_t get_offset(void) const { return offset; }

  void set_linedef(linedef const *ld);
  void set_start_vertex(vertex const *v) { start_vertex = v; }
  void set_end_vertex(vertex const *v) { end_vertex = v; }

  void render_player_view(player const *_player, overhead_map *omap) const;

private:
  uint16_t start_vertex_num;
  uint16_t end_vertex_num;
  int16_t  angle; 
  uint16_t linedef_num;
  uint16_t direction;        // 0 (same as linedef) or 1 (opposite of linedef)
  uint16_t offset;           // distance along linedef to start of seg

  vertex const *start_vertex;
  vertex const *end_vertex;
  linedef const *_linedef;
};

#endif
