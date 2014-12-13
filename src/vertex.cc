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
  // FIXME: actual DOOM divides this by 256.0, because it's treated as a floating point...
  x = (float)(*((int16_t*)lump_data)) / 1.0; lump_data += 2;
  y = (float)(*((int16_t*)lump_data)) / 1.0; lump_data += 2;

  return true;
}

void vertex::set_to_a_minus_b(vertex const *a, vertex const *b)
{
  x = a->get_x() - b->get_x();
  y = a->get_y() - b->get_y();
}

float vertex::angle_to_point(vertex const *v) const
{
  float dy = v->get_y() - y;
  float dx = v->get_x() - x;
  return atan2(dy, dx);
}

float vertex::distance_to_point(vertex const*v) const
{
  float dy = v->get_y() - y;
  float dx = v->get_x() - x;
  return sqrt(dx*dx + dy*dy);
}

void vertex::set_from_angle_and_radius(float angle, float radius)
{
  x = radius*cos(angle);
  y = radius*sin(angle);
}

void vertex::rotate(float angle)
{
  float _x = x, _y = y;

  x = (_x*cos(angle)) - (_y*sin(angle));
  y = (_y*cos(angle)) + (_x*sin(angle));
}

 
/******************************************************************************
 * TESTS
 ******************************************************************************/

void vertex_test_angle_origin_to_up(void)
{
  vertex v1(0,0);
  vertex v2(0,1);
  float expected_angle = M_PI/2.0; // 90 deg
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), expected_angle-0.01,expected_angle+0.01);
}

void vertex_test_angle_origin_to_downright(void)
{
  vertex v1(0,0);
  vertex v2(1,-1);
  float expected_angle = -M_PI/4.0; // -45 deg
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), expected_angle-0.01,expected_angle+0.01);
}

void vertex_test_angle_origin_to_left(void)
{
  vertex v1(0,0);
  vertex v2(-1,0);
  float expected_angle = M_PI; // 180 deg
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), expected_angle-0.01,expected_angle+0.01);
}

void vertex_test_angle_random_to_upleft(void)
{
  vertex v1(2,2);
  vertex v2(1,3);
  float expected_angle = 3.0*M_PI/4.0; // 135 deg
  TEST_ASSERT_WITHIN(v1.angle_to_point(&v2), expected_angle-0.01,expected_angle+0.01);
}

void vertex_test_angle_to_point(void)
{
  vertex v;
  float psqrt2 =  0.7071;
  float nsqrt2 = -0.7071;

  v.set_from_angle_and_radius(0.75*M_PI, 1.0);
  TEST_ASSERT_WITHIN(v.get_x(), nsqrt2-0.1, nsqrt2+0.01);
  TEST_ASSERT_WITHIN(v.get_y(), psqrt2-0.1, psqrt2+0.01);

  v.set_from_angle_and_radius(-M_PI/4.0, 1.0);
  TEST_ASSERT_WITHIN(v.get_x(), psqrt2-0.1, psqrt2+0.01);
  TEST_ASSERT_WITHIN(v.get_y(), nsqrt2-0.1, nsqrt2+0.01);
}

void vertex_test(void)
{
  vertex_test_angle_origin_to_up();
  vertex_test_angle_origin_to_downright();
  vertex_test_angle_origin_to_left();
  vertex_test_angle_random_to_upleft();
  vertex_test_angle_to_point();
}
