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

static uint16_t next_segment_num = 0; // for debug printing

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

/*********************************************************************************************/

wad_segment::wad_segment()
{
  _linedef = NULL;
  front_sector = back_sector = NULL;
}

wad_segment::~wad_segment()
{
}

bool wad_segment::read_from_lump_data(uint8_t const *lump_data)
{
  segment_num  = next_segment_num++; // for debug printing

  vertex_l_num = *((uint16_t*)lump_data); lump_data += 2;
  vertex_r_num = *((uint16_t*)lump_data); lump_data += 2;
  angle =(float)(*(( int16_t*)lump_data))/256.0; lump_data += 2;
  linedef_num  = *((uint16_t*)lump_data); lump_data += 2;
  direction    = *((uint16_t*)lump_data); lump_data += 2;
  offset       = *((uint16_t*)lump_data); lump_data += 2;

  // convert angle from degrees to radians
  angle = DEG_TO_RAD(angle); // FIXME: I'm not sure I use this anywhere...

  return true;
}

void wad_segment::set_linedef(linedef const *ld)
{
  _linedef = ld;
}

bool wad_segment::is_singled_sided_line(void) const
{
  return (back_sector == NULL);
}

bool wad_segment::is_closed_door(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_ceiling_height() <= front_sector->get_floor_height()  ) ||
         (back_sector->get_floor_height()   >= front_sector->get_ceiling_height());
}

bool wad_segment::is_window(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }

  return (back_sector->get_ceiling_height() != front_sector->get_ceiling_height()) ||
         (back_sector->get_floor_height()   != front_sector->get_floor_height()  );
}

bool wad_segment::is_empty_line(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }
  if(is_window())             { return false; }
 
  return (back_sector->get_ceiling_texture() == front_sector->get_ceiling_texture()) &&
         (back_sector->get_floor_texture()   == front_sector->get_floor_texture()  ) &&
         (back_sector->get_light_level()     == front_sector->get_light_level()    ) &&
         (!_linedef->get_sidedef(direction)->has_mid_texture());
}

bool wad_segment::is_other_single_sided_line(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }
  if(is_window())             { return false; }
  if(is_empty_line())         { return false; }

  return true;
}

bool wad_segment::is_same_floor_plane_on_both_sides(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_floor_height()  == front_sector->get_floor_height()) &&
         (back_sector->get_floor_texture() == front_sector->get_floor_texture()) &&
         (back_sector->get_light_level()   == front_sector->get_light_level());
}

bool wad_segment::is_same_ceiling_plane_on_both_sides(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_ceiling_height()  == front_sector->get_ceiling_height()) &&
         (back_sector->get_ceiling_texture() == front_sector->get_ceiling_texture()) &&
         (back_sector->get_light_level()     == front_sector->get_light_level());
}

