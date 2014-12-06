#ifndef __FLAT_H
#define __FLAT_H

#include <stdint.h>

#include "palette.h"

#define FLAT_WIDTH	64
#define FLAT_HEIGHT	64
#define FLAT_NUM_BYTES	(FLAT_WIDTH*FLAT_HEIGHT)

class flat
{
public:
  flat();
  ~flat();

  bool set_data(uint8_t const *_data);
  void print_html_file(char const *filename, palette const *pal);

  uint8_t const *get_pixel(int x, int y);

private:
  uint8_t *data;
};

#endif
