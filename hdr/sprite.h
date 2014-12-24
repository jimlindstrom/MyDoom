#ifndef __SPRITE_H
#define __SPRITE_H

#include <string.h>
#include <stdint.h>

#include "picture_data.h"

class sprite : public picture_data
{
public:
  sprite();
  ~sprite();

  char const *get_name_prefix(void) const { return name_prefix; }

  void set_name_prefix(char const *_name_prefix);
  void set_frame_idx(uint8_t orientation, uint8_t _frame_idx);
  void set_rotation_idx(uint8_t orientation, uint8_t _rotation_idx);

  uint8_t get_num_orientations(void) const { return num_orientations; }
  uint8_t get_frame_idx(uint8_t orientation) const { return frame_idx[orientation]; }
  uint8_t get_rotation_idx(uint8_t orientation) const { return rotation_idx[orientation]; }

  void draw(int16_t screen_x, int16_t screen_y, float scale) const;

private:
  char name_prefix[5]; // 4 chars + NULL
  uint8_t frame_idx[2];
  uint8_t rotation_idx[2];
  uint8_t num_orientations; // 1 or 2 (if same sprite used in mirror image at different rotation angle
};

#endif
