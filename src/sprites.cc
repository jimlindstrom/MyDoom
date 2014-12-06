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
  uint8_t frame_idx, rotation_idx;
  char name_prefix[5];
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
      strncpy(name_prefix, sprite_lump->get_name(), 4); name_prefix[4] = 0;
      sprites[i].set_name_prefix(name_prefix);

      frame_idx = sprite_lump->get_name()[4] - 'A';
      sprites[i].set_frame_idx(frame_idx);

      rotation_idx = sprite_lump->get_name()[5] - '0';
      if(rotation_idx > 8)
      {
        printf("ERROR: Sprite \"%s\" has rotation index of %d\n", sprite_lump->get_name(), rotation_idx);
        return false;
      }
      sprites[i].set_rotation_idx(rotation_idx);

      sprites[i].set_from_lump_data(sprite_lump->get_data());
      i++;
    }
  }

  sprites[0].print_html_file("/tmp/sprite0.html", palettes_get(0));

  return true;
}

void sprites_destroy(void)
{
  if (sprites) { delete[] sprites; }
}

