#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "palettes.h"
#include "flats.h"
#include "wad_file.h"
#include "flat.h"

static int32_t num_flats = 0;
static flat *flats = NULL;

bool flats_init(wad_file const *wad)
{
  wad_lump const *flat_lump = NULL;
  int i;

  num_flats = 0;
  for(flat_lump = wad->get_next_lump(wad->find_lump_by_name("F_START"));
      flat_lump && !flat_lump->is_named("F_END");
      flat_lump = wad->get_next_lump(flat_lump))
  {
    if (flat_lump->get_num_bytes() > 0)
    {
      num_flats++;
    }
  }

  flats = new flat[num_flats];

  i=0;
  for(flat_lump = wad->get_next_lump(wad->find_lump_by_name("F_START"));
      flat_lump && !flat_lump->is_named("F_END");
      flat_lump = wad->get_next_lump(flat_lump))
  {
    if (flat_lump->get_num_bytes() > 0)
    {
      flats[i].set_data(flat_lump->get_data());
      flats[i].set_name(flat_lump->get_name());
      i++;
    }
  }

  //flats[0].print_html_file("/tmp/flat0.html", palettes_get(0));

  return true;
}

flat const *flats_find_by_name(char const *name)
{
  for(int i=0; i<num_flats; i++)
  {
    if(strcmp(flats[i].get_name(), name) == 0)
    {
      return &flats[i];
    }
  }

  return NULL;
}

void flats_destroy(void)
{
  if (flats) { delete[] flats; }
}

