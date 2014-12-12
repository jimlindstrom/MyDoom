#include <math.h>
#include <stdio.h>
#include "projector.h"
#include "tests.h"

#define MAX(x,y) ((x)>(y) ? (x) : (y))
#define MIN(x,y) ((x)<(y) ? (x) : (y))

projector::projector()
{
}

void projector::set_screen_size(uint16_t _screen_width, uint16_t _screen_height)
{
  screen_width = _screen_width;
  screen_height = _screen_height;

  x_proj_scale = ((screen_width-1)/2.0) / tan(get_horiz_fov_radius()*M_PI/180.0); // FIXME: use rad
}

int16_t projector::get_horiz_fov_radius() const
{
  return 60;
} 

int16_t projector::project_horiz_angle_to_x(float angle) const
{
  return ((0.5*(screen_width-1)) + (x_proj_scale*tan(angle*M_PI/180.0))); // FIXME: use rad
}

float projector::unproject_x_to_horiz_angle(int16_t x) const
{
  return (atan2(x - ((0.5*(screen_width-1))), x_proj_scale) * 180.0/M_PI); // FIXME: use rad
}

float projector::clip_horiz_angle_to_fov(float angle) const // FIXME: this may no longer get used...
{
  return MAX(-get_horiz_fov_radius(), MIN(get_horiz_fov_radius(), angle));
}

void projector::set_left_clipping_vector(vertex *clip_l1, vertex *clip_l2) const
{
  clip_l1->set_x(0.0);
  clip_l1->set_y(0.0);

  clip_l2->set_x(1.0);
  clip_l2->set_y(tan( get_horiz_fov_radius()*M_PI/180.0));
}

void projector::set_right_clipping_vector(vertex *clip_r1, vertex *clip_r2) const
{
  clip_r1->set_x(0.0);
  clip_r1->set_y(0.0);

  clip_r2->set_x(1.0);
  clip_r2->set_y(tan(-get_horiz_fov_radius()*M_PI/180.0));
}

/******************************************************************************
 * TESTS
 ******************************************************************************/

void projector_clip_vectors_test(void)
{
  int w=640, h=480;

  projector p;
  p.set_screen_size(w, h);

  vertex clip_l1, clip_l2, clip_r1, clip_r2;
  p.set_left_clipping_vector( &clip_l1, &clip_l2);
  p.set_right_clipping_vector(&clip_r1, &clip_r2);

  TEST_ASSERT_WITHIN(clip_l1.get_x(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_l1.get_y(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_l2.get_x(), 0.99,1.01);
  TEST_ASSERT_WITHIN(clip_l2.get_y(), 1.73,1.74);

  TEST_ASSERT_WITHIN(clip_r1.get_x(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_r1.get_y(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_r2.get_x(), 0.99,1.01);
  TEST_ASSERT_WITHIN(clip_r2.get_y(), -1.74,-1.73);
}

void unprojector_test(void)
{
  int w=640, h=480;

  projector p;
  p.set_screen_size(w, h);

  float a1 = -33.3;
  int16_t x = p.project_horiz_angle_to_x(a1);
  float a2 = p.unproject_x_to_horiz_angle(x);
  TEST_ASSERT_WITHIN(a2, a1-0.1, a1+0.1);
}

void projector_test(void)
{
  int w=640, h=480;

  projector p;
  p.set_screen_size(w, h);

  /*
   * SCENARIO:
   * player at (777,-3307) facing 110
   * segment 0x7bbfde94: (896,-3104)->(896,-3360)
   *   angles:[-50.4, -134.0], x:[96, 511]
   *   1 clipped ranges
   *     clipped range 0: [96,511], t:[0.00,1.00]
   *       drawing (896,-3104)->(896,-3360)
   * segment 0x7bbfdeac: (704,-3360)->(704,-3104)
   *   angles:[106.0, -0.2], x:[-325, 319]
   *   1 clipped ranges
   *     clipped range 0: [-325,95], t:[0.00,0.65]
   *       drawing (704,-3360)->(704,-3193)
   */

  float a1 = -34.0;
  float a2 = -20.4;
  float a3 =  -0.2;
  float a4 =  16.0;

  TEST_ASSERT_LESS_THAN(p.project_horiz_angle_to_x(a1),
                        p.project_horiz_angle_to_x(a2));
  TEST_ASSERT_LESS_THAN(p.project_horiz_angle_to_x(a2),
                        p.project_horiz_angle_to_x(a3));
  TEST_ASSERT_LESS_THAN(p.project_horiz_angle_to_x(a3),
                        p.project_horiz_angle_to_x(a4));
}

void projector_tests(void)
{
  projector_test();
  unprojector_test();
  projector_clip_vectors_test();
}

