#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing.h"

#define DEBUG_PRINTING
#include "debug.h"

thing::thing()
{
}

thing::~thing()
{
}

bool thing::read_from_lump_data(uint8_t const *lump_data)
{
  map_position.set_x(*(( int16_t*)lump_data)); lump_data += 2;
  map_position.set_y(*(( int16_t*)lump_data)); lump_data += 2;
  facing_angle     = (*(( int16_t*)lump_data))/256.0 ; lump_data += 2;
  thing_type       = *((uint16_t*)lump_data) ; lump_data += 2;
  flags            = *((uint16_t*)lump_data) ; lump_data += 2;

  // convert angle from degrees to radians
  facing_angle = DEG_TO_RAD(facing_angle+90);

  // get the definition (description, etc.)
  defn = thing_definition_lookup(thing_type);

  animation = sprites_lookup_animation(defn->sprite_prefix);

  return true;
}

void thing::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player) const
{
  debug_printf("  rendering \"%s\"\n", defn->description);
}

