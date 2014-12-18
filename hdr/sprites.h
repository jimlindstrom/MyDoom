#ifndef __SPRITES_H
#define __SPRITES_H

#include "wad_file.h"
#include "sprite.h"

class sprite_animation_frame
{
public:
  sprite_animation_frame() { num_angles = 0; }

  void set_num_angles(int16_t n) { num_angles = n; }
  void set_sprite(int16_t angle_idx, sprite const *s) { sprites[angle_idx] = s; }

  int16_t get_num_angles(void) const { return num_angles; }
  sprite const *get_sprite(int16_t angle_idx) const { return sprites[angle_idx]; }

private:
  sprite const *sprites[8];
  int16_t num_angles;
};

class sprite_animation
{
public:
  sprite_animation() { num_frames = 0; }

  void set_num_frames(int16_t n) { num_frames = n; }
  void set_name_prefix(char const *np) { strcpy(name_prefix, np); name_prefix[4] = 0; }

  int16_t get_num_frames(void) const { return num_frames; }
  char const *get_name_prefix(void) const { return name_prefix; }

  sprite_animation_frame *get_frame(int16_t frame_idx) { return &frames[frame_idx]; }

private:
  sprite_animation_frame frames[50];
  int16_t num_frames;
  char name_prefix[5]; // 4 chars + NULL
};

bool sprites_init(wad_file const *wad);
void sprites_destroy(void);
sprite_animation *sprites_lookup_animation(char const *prefix);

#endif
