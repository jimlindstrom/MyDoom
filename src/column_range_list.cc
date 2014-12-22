#include <stdlib.h>
#include <string.h>
#include "column_range_list.h"
#include "tests.h"

#include "common.h"

column_range_list::column_range_list()
{
  left_solid_range = NULL;
  first_nonsolid_range = NULL;
}

column_range_list::~column_range_list()
{
  wall_projection *cur_range, *next_range;

  cur_range = left_solid_range;
  while(cur_range)
  {
    next_range = cur_range->next_range;
    delete cur_range;
    cur_range = next_range;
  }

  cur_range = first_nonsolid_range;
  while(cur_range)
  {
    next_range = cur_range->next_range;
    delete cur_range;
    cur_range = next_range;
  }
}

bool column_range_list::insert_solid(wall_projection *new_range)
{
  new_range->next_range = NULL;

  if(left_solid_range == NULL)
  {
    left_solid_range = new_range;
    return true;
  }
  if(new_range->x_r <= left_solid_range->x_l)
  {
    new_range->next_range = left_solid_range;
    left_solid_range = new_range;
    return true;
  }

  wall_projection *cur_range = left_solid_range;
  while(cur_range)
  {
    if(cur_range->x_r <= new_range->x_l)
    {
      if(!cur_range->next_range || (new_range->x_r <= cur_range->next_range->x_l))
      {
        new_range->next_range = cur_range->next_range;
        cur_range->next_range = new_range;
        return true;
      }
    }

    cur_range = cur_range->next_range;
  }
  return false;
}

void column_range_list::insert_nonsolid(wall_projection *new_range)
{
  // just insert it at the beginning of the list, for simplicity's sake
  new_range->next_range = first_nonsolid_range;
  first_nonsolid_range = new_range;
}

