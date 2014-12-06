#ifndef __VERTEX_H
#define __VERTEX_H

#include <stdint.h>

#define VERTEX_NUM_BYTES 4 // size on disk (in the lump)

class vertex
{
public:
  vertex();
  ~vertex();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_x(void) const { return x; }
  int16_t get_y(void) const { return y; }

private:
  int16_t x; // FIXME: signed?
  int16_t y; // FIXME: signed?
};

#endif
