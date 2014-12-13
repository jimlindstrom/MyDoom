#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "segment.h"
#include "vector.h"
#include "tests.h"

#define DEBUG_PRINTING
#include "debug.h"

#define FLATNESS_EPSILON 0.00001

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
      debug_printf("    intersection case 1\n");
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
      debug_printf("    intersection case 2\n");
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
      debug_printf("    intersection case 3\n");
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
        debug_printf("    clip left at %.3f\n", u_l);
        v_l_c->set_to(&v);
        *u_l_c = u_l;
        did_set = true;
      }
      else { debug_printf("    no clip left: in wrong quadrant\n"); }
    }
    else { debug_printf("    no clip left: outside [0, 1]\n"); }
  }
  else { debug_printf("    no clip left: non-intersecting\n"); }
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
        debug_printf("    clip right at %.3f\n", u_r);
        v_r_c->set_to(&v);
        *u_r_c = u_r;
        did_set = true;
      }
      else { debug_printf("    no clip right: in wrong quadrant\n"); }
    }
    else { debug_printf("    no clip right: outside [0, 1]\n"); }
  }
  else { debug_printf("    no clip right: non-intersecting\n"); }
  if(!did_set)
  {
    v_r_c->set_to(vertex_r);
    *u_r_c = 1.0;
  }

  debug_printf("    u: [%.3f, %.3f] clipped to [%.3f, %.3f]\n", u_l, u_r, *u_l_c, *u_r_c);
}

/*********************************************************************************************/

wad_segment::wad_segment()
{
}

wad_segment::~wad_segment()
{
}

bool wad_segment::read_from_lump_data(uint8_t const *lump_data)
{
  vertex_l_num = *((uint16_t*)lump_data); lump_data += 2;
  vertex_r_num = *((uint16_t*)lump_data); lump_data += 2;
  angle =(float)(*(( int16_t*)lump_data))/256.0; lump_data += 2;
  linedef_num  = *((uint16_t*)lump_data); lump_data += 2;
  direction    = *((uint16_t*)lump_data); lump_data += 2;
  offset       = *((uint16_t*)lump_data); lump_data += 2;

  // convert angle from degrees to radians
  angle = angle*M_PI/180.0;

  return true;
}

void wad_segment::set_linedef(linedef const *ld)
{
  _linedef = ld;
}

