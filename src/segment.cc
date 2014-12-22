#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "segment.h"
#include "vector.h"
#include "tests.h"
#include "common.h"

//#define DEBUG_PRINTING
#include "debug.h"

#define FLATNESS_EPSILON 0.00001

segment::segment()
{
  vertex_r = vertex_l = _vertex_r = _vertex_l = NULL;
}

segment::segment(vertex const *vl, vertex const *vr)
{
  vertex_l = vl;
  vertex_r = vr;
}

segment::~segment()
{
  if(_vertex_l) { delete _vertex_l; }
  if(_vertex_r) { delete _vertex_r; }
}

bool segment::is_vertical(void) const
{
  float dx = vertex_r->get_x() - vertex_l->get_x();
  return ((dx > -FLATNESS_EPSILON) && (dx < FLATNESS_EPSILON));
}

bool segment::is_horizontal(void) const
{
  float dy = vertex_r->get_y() - vertex_l->get_y();
  return ((dy > -FLATNESS_EPSILON) && (dy < FLATNESS_EPSILON));
}

float segment::get_length(void) const
{
  return vertex_l->distance_to_point(vertex_r);
}

float segment::get_slope(void) const
{
  float dy = vertex_r->get_y() - vertex_l->get_y();
  float dx = vertex_r->get_x() - vertex_l->get_x();
  return dy / dx;
}

void segment::get_slope_and_y_intercept(float *slope, float *y_intercept) const
{
  *slope       = get_slope();
  *y_intercept = vertex_l->get_y() - (*slope * vertex_l->get_x());
}

bool segment::get_intersection_with_vector(vector const *vec, vertex *ver, float *u) const
{
  if(!is_vertical())
  {
    if(!vec->is_vertical())
    {
      float m1,b1, m2,b2;
      get_slope_and_y_intercept(&m1, &b1);
      vec->get_slope_and_y_intercept(&m2, &b2);
  
      float x = (b2 - b1) / (m1 - m2);
      float y = m1*x + b1;
      ver->set_x(x); ver->set_y(y);
  
      *u = (x - vertex_l->get_x()) / (vertex_r->get_x() - vertex_l->get_x());
      return true;
    }
    else
    {
      float m1,b1;
      get_slope_and_y_intercept(&m1, &b1);
      float x = vec->get_vertex_1()->get_x();
  
      float y = m1*x + b1;
      ver->set_x(x); ver->set_y(y);
  
      *u = (x - vertex_l->get_x()) / (vertex_r->get_x() - vertex_l->get_x());
      return true;
    }
  }
  else // is vertical: x=c
  {
    if(!vec->is_vertical())
    {
      float x = vertex_l->get_x();
      float m2,b2;
      vec->get_slope_and_y_intercept(&m2, &b2);
  
      float y = m2*x + b2;
      ver->set_x(x); ver->set_y(y);
  
      *u = (y - vertex_l->get_y()) / (vertex_r->get_y() - vertex_l->get_y());
      return true;
    }
    else
    {
      return false; // parallel lines
    }
  }
}

void segment::clip_to_vectors(vector const *clip_l, vector const *clip_r,
                              vertex *v_l_c, vertex *v_r_c,
                              float *u_l_c, float *u_r_c) const
{
  vertex v;
  bool did_set;
  float u_l, u_r;

  did_set = false;
  if(get_intersection_with_vector(clip_l, &v, &u_l))
  {
    if((u_l >= 0.0) && (u_l <= 1.0))
    {
      if((v.get_x() >= 0.0) && (v.get_y() >= 0))
      {
        v_l_c->set_to(&v);
        *u_l_c = u_l;
        did_set = true;
      }
    }
  }
  if(!did_set)
  {
    v_l_c->set_to(vertex_l);
    *u_l_c = 0.0;
  }

  did_set = false;
  if(get_intersection_with_vector(clip_r, &v, &u_r))
  {
    if((u_r >= 0.0) && (u_r <= 1.0))
    {
      if((v.get_x() >= 0.0) && (v.get_y() <= 0))
      {
        v_r_c->set_to(&v);
        *u_r_c = u_r;
        did_set = true;
      }
    }
  }
  if(!did_set)
  {
    v_r_c->set_to(vertex_r);
    *u_r_c = 1.0;
  }

  debug_printf("    u: [%.3f, %.3f] clipped to [%.3f, %.3f]\n", u_l, u_r, *u_l_c, *u_r_c);
}