void wad_segment::project(column_range_list *col_ranges, projector const *_projector, player const *_player,
                          segment_projection *proj) const
{
  proj->is_visible = false;

  // quickly reject empty lines, back faces, lines outside/behind FOV
  calculate_angles_from_player(_player, &proj->ang_l, &proj->ang_r);
  if(is_empty_line() ||
     is_backface(proj->ang_l, proj->ang_r) ||
     is_outside_fov(proj->ang_l, proj->ang_r, _projector->get_horiz_fov_radius()))
  {
    return;
  }

  debug_printf("  segment %d: (%.1f,%.1f)->(%.1f,%.1f)\n",
               segment_num,
               vertex_l->get_x(), vertex_l->get_y(),
               vertex_r->get_x(), vertex_r->get_y() ); 
  debug_printf("    angles: [%.1f,%.1f]\n", RAD_TO_DEG(proj->angle_l), RAD_TO_DEG(proj->angle_r));

  // If not a solid line segment, don't consider the columns completely occluded. (continue drawing further-back segments)
  if(is_window() || is_other_single_sided_line()) { proj->store_clipping = false; }
  else                                            { proj->store_clipping = true;  }

  // If the back sector has the same floor or ceiling, dont' clip the cooresponding plane
  proj->clip_floor = proj->clip_ceiling = true;
  if(!is_closed_door() && is_same_floor_plane_on_both_sides()  ) { proj->clip_floor   = false; }
  if(!is_closed_door() && is_same_ceiling_plane_on_both_sides()) { proj->clip_ceiling = false; }

  // step 1: translate segment's verticies into player-centric map coordinates
  vertex _pvl(vertex_l); _pvl.subtract(_player->get_map_position()); _pvl.rotate(-_player->get_facing_angle());
  vertex _pvr(vertex_r); _pvr.subtract(_player->get_map_position()); _pvr.rotate(-_player->get_facing_angle());
  segment seg(&_pvl, &_pvr);

  // Step 2: clip it 
  vector const *clip_l = _projector->get_left_clipping_vector();
  vector const *clip_r = _projector->get_right_clipping_vector();
  seg.clip_to_vectors(clip_l, clip_r, &proj->v_l_c, &proj->v_r_c, &proj->u_l_c, &proj->u_r_c);

  // Step 3: Project it
  vertex origin(0,0);
  proj->ang_l_c  = origin.angle_to_point(&proj->v_l_c); 
  proj->ang_r_c  = origin.angle_to_point(&proj->v_r_c); 
  proj->x_l_c    = _projector->project_horiz_angle_to_x(proj->ang_l_c);
  proj->x_r_c    = _projector->project_horiz_angle_to_x(proj->ang_r_c);
  proj->dist_l_c = origin.distance_to_point(&proj->v_l_c);
  proj->dist_r_c = origin.distance_to_point(&proj->v_r_c);

  // guard against zero-width segments
  if(proj->x_r_c <= proj->x_l_c) { return; } // FIXME: how could this happen?

  proj->is_visible = true;
}

void wad_segment::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player,
                                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  segment_projection seg_proj;
  wall_projection **wall_projs;
  int num_wall_projs;

  project(col_ranges, _projector, _player, &seg_proj);
  if(!seg_proj.is_visible)
  {
    return;
  }

  float seg_len = get_length(); 
  float seg_off = _linedef->get_start_vertex()->distance_to_point(vertex_l);
  if(direction == 1) { seg_off = seg_len - seg_off; } // FIXME: why am I reversing this? seems bad...

  wall_projs = col_ranges->clip_segment(&seg_proj, &num_wall_projs);
  for(int i=0; i<num_wall_projs; i++)
  {
    wall_projs[i]->project_vertically(_projector, _player);

    float t_l = seg_proj.u_l_c + seg_proj.delta_u()*(wall_projs[i]->x_l - seg_proj.x_l_c)/seg_proj.delta_x();
    float t_r = seg_proj.u_l_c + seg_proj.delta_u()*(wall_projs[i]->x_r - seg_proj.x_l_c)/seg_proj.delta_x();
    wall_projs[i]->ldx_l = seg_off + (seg_len*t_l);
    wall_projs[i]->ldx_r = seg_off + (seg_len*t_r);

    if(floor)   { floor   = vp->adjust_or_create(floor,   wall_projs[i]->x_l, wall_projs[i]->x_r); }
    if(ceiling) { ceiling = vp->adjust_or_create(ceiling, wall_projs[i]->x_l, wall_projs[i]->x_r); }

    wall_projs[i]->clip_floor   = seg_proj.clip_floor;
    wall_projs[i]->clip_ceiling = seg_proj.clip_ceiling;
    wall_projs[i]->light_level  = front_sector->get_light_level();
    wall_projs[i]->vp           = vp;
    wall_projs[i]->floor        = floor;
    wall_projs[i]->ceiling      = ceiling;

    _linedef->render(direction, wall_projs[i]);
  }
  delete[] wall_projs;
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

bool wad_segment::is_backface(float angle_l, float angle_r) const
{
  #define ANGLE_EPSILON (5.0) // just small enough to avoid weird near-infinity isssues
  return (angle_r > angle_l) || ((angle_l - angle_r) > DEG_TO_RAD(180.0 - ANGLE_EPSILON));
}

bool wad_segment::is_outside_fov(float angle_l, float angle_r, float horiz_fov_radius) const
{
  return ( ( (angle_l < -horiz_fov_radius) && (angle_r < -horiz_fov_radius) ) ||
           ( (angle_l >  horiz_fov_radius) && (angle_r >  horiz_fov_radius) ) );
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
