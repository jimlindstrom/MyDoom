#ifndef __FLAT_H
#define __FLAT_H

#include <stdint.h>
#include <string.h>

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

  uint8_t const *get_pixel(int x, int y) const;

  void set_name(char const *_name) { strcpy(name, _name); name[8] = 0; }
  char const *get_name(void) const { return name; }

private:
  uint8_t *data;
  char name[9];
};

#endif
