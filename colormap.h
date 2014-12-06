#ifndef __COLORMAP_H
#define __COLORMAP_H

#include "color.h"

class colormap
{
public:
  colormap();
  ~colormap();

  bool set_data(uint8_t const *data, uint32_t _num_brightnesses);
  void print_html_file(char const *filename);

  uint8_t const *get_brightness(int idx);

private:
  uint32_t num_brightnesses;
  uint8_t *brightnesses;
};

#endif
