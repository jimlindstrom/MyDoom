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
  uint8_t get_frame_idx(void) const { return frame_idx; }
  uint8_t get_rotation_idx(void) const { return rotation_idx; }

  void set_name_prefix(char const *_name_prefix) { strcpy(name_prefix, _name_prefix); name_prefix[4]=0; }
  void set_frame_idx(uint8_t _frame_idx) { frame_idx = _frame_idx; }
  void set_rotation_idx(uint8_t _rotation_idx) { rotation_idx = _rotation_idx; }

private:
  char name_prefix[5]; // 4 chars + NULL
  uint8_t frame_idx;
  uint8_t rotation_idx;
};

#endif
