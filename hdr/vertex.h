#ifndef __VERTEX_H
#define __VERTEX_H

#include <stdint.h>

#define VERTEX_NUM_BYTES 4 // size on disk (in the lump)

class vertex
{
public:
  vertex();
  vertex(int _x, int _y) { x=_x; y=_y; }
  ~vertex();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_x(void) const { return x; }
  int16_t get_y(void) const { return y; }

  void set_to(vertex const *v) { x=v->get_x(); y=v->get_y(); }
  void set_x(int _x) { x=_x; }
  void set_y(int _y) { y=_y; }

  void translate(vertex const *v) { x += v->get_x(); y += v->get_y(); }

  float angle_to_point(vertex const *v) const;

private:
  int16_t x;
  int16_t y;
};

void vertex_test(void);

#endif
