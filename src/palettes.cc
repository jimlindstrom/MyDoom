#include <stdlib.h>
#include <stdio.h>

#include "palettes.h"
#include "wad_file.h"
#include "palette.h"

#define NUM_PALETTES 		 14
#define COLORS_PER_PALETTE	256
#define BYTES_PER_COLOR		  3

static palette palettes[NUM_PALETTES];

bool palettes_init(wad_file const *wad)
{
  wad_lump const *palette_lump = NULL;
  uint8_t const *palette_ptr;
  int i;

  palette_lump = wad->find_lump_by_name("PLAYPAL");
  if (!palette_lump)
  {
    printf("ERROR: could not file palette lump\n");
    return false;
  }

  for(i=0; i<NUM_PALETTES; i++)
  {
    palette_ptr = palette_lump->get_data() + (i*COLORS_PER_PALETTE*BYTES_PER_COLOR);
    palettes[i].from_linear_256_array(palette_ptr);
  }

  palettes[0].print_html_file("/tmp/palettes.html");

  return true;
}

void palettes_destroy(void)
{
}

palette const *palettes_get(int idx)
{
  if(idx >= NUM_PALETTES)
  {
    printf("ERROR: palette %d requested. >= NUM PALETTES (%d).\n", idx, NUM_PALETTES);
    exit(0);
  }
  return &palettes[idx];
}
