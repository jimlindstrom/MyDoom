#ifndef __VERTEX_H
#define __VERTEX_H

#include <stdint.h>

#define VERTEX_NUM_BYTES 4 // size on disk (in the lump)

class vertex
{
public:
  vertex();
  vertex(float _x, float _y) { x=_x; y=_y; }
  ~vertex();

  bool read_from_lump_data(uint8_t const *lump_data);

  float get_x(void) const { return x; }
  float get_y(void) const { return y; }

  void set_to(vertex const *v) { x=v->get_x(); y=v->get_y(); }
  void set_x(float _x) { x=_x; }
  void set_y(float _y) { y=_y; }

  void translate(vertex const *v) { x += v->get_x(); y += v->get_y(); }
  void rotate(float angle);

  float angle_to_point(vertex const *v) const;
  float distance_to_point(vertex const *v) const;

  void set_from_angle_and_radius(float angle, float radius);


private:
  float x, y;
};

void vertex_test(void);

#endif