segment *segment::transform_origin(vertex const *new_origin, float new_ang) const
{
  vertex *vl = new vertex(vertex_l); vl->subtract(new_origin); vl->rotate(-new_ang);
  vertex *vr = new vertex(vertex_r); vr->subtract(new_origin); vr->rotate(-new_ang);

  segment *s = new segment();
  s->add_vertex_l(vl);
  s->add_vertex_r(vr);

  return s;
}

/******************************************************************************
 * TESTS
 ******************************************************************************/

void segment_test_line_intersect1(void)
{
  vertex v1, v2;
  v1.set_x(0);  v1.set_y(0);
  v2.set_x(0);  v2.set_y(1);
  vector vec;
  vec.set_vertex_1(&v1);
  vec.set_vertex_2(&v2);

  vertex v3, v4;
  v3.set_x(5);  v3.set_y(5+2);
  v4.set_x(10); v4.set_y(10+2);
  segment s;
  s.set_vertex_l(&v3);
  s.set_vertex_r(&v4);

  vertex v;
  float u;
  bool lines_intersect = s.get_intersection_with_vector(&vec, &v, &u);
  float expected_u = -v.distance_to_point(&v3) / s.get_length();

  TEST_ASSERT(lines_intersect);
  TEST_ASSERT_WITHIN(v.get_x(), -0.01,0.01);
  TEST_ASSERT_WITHIN(v.get_y(),  1.99,2.01);
  TEST_ASSERT_WITHIN(u,         expected_u-0.01,expected_u+0.01);
}

void segment_test_line_intersect2(void)
{
  vertex v1, v2;
  v1.set_x(0);  v1.set_y(0);
  v2.set_x(1);  v2.set_y(1);
  vector vec;
  vec.set_vertex_1(&v1);
  vec.set_vertex_2(&v2);

  vertex v3, v4;
  v3.set_x(0);  v3.set_y(10);
  v4.set_x(5);  v4.set_y(5);
  segment s;
  s.set_vertex_l(&v3);
  s.set_vertex_r(&v4);

  vertex v;
  float u;
  bool lines_intersect = s.get_intersection_with_vector(&vec, &v, &u);
  float expected_u = 1.0;

  TEST_ASSERT(lines_intersect);
  TEST_ASSERT_WITHIN(v.get_x(),  4.99,5.01);
  TEST_ASSERT_WITHIN(v.get_y(),  4.99,5.01);
  TEST_ASSERT_WITHIN(u,         expected_u-0.01,expected_u+0.01);
}

void segment_test_line_eq(void)
{
  float b = -9.3, m = 3.8;
  float b2, m2;

  vertex v1, v2;
  v1.set_x(-3);
  v1.set_y((m * v1.get_x()) + b);

  v2.set_x(10);
  v2.set_y((m * v2.get_x()) + b);

  segment s;
  s.set_vertex_l(&v1);
  s.set_vertex_r(&v2);

  s.get_slope_and_y_intercept(&m2, &b2);

  TEST_ASSERT_WITHIN(m2, m-0.001, m+0.001);
  TEST_ASSERT_WITHIN(b2, b-0.001, b+0.001);
}

