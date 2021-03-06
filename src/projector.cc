#include <math.h>
#include <stdio.h>

#include "common.h"
#include "projector.h"
#include "tests.h"

projector __projector;
projector *_projector = &__projector; // GLOBAL

projector::projector()
: clip_l(&clip_l1, &clip_l2),
  clip_r(&clip_r1, &clip_r2)
{
  // initialize these.
  set_left_clipping_vector( &clip_l1, &clip_l2);
  set_right_clipping_vector(&clip_r1, &clip_r2);
}

void projector::set_screen_size(uint16_t _screen_width, uint16_t _screen_height)
{
  screen_width = _screen_width;
  screen_height = _screen_height;

  x_proj_scale = ((screen_width-1)/2.0) / tan(get_horiz_fov_radius());
}

float projector::get_horiz_fov_radius() const
{
  return DEG_TO_RAD(22.0);
} 

int16_t projector::project_horiz_angle_to_x(float angle) const
{
  return ((0.5*(screen_width-1)) - (x_proj_scale*tan(angle)));
}

float projector::unproject_x_to_horiz_angle(int16_t x) const
{
  return (atan2(-x + ((0.5*(screen_width-1))), x_proj_scale));
}

float projector::clip_horiz_angle_to_fov(float angle) const
{
  return MAX(-get_horiz_fov_radius(), MIN(get_horiz_fov_radius(), angle));
}

void projector::project_z_to_y(float z, float d, float *y0, float *dy) const
{
  d /= 1000; // FIXME....
  *y0 = -(z / d);
  *dy = *y0 / z;
  *y0 = *y0 + (screen_height/2);
}
// screen_y = -(map_z / (map_xy_dist/1000)) + (screen_h/2)
// screen_y = -(map_z / (map_xy_dist/1000)) + (screen_h/2)
// screen_y = -(map_z * (1000/map_xy_dist)) + (screen_h/2)
// screen_y = -1000*map_z/[(map_x^2)+(map_y^2)]^0.5 + (screen_h/2)

void projector::set_left_clipping_vector(vertex *clip_l1, vertex *clip_l2) const
{
  clip_l1->set_x(0.0);
  clip_l1->set_y(0.0);

  clip_l2->set_x(1.0);
  clip_l2->set_y(tan( get_horiz_fov_radius()));
}

void projector::set_right_clipping_vector(vertex *clip_r1, vertex *clip_r2) const
{
  clip_r1->set_x(0.0);
  clip_r1->set_y(0.0);

  clip_r2->set_x(1.0);
  clip_r2->set_y(tan(-get_horiz_fov_radius()));
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
  TEST_ASSERT_WITHIN(clip_l2.get_y(), 0.30,0.50);

  TEST_ASSERT_WITHIN(clip_r1.get_x(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_r1.get_y(), 0.0,0.0);
  TEST_ASSERT_WITHIN(clip_r2.get_x(), 0.99,1.01);
  TEST_ASSERT_WITHIN(clip_r2.get_y(), -0.75,-0.30);
}

void unprojector_test(void)
{
  int w=640, h=480;

  projector p;
  p.set_screen_size(w, h);

  float a1 = -0.3;
  int16_t x = p.project_horiz_angle_to_x(a1);
  float a2 = p.unproject_x_to_horiz_angle(x);
  TEST_ASSERT_WITHIN(a2, a1-0.2, a1+0.2);
}

void projector_test(void)
{
  projector p;
  int w=640, h=480;
  p.set_screen_size(w, h);

  TEST_ASSERT_WITHIN(p.project_horiz_angle_to_x( p.get_horiz_fov_radius()),  -1,  1);
  TEST_ASSERT_WITHIN(p.project_horiz_angle_to_x(0),                         319,321);
  TEST_ASSERT_WITHIN(p.project_horiz_angle_to_x(-p.get_horiz_fov_radius()), 638,640);
}

void projector_tests(void)
{
  projector_test();
  unprojector_test();
  projector_clip_vectors_test();
}

