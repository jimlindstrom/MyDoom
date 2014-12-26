#ifndef __SPRITES_H
#define __SPRITES_H

#include "wad_file.h"
#include "sprite.h"

#define MAX_NUM_SPRITE_ANGLES 12 // FIXME: 9 is probably enough..
class sprite_animation_frame
{
public:
  sprite_animation_frame() { num_angles = 0; }

  void set_num_angles(uint8_t n) { num_angles = n; }
  void set_sprite(uint8_t angle_idx, sprite const *s) { sprites[angle_idx] = s; }

  uint8_t get_num_angles(void) const { return num_angles; }
  sprite const *get_sprite(int16_t angle_idx) const { return sprites[angle_idx]; }

private:
  sprite const *sprites[MAX_NUM_SPRITE_ANGLES];
  uint8_t num_angles;
};

class sprite_animation
{
public:
  sprite_animation() { num_frames = 0; }

  void set_num_frames(uint8_t n) { num_frames = n; }
  void set_name_prefix(char const *np) { strcpy(name_prefix, np); name_prefix[4] = 0; }

  uint8_t get_num_frames(void) const { return num_frames; }
  char const *get_name_prefix(void) const { return name_prefix; }

  sprite_animation_frame *get_frame(int16_t frame_idx) { return &frames[frame_idx]; }

private:
  sprite_animation_frame frames[25];
  uint8_t num_frames;
  char name_prefix[5]; // 4 chars + NULL
};

bool sprites_init(wad_file const *wad);
void sprites_destroy(void);
sprite_animation *sprites_lookup_animation(char const *prefix);

#endif
