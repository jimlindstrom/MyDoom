#include <stdlib.h>
#include <stdio.h>

#include "sprite_animation_frame.h"

sprite_animation_frame::sprite_animation_frame()
{
  num_angles = 0;
}

void sprite_animation_frame::set_num_angles(uint8_t n)
{
  num_angles = n;
}

void sprite_animation_frame::set_sprite(uint8_t angle_idx, sprite const *s)
{
  if(angle_idx >= MAX_NUM_SPRITE_ANGLES)
  {
    printf("ERROR: angle_idx >= MAX_NUM_SPRITE_ANGLES\n");
    exit(0);
  }
  sprites[angle_idx] = s;
}

uint8_t sprite_animation_frame::get_num_angles(void) const
{
  return num_angles;
}

sprite const *sprite_animation_frame::get_sprite(uint8_t angle_idx) const
{
  if(angle_idx >= MAX_NUM_SPRITE_ANGLES)
  {
    printf("ERROR: angle_idx >= MAX_NUM_SPRITE_ANGLES\n");
    exit(0);
  }
  return sprites[angle_idx];
}

