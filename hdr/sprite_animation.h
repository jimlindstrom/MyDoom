#ifndef __SPRITE_ANIMATION_H
#define __SPRITE_ANIMATION_H

#include <stdint.h>

#include "sprite_animation_frame.h"

#define MAX_NUM_SPRITE_FRAMES 25

class sprite_animation
{
public:
  sprite_animation();

  void set_num_frames(uint8_t n);
  void set_name_prefix(char const *np);

  uint8_t get_num_frames(void) const;
  char const *get_name_prefix(void) const;

  sprite_animation_frame *get_frame(int16_t frame_idx);

private:
  sprite_animation_frame frames[MAX_NUM_SPRITE_FRAMES];
  uint8_t num_frames;
  char name_prefix[5]; // 4 chars + NULL
};

#endif
