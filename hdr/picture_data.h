#ifndef __PICTURE_DATA_H
#define __PICTURE_DATA_H

#include <string.h>
#include <stdint.h>

#include "palette.h"

class picture_data
{
public:
  picture_data();
  ~picture_data();

  bool set_from_lump_data(uint8_t const *_data);
  void print_html_file(char const *filename, palette const *pal);

  uint16_t get_width(void) const { return width; } 
  uint16_t get_height(void) const { return height; } 
  uint16_t get_left(void) const { return left; } 
  uint16_t get_top(void) const { return top; } 

  uint8_t const get_pixel(int x, int y) const;

private:
  uint16_t width, height, left, top;
  uint8_t **pixel_columns;
};

#endif