wall_projection **column_range_list::clip_segment(segment_projection const *seg_proj,
                                                  int *num_clipped_crs)
{
  int max_ranges = 2;
  wall_projection **cr_ptrs = new wall_projection *[max_ranges];
  wall_projection *cur_range = left_solid_range;

  *num_clipped_crs = 0;

  int16_t xlc = seg_proj->x_l_c, xrc = seg_proj->x_r_c;

  //printf("\nstarting: [%d,%d]\n", xlc, xrc);
  while(cur_range && (xlc <= xrc))
  {
    //printf("iteration [%d,%d]\n", xlc, xrc);
    // allocate more pointers, if needed
    if(((*num_clipped_crs)+1) >= max_ranges)
    {
      wall_projection **new_cr_ptrs = new wall_projection *[max_ranges*2];
      memcpy(new_cr_ptrs, cr_ptrs, max_ranges*sizeof(wall_projection *));
      cr_ptrs = new_cr_ptrs;
      max_ranges *= 2;
    }

    // if there's a gap, and it's more than big enough, we're done.
    if(xrc < cur_range->x_l)
    {
      //printf("  Case 1: big enough gap. Adding [%d,%d]\n", xlc, xrc);
      (*num_clipped_crs)++;
      cr_ptrs[(*num_clipped_crs)-1] = new wall_projection;
      cr_ptrs[(*num_clipped_crs)-1]->x_l  = xlc;
      cr_ptrs[(*num_clipped_crs)-1]->x_r = xrc;
      cr_ptrs[(*num_clipped_crs)-1]->dist_l  = seg_proj->dist_l_c + ( (seg_proj->dist_r_c-seg_proj->dist_l_c) *
                                                                      (xlc - seg_proj->x_l_c)                 /
                                                                      (seg_proj->x_r_c   - seg_proj->x_l_c  ) );
      cr_ptrs[(*num_clipped_crs)-1]->dist_r  = seg_proj->dist_l_c + ( (seg_proj->dist_r_c-seg_proj->dist_l_c) *
                                                                      (xrc - seg_proj->x_l_c)                 /
                                                                      (seg_proj->x_r_c   - seg_proj->x_l_c  ) );
      if(seg_proj->is_opaque) { insert_solid(   cr_ptrs[(*num_clipped_crs)-1]); }
      else                    { insert_nonsolid(cr_ptrs[(*num_clipped_crs)-1]); }
      xlc = xrc + 1; // DONE
    }
    // okay, well is there *any* gap?
    else if(xlc < cur_range->x_l)
    {
      //printf("  Case 2: small gap. Adding [%d,%d]\n", xlc, cur_range->x_l-1);
      (*num_clipped_crs)++;
      cr_ptrs[(*num_clipped_crs)-1] = new wall_projection;
      cr_ptrs[(*num_clipped_crs)-1]->x_l  = xlc;
      cr_ptrs[(*num_clipped_crs)-1]->x_r = cur_range->x_l-1;
      cr_ptrs[(*num_clipped_crs)-1]->dist_l  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xlc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
      cr_ptrs[(*num_clipped_crs)-1]->dist_r  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*((cur_range->x_l-1) - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
      if(seg_proj->is_opaque) { insert_solid(   cr_ptrs[(*num_clipped_crs)-1]); }
      else                    { insert_nonsolid(cr_ptrs[(*num_clipped_crs)-1]); }
      xlc = cur_range->x_r + 1;
    }
    // no? then just advance the left past this range
    else
    {
      //printf("  Case 3: no gap. Advancing\n");
      xlc = MAX(xlc, cur_range->x_r + 1);
    }

    cur_range = cur_range->next_range;
  }

  // add any remaining, from after the right edge
  if(xlc <= xrc)
  {
    //printf("Post-iteration. Adding [%d,%d]\n", xlc, xrc);
    (*num_clipped_crs)++;
    cr_ptrs[(*num_clipped_crs)-1] = new wall_projection;
    cr_ptrs[(*num_clipped_crs)-1]->x_l  = xlc;
    cr_ptrs[(*num_clipped_crs)-1]->x_r = xrc;
    cr_ptrs[(*num_clipped_crs)-1]->dist_l  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xlc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
    cr_ptrs[(*num_clipped_crs)-1]->dist_r  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xrc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
    if(seg_proj->is_opaque) { insert_solid(   cr_ptrs[(*num_clipped_crs)-1]); }
    else                    { insert_nonsolid(cr_ptrs[(*num_clipped_crs)-1]); }
  }

  return cr_ptrs;
}

bool column_range_list::any_unclipped_columns_in_range(int16_t x_l, int16_t x_r) const
{
  wall_projection *cur_range = left_solid_range;

  while(cur_range && (x_l <= x_r))
  {
    // if there's a gap, and it's more than big enough, we're done.
    if(x_r < cur_range->x_l)
    {
      return true;
    }
    // okay, well is there *any* gap?
    else if(x_l < cur_range->x_l)
    {
      return true;
    }
    // no? then just advance the left past this range
    else
    {
      x_l = MAX(x_l, cur_range->x_r + 1);
    }

    cur_range = cur_range->next_range;
  }

  // add any remaining, from after the right edge
  if(x_l <= x_r)
  {
    return true;
  }

  return false;
}

wall_projection const *column_range_list::get_left_solid_range() const
{
  return left_solid_range;
}

wall_projection const *column_range_list::get_first_nonsolid_range() const
{
  return first_nonsolid_range;
}

/******************************************************************************
 * TETS
 ******************************************************************************/

#if 0
void column_range_list_insert_ordering_test(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3, *cr4;
  wall_projection const *cur_cr;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();
  cr4 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -8; cr3->x_right =  25;
  cr4->x_left =  30; cr4->x_right =  35;

  TEST_ASSERT(cr_list.insert_solid(cr2));
  TEST_ASSERT(cr_list.insert_solid(cr1));
  TEST_ASSERT(cr_list.insert_solid(cr4));
  TEST_ASSERT(cr_list.insert_solid(cr3));

  cur_cr = cr_list.get_left_solid_range();
  TEST_ASSERT(cur_cr != NULL);
  TEST_ASSERT(cur_cr->x_left == cr1->x_left);

  cur_cr = cur_cr->next_range;
  TEST_ASSERT(cur_cr->x_left == cr2->x_left);

  cur_cr = cur_cr->next_range;
  TEST_ASSERT(cur_cr->x_left == cr3->x_left);

  cur_cr = cur_cr->next_range;
  TEST_ASSERT(cur_cr->x_left == cr4->x_left);

  cur_cr = cur_cr->next_range;
  TEST_ASSERT(cur_cr == NULL);
}

void column_range_list_insert_overlap_test(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3, *cr4, *cr5;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();
  cr4 = new wall_projection();
  cr5 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -8; cr3->x_right =  25;
  cr4->x_left =  30; cr4->x_right =  35;

  cr5->x_left = -11; cr5->x_right =  -9;

  TEST_ASSERT(cr_list.insert_solid(cr2) == true);
  TEST_ASSERT(cr_list.insert_solid(cr1) == true);
  TEST_ASSERT(cr_list.insert_solid(cr4) == true);
  TEST_ASSERT(cr_list.insert_solid(cr3) == true);

  TEST_ASSERT(cr_list.insert_solid(cr5) == false);
}

void column_range_list_clip_test1(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3;
  wall_projection **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert_solid(cr1);
  cr_list.insert_solid(cr2);
  cr_list.insert_solid(cr3);

  x_left = -40; x_right = -31;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, x_right);
  delete[] clipped_crs;
}

void column_range_list_clip_test2(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3;
  wall_projection **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert_solid(cr1);
  cr_list.insert_solid(cr2);
  cr_list.insert_solid(cr3);

  x_left = 26; x_right = 30;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, x_right);
  delete[] clipped_crs;
}

void column_range_list_clip_test3(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3;
  wall_projection **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert_solid(cr1);
  cr_list.insert_solid(cr2);
  cr_list.insert_solid(cr3);

  x_left = -12; x_right = 10;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , -9);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, -4);
  delete[] clipped_crs;
}

void column_range_list_clip_test4(void)
{
  column_range_list cr_list;
  wall_projection *cr1, *cr2, *cr3;
  wall_projection **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new wall_projection();
  cr2 = new wall_projection();
  cr3 = new wall_projection();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert_solid(cr1);
  cr_list.insert_solid(cr2);
  cr_list.insert_solid(cr3);

  x_left = -32; x_right = 30;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 3);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , -32);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, -31);
  TEST_ASSERT_EQUAL(clipped_crs[1]->x_left ,  -9);
  TEST_ASSERT_EQUAL(clipped_crs[1]->x_right,  -4);
  TEST_ASSERT_EQUAL(clipped_crs[2]->x_left ,  26);
  TEST_ASSERT_EQUAL(clipped_crs[2]->x_right,  30);
  delete[] clipped_crs;
}
#endif

void column_range_list_test(void)
{
#if 0
  column_range_list_insert_ordering_test();
  column_range_list_insert_overlap_test();
  column_range_list_clip_test1();
  column_range_list_clip_test2();
  column_range_list_clip_test3();
  column_range_list_clip_test4();
#endif
}
