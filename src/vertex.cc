#include <string.h>
#include <math.h>

#include "vertex.h"
#include "tests.h"

vertex::vertex()
{
}

vertex::~vertex()
{
}

bool vertex::read_from_lump_data(uint8_t const *lump_data)
{
  x = *((int16_t*)lump_data); lump_data += 2;
  y = *((int16_t*)lump_data); lump_data += 2;

  return true;
}

float vertex::angle_to_point(vertex const *v) const
{
  float dy = v->get_y() - y;
  float dx = v->get_x() - x;
  return atan2(dy, dx) * 180.0 / M_PI;
}

 
/******************************************************************************
 * TESTS
 ******************************************************************************/

void vertex_text_angle_origin_to_up(void)
{
  vertex v1(0,0);
  vertex v2(0,1);
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), 89.9,90.1); // 90
}

void vertex_text_angle_origin_to_downright(void)
{
  vertex v1(0,0);
  vertex v2(1,-1);
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), -45.1,-44.9); // -45
}

void vertex_text_angle_origin_to_left(void)
{
  vertex v1(0,0);
  vertex v2(-1,0);
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), 179.9,180.1); // 180
}

void vertex_text_angle_random_to_upleft(void)
{
  vertex v1(2,2);
  vertex v2(1,3);
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), 134.9,135.1); // 135
}

void vertex_test(void)
{
  vertex_text_angle_origin_to_up();
  vertex_text_angle_origin_to_downright();
  vertex_text_angle_origin_to_left();
  vertex_text_angle_random_to_upleft();
}
