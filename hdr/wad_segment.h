#ifndef __WAD_SEGMENT_H
#define __WAD_SEGMENT_H

#include <stdint.h>

#include "projector.h"
#include "camera.h"
#include "vertex.h"
#include "segment.h"
#include "linedef.h"
#include "column_range_list.h"
#include "vis_planes.h"
#include "segment_projection.h"

#define SEGMENT_NUM_BYTES 12 // size on disk (in the lump)

class wad_segment : public segment
{
public:
  wad_segment();
  ~wad_segment();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_vertex_r_num(void) const { return vertex_r_num; } // start_vertex == vertex_r
  uint16_t get_vertex_l_num(void) const { return vertex_l_num; } // end_vertex   == vertex_l
  uint16_t get_start_vertex_num(void) const { return get_vertex_r_num(); }
  uint16_t get_end_vertex_num(void) const { return get_vertex_l_num(); }
  float    get_angle(void) const { return angle; }
  uint16_t get_linedef_num(void) const { return linedef_num; }
  uint16_t get_direction(void) const { return direction; }
  uint16_t get_offset(void) const { return offset; }
  linedef const *get_linedef(void) const { return _linedef; }
  sector const *get_front_sector(void) const { return front_sector; }
  sector const *get_back_sector(void) const { return back_sector; }

  void set_linedef(linedef const *ld);
  void set_start_vertex(vertex const *v) { set_vertex_r(v); }
  void set_end_vertex(vertex const *v) { set_vertex_l(v); }
  void set_front_sector(sector const *s) { front_sector = s; }
  void set_back_sector(sector const *s) { back_sector = s; }

  bool is_singled_sided_line(void) const;
  bool is_closed_door(void) const;
  bool is_window(void) const;
  bool is_empty_line(void) const;
  bool is_other_single_sided_line(void) const;

  bool is_same_floor_plane_on_both_sides(void) const;
  bool is_same_ceiling_plane_on_both_sides(void) const;

  void render_player_view(camera const *_camera, column_range_list *col_ranges,
                          vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const;

  uint16_t segment_num; // for debug printing

private:
  uint16_t vertex_r_num;
  uint16_t vertex_l_num;
  float    angle; 
  uint16_t linedef_num;
  uint16_t direction;        // 0 (same as linedef) or 1 (opposite of linedef) -- called 'side' in doom code
  uint16_t offset;           // distance along linedef to start of seg

  linedef const *_linedef;
  sector const *front_sector, *back_sector;

  segment_projection *project(camera const *_camera) const;
};

#endif
