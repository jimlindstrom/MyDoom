#include "partition_line.h"
#include "tests.h"

// Assumption about coordinate system: 0,0 is (top,left) of screen
bool partition_line::is_point_on_left(vertex const *v) const
{
  float term1 = dx * (v->get_y() - y);
  float term2 = dy * (v->get_x() - x);
  int position = term1 - term2;
  return (position < 0);
}
 
/******************************************************************************
 * TESTS
 ******************************************************************************/

/*   ^
 * v |
 *   p
 */
void partition_line_test_upleft_of_up(void)
{
  {
  // straight up
  partition_line origin_to_up(0, 0, 0, -10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_up.is_point_on_left(&v1));
  }

  {
  // crooked up (left leaning)
  partition_line origin_to_up(0, 0,-1, -10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_up.is_point_on_left(&v1));
  }

  {
  // crooked up (right leaning)
  partition_line origin_to_up(0, 0, 1, -10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_up.is_point_on_left(&v1));
  }
}

/*
 * v
 *   p
 *   |
 *   v
 */
void partition_line_test_upleft_of_down(void)
{
  {
  // straight down
  partition_line origin_to_down( 0, 0, 0, 10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_down.is_point_on_left(&v1));
  }

  {
  // crooked down (left leaning)
  partition_line origin_to_down( 0, 0,-1, 10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_down.is_point_on_left(&v1));
  }

  {
  // crooked down (right leaning)
  partition_line origin_to_down( 0, 0, 1, 10);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_down.is_point_on_left(&v1));
  }
}

/*
 * v
 *   p--->
 */
void partition_line_test_upleft_of_right(void)
{
  {
  // Straight right
  partition_line origin_to_right(0, 0,  1,  0);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_right.is_point_on_left(&v1));
  }

  {
  // Crooked right (leaning up)
  partition_line origin_to_right(0, 0, 10, -1);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_right.is_point_on_left(&v1));
  }

  {
  // Crooked right (leaning down)
  partition_line origin_to_right(0, 0, 10,  1);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(origin_to_right.is_point_on_left(&v1));
  }
}

/*
 *  v
 * <--p
 */
void partition_line_test_upleft_of_left(void)
{
  {
  // straight left
  partition_line origin_to_left( 0, 0, -1, 0);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_left.is_point_on_left(&v1));
  }

  {
  // crookedd left (up leaning)
  partition_line origin_to_left( 0, 0, -10, -1);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_left.is_point_on_left(&v1));
  }

  {
  // crookedd left (down leaning)
  partition_line origin_to_left( 0, 0, -10,  1);
  vertex v1(-1,-1); // point at (-1,-1)
  TEST_ASSERT(!origin_to_left.is_point_on_left(&v1));
  }
}

void partition_line_test(void)
{
  partition_line_test_upleft_of_up();
  partition_line_test_upleft_of_down();
  partition_line_test_upleft_of_right();
  partition_line_test_upleft_of_left();
}

