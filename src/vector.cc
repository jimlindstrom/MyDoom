#include "vector.h"
#include "tests.h"

#define FLATNESS_EPSILON 0.00001

bool vector::is_vertical(void) const
{
  float dx = vertex_2->get_x() - vertex_1->get_x();
  return ((dx > -FLATNESS_EPSILON) && (dx < FLATNESS_EPSILON));
}

bool vector::is_horizontal(void) const
{
  float dy = vertex_2->get_y() - vertex_1->get_y();
  return ((dy > -FLATNESS_EPSILON) && (dy < FLATNESS_EPSILON));
}

float vector::get_slope(void) const
{
  float dy = vertex_2->get_y() - vertex_1->get_y();
  float dx = vertex_2->get_x() - vertex_1->get_x();
  return dy / dx;
}

void vector::get_slope_and_y_intercept(float *slope, float *y_intercept) const
{
  *slope       = get_slope();
  *y_intercept = vertex_1->get_y() - (*slope * vertex_1->get_x());
}

/******************************************************************************
 * TESTS
 ******************************************************************************/

void vector_test_line_eq(void)
{
  float b = -9.3, m = 3.8;
  float b2, m2;

  vertex v1, v2;
  v1.set_x(-3);
  v1.set_y((m * v1.get_x()) + b);

  v2.set_x(10);
  v2.set_y((m * v2.get_x()) + b);

  vector v;
  v.set_vertex_1(&v1);
  v.set_vertex_2(&v2);

  v.get_slope_and_y_intercept(&m2, &b2);

  TEST_ASSERT_WITHIN(m2, m-0.001, m+0.001);
  TEST_ASSERT_WITHIN(b2, b-0.001, b+0.001);
}

void vector_tests(void)
{
  vector_test_line_eq();
}

