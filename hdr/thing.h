#ifndef __THING_H
#define __THING_H

#include <stdint.h>

#include "thing_types.h"

#define THING_NUM_BYTES 10 // size on disk (in the lump)

#define THING_MASK_LEVELS_1_AND_2	0x0001	// Thing is on skill levels 1 & 2
#define THING_MASK_LEVEL_3		0x0002	// Thing is on skill level 3
#define THING_MASK_LEVELS_4_AND_5	0x0004	// Thing is on skill levels 4 & 5
#define THING_MASK_DEAF			0x0008	// Thing is deaf
#define THING_MASK_NOT_SINGLE_PLAYER	0x0010	// Thing is not in single player

class thing
{
public:
  thing();
  ~thing();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_x(void) const { return x; }
  int16_t get_y(void) const { return y; }
  int16_t get_facing_angle(void) const { return facing_angle; }
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

private:
  int16_t x, y;  // FIXME: signed?
  int16_t facing_angle; // FIXME: signed?
  uint16_t thing_type, flags;

};

#endif
