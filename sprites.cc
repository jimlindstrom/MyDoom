#include <stdlib.h>
#include <stdio.h>

#include "palettes.h"
#include "sprites.h"
#include "wad_file.h"
#include "sprite.h"

static int32_t num_sprites = 0;
static sprite *sprites = NULL;

bool sprites_init(wad_file const *wad)
{
  wad_lump const *sprite_lump = NULL;
  uint8_t const *sprite_ptr;
  int i;

  num_sprites = 0;
  for(sprite_lump = wad->get_next_lump(wad->find_lump_by_name("S_START"));
      sprite_lump && !sprite_lump->is_named("S_END");
      sprite_lump = wad->get_next_lump(sprite_lump))
  {
    if (sprite_lump->get_num_bytes() > 0)
    {
      num_sprites++;
    }
  }

  sprites = new sprite[num_sprites];

  i=0;
  for(sprite_lump = wad->get_next_lump(wad->find_lump_by_name("S_START"));
      sprite_lump && !sprite_lump->is_named("S_END");
      sprite_lump = wad->get_next_lump(sprite_lump))
  {
    if (sprite_lump->get_num_bytes() > 0)
    {
      printf("reading sprite %s\n", sprite_lump->get_name());
      sprites[i++].set_from_lump_data(sprite_lump->get_data());
    }
  }

  sprites[0].print_html_file("/tmp/sprite0.html", palettes_get(0));

  return true;
}

void sprites_destroy(void)
{
  if (sprites) { delete[] sprites; }
}

