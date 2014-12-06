#include <stdlib.h>
#include <stdio.h>

#include "things.h"
#include "wad_file.h"
#include "thing.h"

#define NUM_THINGS 30

static thing things[NUM_THINGS];

bool things_init(wad_file const *wad)
{
  wad_lump const *palette_lump = NULL;
  uint8_t const *palette_ptr;
  int i;

  palette_lump = wad->find_lump_by_name("PLAYPAL");
  if (!thing_lump)
  {
    printf("ERROR: could not file thing lump\n");
    return false;
  }

  for(i=0; i<NUM_THINGS; i++)
  {
    thing_ptr = thing_lump->get_data() + (i*COLORS_PER_PALETTE*BYTES_PER_COLOR);
    things[i].from_linear_256_array(thing_ptr);
  }

  things[0].print_html_file("/tmp/things.html");

  return true;
}

void things_destroy(void)
{
}
