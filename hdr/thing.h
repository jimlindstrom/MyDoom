#ifndef __THING_H
#define __THING_H

#include <stdint.h>

#include "vertex.h"
#include "thing_definitions.h"
#include "projector.h"
#include "sector.h"
#include "camera.h"
#include "clipped_segment_projections.h"
#include "sprites.h"
#include "thing_projection.h"

#define THING_NUM_BYTES 10 // size on disk (in the lump)

#define THING_MASK_LEVELS_1_AND_2	0x0001	// Thing is on skill levels 1 & 2
#define THING_MASK_LEVEL_3		0x0002	// Thing is on skill level 3
#define THING_MASK_LEVELS_4_AND_5	0x0004	// Thing is on skill levels 4 & 5
#define THING_MASK_DEAF			0x0008	// Thing is deaf
#define THING_MASK_NOT_SINGLE_PLAYER	0x0010	// Thing is not in single player

class subsector; // forward declaration

class thing
{
public:
  thing();
  ~thing();

  bool read_from_lump_data(uint8_t const *lump_data);

  vertex const *get_map_position(void) const { return &map_position; }
  float get_facing_angle(void) const { return facing_angle; }
  uint16_t get_thing_type(void) const { return thing_type; }
  uint16_t get_flags(void) const { return flags; }

  bool is_on_in_level_1(void) const { return (flags & THING_MASK_LEVELS_1_AND_2); }
  bool is_on_in_level_2(void) const { return (flags & THING_MASK_LEVELS_1_AND_2); }
  bool is_on_in_level_3(void) const { return (flags & THING_MASK_LEVEL_3); }
  bool is_on_in_level_4(void) const { return (flags & THING_MASK_LEVELS_4_AND_5); }
  bool is_on_in_level_5(void) const { return (flags & THING_MASK_LEVELS_4_AND_5); }
  bool is_on_in_level_n(int n) const { return ((n==1) && is_on_in_level_1()) ||
                                              ((n==2) && is_on_in_level_2()) ||
                                              ((n==3) && is_on_in_level_3()) ||
                                              ((n==4) && is_on_in_level_4()) ||
                                              ((n==5) && is_on_in_level_5()); }
  bool is_deaf(void) const { return (flags & THING_MASK_DEAF); }
  bool is_not_single_player(void) const { return (flags & THING_MASK_NOT_SINGLE_PLAYER); }

  void set_subsector(subsector const *ss) { _subsector = ss; }
  subsector const *get_subsector(void) const { return _subsector; }
  sector const *get_sector(void) const;
  thing_definition const *get_definition(void) const { return defn; }
  uint8_t get_frame_idx(void) const;

  void render_player_view(camera const *_camera, clipped_segment_projections *clipped_seg_projs) const;

private:
  vertex map_position;
  float facing_angle;
  uint16_t thing_type, flags;

  thing_definition const *defn;

  sprite_animation *animation;
  uint16_t frame_ctr;

  subsector const *_subsector;

  thing_projection *project(camera const *_camera) const;
  sprite const *get_cur_sprite(thing_projection const *proj) const;
};

#endif
