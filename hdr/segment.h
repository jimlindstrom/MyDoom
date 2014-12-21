#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <stdint.h>

#include "projector.h"
#include "player.h"
#include "vertex.h"
#include "vector.h"
#include "linedef.h"
#include "column_range.h"
#include "vis_planes.h"
#include "segment_projection.h"

#define SEGMENT_NUM_BYTES 12 // size on disk (in the lump)

class segment
{
public:
  segment() { vertex_r = vertex_l = NULL; }
  segment(vertex const *vl, vertex const *vr) { vertex_l = vl; vertex_r = vr; }
  ~segment() { }

  void set_vertex_l(vertex const *v) { vertex_l = v; }
  void set_vertex_r(vertex const *v) { vertex_r = v; }

  bool is_vertical(void) const;
  bool is_horizontal(void) const;

  float get_length(void) const;
  float get_slope(void) const;
  void get_slope_and_y_intercept(float *slope, float *y_intercept) const;

  bool get_intersection_with_vector(vector const *vec, vertex *ver, float *u) const; // u=0 -> left vertex, u=1 -> right vertex

  void clip_to_vectors(vector const *l_l_delta, vector const *l_r_delta,
                       vertex *v_l_c, vertex *v_r_c,
                       float *u_l_c, float *u_r_c) const;

protected:
  vertex const *vertex_r;
  vertex const *vertex_l;
};

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

  void render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, 
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

  void calculate_angles_from_player(player const *_player, float *angle_l, float *angle_r) const;

  bool is_backface(float angle_l, float angle_r) const;
  bool is_outside_fov(float angle_l, float angle_r, float horiz_fov_radius) const;

  void project(column_range_list *col_ranges, projector const *_projector, player const *_player,
               segment_projection *proj) const;
};

void segment_tests(void);

#endif
