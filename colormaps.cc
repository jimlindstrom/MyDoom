#include <stdlib.h>
#include <stdio.h>

#include "colormaps.h"
#include "wad_file.h"
#include "colormap.h"

#define NUM_COLORMAPS 		 34
#define BRIGHTNESSES_PER_MAP	256
#define BYTES_PER_COLOR		  1

static colormap colormaps[NUM_COLORMAPS];

bool colormaps_init(wad_file const *wad)
{
  wad_lump const *colormap_lump = NULL;
  uint8_t const *colormap_ptr;
  int i;

  colormap_lump = wad->find_lump_by_name("COLORMAP");
  if (!colormap_lump)
  {
    printf("ERROR: could not file colormap lump\n");
    return false;
  }

  for(i=0; i<NUM_COLORMAPS; i++)
  {
    colormap_ptr = colormap_lump->get_data() + (i*BRIGHTNESSES_PER_MAP*BYTES_PER_COLOR);
    colormaps[i].set_data(colormap_ptr, BRIGHTNESSES_PER_MAP);
  }

  colormaps[0].print_html_file("/tmp/colormaps.html");

  return true;
}

void colormaps_destroy(void)
{
}