void wad_segment::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, overhead_map *omap) const
{
  vertex origin(0,0);

  debug_printf("  segment 0x%08x: (%.1f,%.1f)->(%.1f,%.1f)\n",
         (unsigned int)this, 
         vertex_l->get_x(), vertex_l->get_y(),
         vertex_r->get_x(), vertex_r->get_y() ); 

  float angle_r, angle_l;
  calculate_angles_from_player(_player, &angle_l, &angle_r);
  debug_printf("    angles: [%.1f,%.1f]\n", angle_l, angle_r);
  if(is_viewer_behind(_projector, angle_l, angle_r))
  {
    // This is the state in which we're just rendering the map view
    color_rgba red(255, 0, 0, 255);
    omap->draw_line(vertex_l, vertex_r, &red);
    return;
  }

  // step 1: translate it into player-centric coordinates
  vertex _pvl, _pvr;
  _pvl.set_to_a_minus_b(vertex_l, _player->get_map_position());
  _pvr.set_to_a_minus_b(vertex_r, _player->get_map_position());
  _pvl.rotate(-_player->get_facing_angle());
  _pvr.rotate(-_player->get_facing_angle());
  segment seg(&_pvl, &_pvr);
  debug_printf("    pv: (%.1f,%.1f)->(%.1f,%.1f)\n", _pvl.get_x(), _pvl.get_y(), _pvr.get_x(), _pvr.get_y()); 

  #if 0 // just for debugging purposes
  float _ang_l_c = origin.angle_to_point(&_pvl);
  float _ang_r_c = origin.angle_to_point(&_pvr);
  debug_printf("    angles: [%.1f,%.1f]\n", _ang_l_c, _ang_r_c);
  #endif

  // Step 2: clip it
  vector const *clip_l = _projector->get_left_clipping_vector();
  vector const *clip_r = _projector->get_right_clipping_vector();
  vertex v_l_c, v_r_c;
  float u_l_c, u_r_c;
  seg.clip_to_vectors(clip_l, clip_r, &v_l_c, &v_r_c, &u_l_c, &u_r_c);
  debug_printf("    v: (%.1f, %.1f)->(%.1f,%.1f)\n", v_l_c.get_x(), v_l_c.get_y(), v_r_c.get_x(), v_r_c.get_y());

  float ang_l_c = origin.angle_to_point(&v_l_c);
  float ang_r_c = origin.angle_to_point(&v_r_c);
  debug_printf("    clipped angles: [%.1f,%.1f]\n", ang_l_c, ang_r_c);
  float x_l_c = _projector->project_horiz_angle_to_x(ang_l_c);
  float x_r_c = _projector->project_horiz_angle_to_x(ang_r_c);
  debug_printf("    clipped x: [%.1f,%.1f]\n", x_l_c, x_r_c);

  // This is the state in which we're simulating actually rendering the wall in the player's view
  column_range **clipped_ranges;
  int num_clipped_crs;
  clipped_ranges = col_ranges->insert_with_clipping(x_l_c, x_r_c, &num_clipped_crs);
  debug_printf("    %d clipped ranges\n", num_clipped_crs);
  color_rgba grn(0, 255, 0, 255);

  vertex v1, v2, d;
  d.set_x(vertex_r->get_x() - vertex_l->get_x());
  d.set_y(vertex_r->get_y() - vertex_l->get_y());
  for(int i=0; i<num_clipped_crs; i++)
  {
    float t1 = (clipped_ranges[i]->x_left - x_l_c)/(float)(x_r_c-x_l_c);
    t1 = (t1*(u_r_c - u_l_c)) + u_l_c;
    v1.set_x(vertex_l->get_x() + t1*d.get_x());
    v1.set_y(vertex_l->get_y() + t1*d.get_y());
    float t2 = (clipped_ranges[i]->x_right- x_l_c)/(float)(x_r_c-x_l_c);
    t2 = (t2*(u_r_c - u_l_c)) + u_l_c;
    v2.set_x(vertex_l->get_x() + t2*d.get_x());
    v2.set_y(vertex_l->get_y() + t2*d.get_y());
    debug_printf("      clipped range %d: [%d,%d], t:[%.2f,%.2f]\n", i, clipped_ranges[i]->x_left, clipped_ranges[i]->x_right, t1, t2);
    debug_printf("        drawing (%.1f,%.1f)->(%.1f,%.1f)\n", v1.get_x(), v1.get_y(), v2.get_x(), v2.get_y());
    omap->draw_line(&v1, &v2, &grn);
  }
  delete[] clipped_ranges;
}

void wad_segment::calculate_angles_from_player(player const *_player, float *angle_l, float *angle_r) const
{
  *angle_l = _player->get_map_position()->angle_to_point(vertex_l) - _player->get_facing_angle();
  *angle_r = _player->get_map_position()->angle_to_point(vertex_r) - _player->get_facing_angle();

  if     (*angle_l >  M_PI) { *angle_l -= 2.0*M_PI; }
  else if(*angle_l < -M_PI) { *angle_l += 2.0*M_PI; }
  if     (*angle_r >  M_PI) { *angle_r -= 2.0*M_PI; }
  else if(*angle_r < -M_PI) { *angle_r += 2.0*M_PI; }
}

bool wad_segment::is_viewer_behind(projector const *_projector, float angle_l, float angle_r) const
{
  return ( 
           (angle_r > angle_l) ||
           ( 
             ( (angle_l < -_projector->get_horiz_fov_radius()) ||
               (angle_l >  _projector->get_horiz_fov_radius()) ) &&
             ( (angle_r < -_projector->get_horiz_fov_radius()) ||
               (angle_r >  _projector->get_horiz_fov_radius()) )
           ) 
         );
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
  wad_segment s;
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
  wad_segment s;
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
