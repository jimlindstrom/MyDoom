#include <stdlib.h>
#include <stdio.h>

#include "sprite_animation.h"

sprite_animation::sprite_animation()
{
  num_frames = 0;
}

void sprite_animation::set_num_frames(uint8_t n)
{
  if(n >= MAX_NUM_SPRITE_FRAMES)
  {
    printf("ERROR: num_frames >= MAX_NUM_SPRITE_FRAMES\n");
    exit(0);
  }
  num_frames = n;
}

void sprite_animation::set_name_prefix(char const *np)
{
  strncpy(name_prefix, np, 4);
  name_prefix[4] = 0;
}

uint8_t sprite_animation::get_num_frames(void) const
{
  return num_frames;
}

char const *sprite_animation::get_name_prefix(void) const
{
  return name_prefix;
}

sprite_animation_frame *sprite_animation::get_frame(int16_t frame_idx)
{
  if(frame_idx >= MAX_NUM_SPRITE_FRAMES)
  {
    printf("ERROR: frame_idx >= MAX_NUM_SPRITE_FRAMES\n");
    exit(0);
  }
  return &frames[frame_idx];
}