void segment_simple_clip_test(void)
{
  // segment: two points down the x axis, just above/below it.
  vertex v_l, v_r, v_l_c, v_r_c;
  v_l.set_x(10); v_l.set_y( 1); // NOTE: it's assumed these are translated and scaled to player POV
  v_r.set_x(10); v_r.set_y(-1); // i.e., assume player is at (0,), looking along the positive x vector

  // setup the segment
  segment s;
  s.set_vertex_l(&v_l);
  s.set_vertex_r(&v_r);

  // set up clipping lines at +/-45 degrees
  vector clip_l, clip_r;
  vertex o(0,0), clip_l_vertex, clip_r_vertex;
  clip_l_vertex.set_from_angle_and_radius( 45.0, 1.0);
  clip_r_vertex.set_from_angle_and_radius(-45.0, 1.0);
  clip_l.set_vertex_1(&o);
  clip_l.set_vertex_2(&clip_l_vertex);
  clip_r.set_vertex_1(&o);
  clip_r.set_vertex_2(&clip_r_vertex);

  // clip the segment
  float u_l_c, u_r_c;
  s.clip_to_vectors(&clip_l, &clip_r, &v_l_c, &v_r_c, &u_l_c, &u_r_c);

  // expect that the left edge is unclipped
  TEST_ASSERT_WITHIN(v_l_c.get_x(), v_l.get_x()-0.01, v_l.get_x()+0.01);
  TEST_ASSERT_WITHIN(v_l_c.get_y(), v_l.get_y()-0.01, v_l.get_y()+0.01);

  // expect that the right edge is unclipped
  TEST_ASSERT_WITHIN(v_r_c.get_x(), v_r.get_x()-0.01, v_r.get_x()+0.01);
  TEST_ASSERT_WITHIN(v_r_c.get_y(), v_r.get_y()-0.01, v_r.get_y()+0.01);

  // expect that the parameter goes 0 to 1
  TEST_ASSERT_WITHIN(u_l_c, -0.01,0.01);
  TEST_ASSERT_WITHIN(u_r_c,  0.99,1.01);
}

void segment_complex_clip_test(void)
{
  // segment: two points down the x axis, just above/below it.
  vertex v_l, v_r, v_l_c, v_r_c;
  v_l.set_x(10); v_l.set_y( 50); // NOTE: it's assumed these are translated and scaled to player POV
  v_r.set_x(10); v_r.set_y(-50); // i.e., assume player is at (0,), looking along the positive x vector

  // setup the segment
  segment s;
  s.set_vertex_l(&v_l);
  s.set_vertex_r(&v_r);

  // set up clipping lines at +/-45 degrees
  vector clip_l, clip_r;
  vertex o(0,0), clip_l_vertex, clip_r_vertex;
  clip_l_vertex.set_from_angle_and_radius( M_PI/4.0, 1.0);
  clip_r_vertex.set_from_angle_and_radius(-M_PI/4.0, 1.0);
  clip_l.set_vertex_1(&o);
  clip_l.set_vertex_2(&clip_l_vertex);
  clip_r.set_vertex_1(&o);
  clip_r.set_vertex_2(&clip_r_vertex);

  // clip the segment
  float u_l_c, u_r_c;
  s.clip_to_vectors(&clip_l, &clip_r, &v_l_c, &v_r_c, &u_l_c, &u_r_c);

  // expect that the left edge is clipped 
  TEST_ASSERT_WITHIN(v_l_c.get_x(), v_l.get_x()-0.01, v_l.get_x()+0.01);
  TEST_ASSERT_WITHIN(v_l_c.get_y(), 9.99,10.01);

  // expect that the right edge is clipped
  TEST_ASSERT_WITHIN(v_r_c.get_x(), v_r.get_x()-0.01, v_r.get_x()+0.01);
  TEST_ASSERT_WITHIN(v_r_c.get_y(), -10.01,-9.99);

  // expect that the parameter goes 0 to 1
  TEST_ASSERT_WITHIN(u_l_c, 0.39,0.41);
  TEST_ASSERT_WITHIN(u_r_c, 0.59,0.61);
}

void segment_clip_wall_on_right_test(void)
{
  // FIXME re-write text
}

void segment_clip_wall_on_left_test(void)
{
  // FIXME re-write text
}

void segment_tests(void)
{
  segment_test_line_intersect1();
  segment_test_line_intersect2();
  segment_test_line_eq();
  segment_simple_clip_test();
  segment_complex_clip_test();
  segment_clip_wall_on_right_test();
  segment_clip_wall_on_left_test();
}
