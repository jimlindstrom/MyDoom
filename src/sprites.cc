#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "palettes.h"
#include "sprites.h"
#include "wad_file.h"
#include "sprite.h"

//#define DEBUG_PRINTING
#include "debug.h"

static uint32_t num_sprites = 0;
static sprite *sprites = NULL;

#define MAX_ANIMATIONS 200
static sprite_animation animations[MAX_ANIMATIONS];
static int32_t num_animations = 0;


bool read_sprites(wad_file const *wad)
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
      debug_printf("loading sprite \"%s\" ", sprite_lump->get_name());
      strncpy(name_prefix, sprite_lump->get_name(), 4); name_prefix[4] = 0;
      sprites[i].set_name_prefix(name_prefix);

      frame_idx = sprite_lump->get_name()[4] - 'A';
      if(frame_idx > 22) /* just some sanity-checking */
      {
        printf("WARNING: Sprite \"%s\" has a %d'th frame\n", name_prefix, frame_idx);
      }
      sprites[i].set_frame_idx(0, frame_idx);

      rotation_idx = sprite_lump->get_name()[5] - '0';
      if(rotation_idx > 8)
      {
        printf("ERROR: Sprite \"%s\" has rotation index of %d\n", sprite_lump->get_name(), rotation_idx);
        return false;
      }
      sprites[i].set_rotation_idx(0, rotation_idx);
      debug_printf(" [frame:%d, ang:%d]", frame_idx, rotation_idx);
      if(sprites[i].get_frame_idx(1)    > 30) { printf("ERROR: sprites frame idx is HUGE\n");    exit(0); }
      if(sprites[i].get_rotation_idx(1) > 30) { printf("ERROR: sprites rotation idx is HUGE\n"); exit(0); }

      if(strlen(sprite_lump->get_name()) == 8)
      {
        frame_idx = sprite_lump->get_name()[6] - 'A';
        if(frame_idx > 22) /* just some sanity-checking */
        {
          printf("WARNING: Sprite \"%s\" has a %d'th frame (2ndary rotation)\n", name_prefix, frame_idx);
        }
        sprites[i].set_frame_idx(1, frame_idx);
  
        rotation_idx = sprite_lump->get_name()[7] - '0';
        if(rotation_idx > 8)
        {
          printf("ERROR: Sprite \"%s\" has rotation index of %d (2ndary rotation)\n", sprite_lump->get_name(), rotation_idx);
          return false;
        }
        sprites[i].set_rotation_idx(1, rotation_idx);
        debug_printf(" [frame:%d, ang:%d]", frame_idx, rotation_idx);
        if(sprites[i].get_frame_idx(1)    > 30) { printf("ERROR: sprites frame idx is HUGE\n");    exit(0); }
        if(sprites[i].get_rotation_idx(1) > 30) { printf("ERROR: sprites rotation idx is HUGE\n"); exit(0); }
      }
      debug_printf("\n");

      sprites[i].set_from_lump_data(sprite_lump->get_data());
      i++;
    }
  }

  return true;
}

bool assemble_animations(void)
{
  int i;

  for(i=0; i<num_sprites; i++)
  {
    sprite const *cur_sprite = &sprites[i];
    sprite_animation *anim = sprites_lookup_animation(cur_sprite->get_name_prefix());
    if(!anim)
    {
      anim = &animations[num_animations++];
      if(num_animations >= MAX_ANIMATIONS)
      {
        printf("ERROR: too many sprite animations!\n");
        exit(0);
      }
      anim->set_name_prefix(cur_sprite->get_name_prefix());
    }

    for(int j=0; j<cur_sprite->get_num_orientations(); j++)
    {
      if(j>1) { printf("WARNING: %s has %d orientations\n", cur_sprite->get_name_prefix(), cur_sprite->get_num_orientations()); }
      uint8_t frame_idx = cur_sprite->get_frame_idx(j);
      sprite_animation_frame *cur_frame = anim->get_frame(frame_idx);
      if(!cur_frame)
      {
        printf("ERROR: %s failed to retrieve frame %d\n", cur_sprite->get_name_prefix(), frame_idx); 
        exit(0);
      }
      uint8_t new_num_frames = MAX(frame_idx+1, anim->get_num_frames());
      anim->set_num_frames(new_num_frames);

      uint8_t rotation_idx = cur_sprite->get_rotation_idx(j);
      if(rotation_idx >= MAX_NUM_SPRITE_ANGLES)
      {
        printf("ERROR: %s has sprite with rotation angle %d\n", cur_sprite->get_name_prefix(), rotation_idx); 
        exit(0);
      }
      uint8_t new_num_angles = MAX(cur_frame->get_num_angles(), rotation_idx+1);
      cur_frame->set_num_angles(new_num_angles);
      cur_frame->set_sprite(rotation_idx, cur_sprite);
      debug_printf("animation \"%s\" (frame %d, angle %d): frame %d (of %d) now has %d angles\n", 
                   cur_sprite->get_name_prefix(), frame_idx, rotation_idx, frame_idx, anim->get_num_frames(), cur_frame->get_num_angles());
    }
  }

  return true;
}

bool sprites_init(wad_file const *wad)
{
  return read_sprites(wad) && assemble_animations();
}

void sprites_destroy(void)
{
  if (sprites) { delete[] sprites; }
}

sprite_animation *sprites_lookup_animation(char const *prefix)
{
  for(int i=0; i<num_animations; i++)
  {
    if(strcasecmp(prefix, animations[i].get_name_prefix()) == 0)
    {
      return &animations[i];
    }
  }

  return NULL;
}
