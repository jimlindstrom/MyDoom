#ifndef __SPRITE_ANIMATION_FRAME_H
#define __SPRITE_ANIMATION_FRAME_H

#include <stdint.h>

#include "sprite.h"

#define MAX_NUM_SPRITE_ANGLES 12 // FIXME: 9 is probably enough..

class sprite_animation_frame
{
public:
  sprite_animation_frame();

  void set_num_angles(uint8_t n);
  void set_sprite(uint8_t angle_idx, sprite const *s);

  uint8_t get_num_angles(void) const;
  sprite const *get_sprite(uint8_t angle_idx) const;

private:
  sprite const *sprites[MAX_NUM_SPRITE_ANGLES];
  uint8_t num_angles;
};

#endif
