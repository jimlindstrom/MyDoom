#ifndef __LINEDEF_H
#define __LINEDEF_H

#include <stdint.h>

#include "vertex.h"
#include "sidedef.h"
#include "vis_planes.h"
#include "clipped_segment_projection.h"

#define LINEDEF_NUM_BYTES 14 // size on disk (in the lump)

#define LINEDEF_FLAGS_MASK_BLOCKS_PLAYERS_AND_MONSTERS	0x0001 // blocks players and monsters 
#define LINEDEF_FLAGS_MASK_BLOCKS_MONSTERS		0x0002 // blocks monsters 
#define LINEDEF_FLAGS_MASK_TWO_SIDED			0x0004 // two sided 
#define LINEDEF_FLAGS_MASK_UPPER_TEXTURE_IS_UNPEGGED	0x0008 // upper texture is unpegged 
#define LINEDEF_FLAGS_MASK_LOWER_TEXTURE_IS_UNPEGGED	0x0010 // lower texture is unpegged 
#define LINEDEF_FLAGS_MASK_SECRET			0x0020 // secret (shows as one-sided on automap), and 
							       // monsters cannot open if it is a door (type 1) 
#define LINEDEF_FLAGS_MASK_BLOCKS_SOUND			0x0040 // blocks sound 
#define LINEDEF_FLAGS_MASK_NEVER_ON_AUTOMAP		0x0080 // never shows on automap 
#define LINEDEF_FLAGS_MASK_ALWAYS_ON_AUTOMAP		0x0100 // always shows on automap

#define LINEDEF_HAS_NO_SIDEDEF				65535 // would be -1 if we had used int16_t vs uint16_t

class linedef
{
public:
  linedef();
  ~linedef();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_start_vertex_num(void) const { return start_vertex_num; }
  uint16_t get_end_vertex_num(void) const { return end_vertex_num; }
  uint16_t get_flags(void) const { return flags; }
  uint16_t get_special_type(void) const { return special_type; }
  uint16_t get_sector_tag(void) const { return sector_tag; }
  uint16_t get_right_sidedef_num(void) const { return right_sidedef_num; }
  uint16_t get_left_sidedef_num(void) const { return left_sidedef_num; }

  bool has_left_sidedef(void)  const { return (left_sidedef_num  != LINEDEF_HAS_NO_SIDEDEF); }
  bool has_right_sidedef(void) const { return (right_sidedef_num != LINEDEF_HAS_NO_SIDEDEF); }

  bool blocks_players(void)    const { return (flags & LINEDEF_FLAGS_MASK_BLOCKS_PLAYERS_AND_MONSTERS); }
  bool blocks_monsters(void)   const { return (flags & LINEDEF_FLAGS_MASK_BLOCKS_PLAYERS_AND_MONSTERS) || 
                                            (flags & LINEDEF_FLAGS_MASK_BLOCKS_MONSTERS); }
  bool is_two_sided(void)      const { return (flags & LINEDEF_FLAGS_MASK_TWO_SIDED); }
  bool is_one_sided(void)      const { return !is_two_sided(); }
  bool upper_is_unpegged(void) const { return (flags & LINEDEF_FLAGS_MASK_UPPER_TEXTURE_IS_UNPEGGED); } 
  bool lower_is_unpegged(void) const { return (flags & LINEDEF_FLAGS_MASK_LOWER_TEXTURE_IS_UNPEGGED); }
  bool is_secret(void)         const { return (flags & LINEDEF_FLAGS_MASK_SECRET); }
  bool blocks_sound(void)      const { return (flags & LINEDEF_FLAGS_MASK_BLOCKS_SOUND); }
  bool never_on_automap(void)  const { return (flags & LINEDEF_FLAGS_MASK_NEVER_ON_AUTOMAP); }
  bool always_on_automap(void) const { return (flags & LINEDEF_FLAGS_MASK_ALWAYS_ON_AUTOMAP); }

  void set_left_sidedef(sidedef const *_sidedef);
  void set_right_sidedef(sidedef const *_sidedef);
  void set_start_vertex(vertex const *v);
  void set_end_vertex(vertex const *v);
  vertex const *get_start_vertex(void) const { return start_vertex; }
  vertex const *get_end_vertex(void) const { return end_vertex; }

  sidedef const *get_sidedef(int direction) const { return (direction ? left_sidedef : right_sidedef ); } // dir is from segment

  float get_length(void) const { return start_vertex->distance_to_point(end_vertex); }

  int16_t get_ceiling_z(int direction) const;
  int16_t get_floor_z(int direction) const;

  void set_z_values(int direction, bool is_outdoor_area, clipped_segment_projection *wall) const;
  void set_textures(int direction, clipped_segment_projection *wall) const;

private:
  uint16_t start_vertex_num;
  uint16_t end_vertex_num;
  uint16_t flags;
  uint16_t special_type;
  uint16_t sector_tag;
  uint16_t right_sidedef_num;
  uint16_t left_sidedef_num;

  sidedef const *left_sidedef;
  sidedef const *right_sidedef;
  vertex const *start_vertex;
  vertex const *end_vertex;

  int16_t get_upper_ty_peg_offset(int16_t dz, int16_t tex_h) const;
  int16_t get_mid_ty_peg_offset(  int16_t dz, int16_t tex_h) const;
  int16_t get_lower_ty_peg_offset(int16_t dz, int16_t tex_h) const;
};

#endif
