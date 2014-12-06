#ifndef __PALETTE_H
#define __PALETTE_H

#include "color.h"

class palette
{
public:
  palette();
  ~palette();

  bool from_linear_256_array(uint8_t const *data);
  void print_html_file(char const *filename);

  color_rgb const *get_color(int color_idx) const;

private:
  int num_colors;
  color_rgb *colors;
};

#endif
