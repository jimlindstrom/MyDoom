#ifndef __SPRITE_H
#define __SPRITE_H

#include <string.h>
#include <stdint.h>

#include "palette.h"

class sprite
{
public:
  sprite();
  ~sprite();

  bool set_from_lump_data(uint8_t const *_data);
  void print_html_file(char const *filename, palette const *pal);

  char const *get_name_prefix(void) const { return name_prefix; }
  uint8_t get_frame_idx(void) const { return frame_idx; }
  uint8_t get_rotation_idx(void) const { return rotation_idx; }
  uint16_t get_width(void) const { return width; } 
  uint16_t get_height(void) const { return height; } 
  uint16_t get_left(void) const { return left; } 
  uint16_t get_top(void) const { return top; } 

  void set_name_prefix(char const *_name_prefix) { strcpy(name_prefix, _name_prefix); name_prefix[4]=0; }
  void set_frame_idx(uint8_t _frame_idx) { frame_idx = _frame_idx; }
  void set_rotation_idx(uint8_t _rotation_idx) { rotation_idx = _rotation_idx; }

  uint8_t const get_pixel(int x, int y);

private:
  char name_prefix[5]; // 4 chars + NULL
  uint8_t frame_idx;
  uint8_t rotation_idx;
  uint16_t width, height, left, top;
  uint8_t **pixel_columns;
};

#endif
