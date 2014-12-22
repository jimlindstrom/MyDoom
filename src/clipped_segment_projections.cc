#include <stdlib.h>
#include <string.h>
#include "clipped_segment_projections.h"
#include "tests.h"

#include "common.h"

clipped_segment_projections::clipped_segment_projections()
{
  left_solid_csp = NULL;
  first_nonsolid_csp = NULL;
}

clipped_segment_projections::~clipped_segment_projections()
{
  clipped_segment_projection *cur_csp, *next_csp;

  cur_csp = left_solid_csp;
  while(cur_csp)
  {
    next_csp = cur_csp->next_csp;
    delete cur_csp;
    cur_csp = next_csp;
  }

  cur_csp = first_nonsolid_csp;
  while(cur_csp)
  {
    next_csp = cur_csp->next_csp;
    delete cur_csp;
    cur_csp = next_csp;
  }
}

bool clipped_segment_projections::insert_solid(clipped_segment_projection *new_csp)
{
  new_csp->next_csp = NULL;

  if(left_solid_csp == NULL)
  {
    left_solid_csp = new_csp;
    return true;
  }
  if(new_csp->x_r <= left_solid_csp->x_l)
  {
    new_csp->next_csp = left_solid_csp;
    left_solid_csp = new_csp;
    return true;
  }

  clipped_segment_projection *cur_csp = left_solid_csp;
  while(cur_csp)
  {
    if(cur_csp->x_r <= new_csp->x_l)
    {
      if(!cur_csp->next_csp || (new_csp->x_r <= cur_csp->next_csp->x_l))
      {
        new_csp->next_csp = cur_csp->next_csp;
        cur_csp->next_csp = new_csp;
        return true;
      }
    }

    cur_csp = cur_csp->next_csp;
  }
  return false;
}

void clipped_segment_projections::insert_nonsolid(clipped_segment_projection *new_csp)
{
  // just insert it at the beginning of the list, for simplicity's sake
  new_csp->next_csp = first_nonsolid_csp;
  first_nonsolid_csp = new_csp;
}

clipped_segment_projection **clipped_segment_projections::clip_segment(segment_projection const *seg_proj,
                                                  int *num_clipped_csp)
{
  int max_csps = 2;
  clipped_segment_projection **csp_ptrs = new clipped_segment_projection *[max_csps];
  clipped_segment_projection *cur_csp = left_solid_csp;

  *num_clipped_csp = 0;

  int16_t xlc = seg_proj->x_l_c, xrc = seg_proj->x_r_c;

  //printf("\nstarting: [%d,%d]\n", xlc, xrc);
  while(cur_csp && (xlc <= xrc))
  {
    //printf("iteration [%d,%d]\n", xlc, xrc);
    // allocate more pointers, if needed
    if(((*num_clipped_csp)+1) >= max_csps)
    {
      clipped_segment_projection **new_csp_ptrs = new clipped_segment_projection *[max_csps*2];
      memcpy(new_csp_ptrs, csp_ptrs, max_csps*sizeof(clipped_segment_projection *));
      csp_ptrs = new_csp_ptrs;
      max_csps *= 2;
    }

    // if there's a gap, and it's more than big enough, we're done.
    if(xrc < cur_csp->x_l)
    {
      //printf("  Case 1: big enough gap. Adding [%d,%d]\n", xlc, xrc);
      (*num_clipped_csp)++;
      csp_ptrs[(*num_clipped_csp)-1] = new clipped_segment_projection;
      csp_ptrs[(*num_clipped_csp)-1]->x_l  = xlc;
      csp_ptrs[(*num_clipped_csp)-1]->x_r = xrc;
      csp_ptrs[(*num_clipped_csp)-1]->dist_l  = seg_proj->dist_l_c + ( (seg_proj->dist_r_c-seg_proj->dist_l_c) *
                                                                      (xlc - seg_proj->x_l_c)                 /
                                                                      (seg_proj->x_r_c   - seg_proj->x_l_c  ) );
      csp_ptrs[(*num_clipped_csp)-1]->dist_r  = seg_proj->dist_l_c + ( (seg_proj->dist_r_c-seg_proj->dist_l_c) *
                                                                      (xrc - seg_proj->x_l_c)                 /
                                                                      (seg_proj->x_r_c   - seg_proj->x_l_c  ) );
      if(seg_proj->is_opaque) { insert_solid(   csp_ptrs[(*num_clipped_csp)-1]); }
      else                    { insert_nonsolid(csp_ptrs[(*num_clipped_csp)-1]); }
      xlc = xrc + 1; // DONE
    }
    // okay, well is there *any* gap?
    else if(xlc < cur_csp->x_l)
    {
      //printf("  Case 2: small gap. Adding [%d,%d]\n", xlc, cur_csp->x_l-1);
      (*num_clipped_csp)++;
      csp_ptrs[(*num_clipped_csp)-1] = new clipped_segment_projection;
      csp_ptrs[(*num_clipped_csp)-1]->x_l  = xlc;
      csp_ptrs[(*num_clipped_csp)-1]->x_r = cur_csp->x_l-1;
      csp_ptrs[(*num_clipped_csp)-1]->dist_l  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xlc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
      csp_ptrs[(*num_clipped_csp)-1]->dist_r  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*((cur_csp->x_l-1) - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
      if(seg_proj->is_opaque) { insert_solid(   csp_ptrs[(*num_clipped_csp)-1]); }
      else                    { insert_nonsolid(csp_ptrs[(*num_clipped_csp)-1]); }
      xlc = cur_csp->x_r + 1;
    }
    // no? then just advance the left past this csp
    else
    {
      //printf("  Case 3: no gap. Advancing\n");
      xlc = MAX(xlc, cur_csp->x_r + 1);
    }

    cur_csp = cur_csp->next_csp;
  }

  // add any remaining, from after the right edge
  if(xlc <= xrc)
  {
    //printf("Post-iteration. Adding [%d,%d]\n", xlc, xrc);
    (*num_clipped_csp)++;
    csp_ptrs[(*num_clipped_csp)-1] = new clipped_segment_projection;
    csp_ptrs[(*num_clipped_csp)-1]->x_l  = xlc;
    csp_ptrs[(*num_clipped_csp)-1]->x_r = xrc;
    csp_ptrs[(*num_clipped_csp)-1]->dist_l  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xlc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
    csp_ptrs[(*num_clipped_csp)-1]->dist_r  = seg_proj->dist_l_c + (seg_proj->dist_r_c-seg_proj->dist_l_c)*(xrc - seg_proj->x_l_c)/(seg_proj->x_r_c - seg_proj->x_l_c);
    if(seg_proj->is_opaque) { insert_solid(   csp_ptrs[(*num_clipped_csp)-1]); }
    else                    { insert_nonsolid(csp_ptrs[(*num_clipped_csp)-1]); }
  }

  return csp_ptrs;
}

bool clipped_segment_projections::any_unclipped_columns_in_range(int16_t x_l, int16_t x_r) const
{
  clipped_segment_projection *cur_csp = left_solid_csp;

  while(cur_csp && (x_l <= x_r))
  {
    // if there's a gap, and it's more than big enough, we're done.
    if(x_r < cur_csp->x_l)
    {
      return true;
    }
    // okay, well is there *any* gap?
    else if(x_l < cur_csp->x_l)
    {
      return true;
    }
    // no? then just advance the left past this csp
    else
    {
      x_l = MAX(x_l, cur_csp->x_r + 1);
    }

    cur_csp = cur_csp->next_csp;
  }

  // add any remaining, from after the right edge
  if(x_l <= x_r)
  {
    return true;
  }

  return false;
}

clipped_segment_projection const *clipped_segment_projections::get_left_solid_csp() const
{
  return left_solid_csp;
}

clipped_segment_projection const *clipped_segment_projections::get_first_nonsolid_csp() const
{
  return first_nonsolid_csp;
}

/******************************************************************************
 * TETS
 ******************************************************************************/

#if 0
void clipped_segment_projections_insert_ordering_test(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3, *csp4;
  clipped_segment_projection const *cur_csp;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();
  csp4 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -8; csp3->x_right =  25;
  csp4->x_left =  30; csp4->x_right =  35;

  TEST_ASSERT(csp_list.insert_solid(csp2));
  TEST_ASSERT(csp_list.insert_solid(csp1));
  TEST_ASSERT(csp_list.insert_solid(csp4));
  TEST_ASSERT(csp_list.insert_solid(csp3));

  cur_csp = csp_list.get_left_solid_csp();
  TEST_ASSERT(cur_csp != NULL);
  TEST_ASSERT(cur_csp->x_left == csp1->x_left);

  cur_csp = cur_csp->next_csp;
  TEST_ASSERT(cur_csp->x_left == csp2->x_left);

  cur_csp = cur_csp->next_csp;
  TEST_ASSERT(cur_csp->x_left == csp3->x_left);

  cur_csp = cur_csp->next_csp;
  TEST_ASSERT(cur_csp->x_left == csp4->x_left);

  cur_csp = cur_csp->next_csp;
  TEST_ASSERT(cur_csp == NULL);
}

void clipped_segment_projections_insert_overlap_test(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3, *csp4, *csp5;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();
  csp4 = new clipped_segment_projection();
  csp5 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -8; csp3->x_right =  25;
  csp4->x_left =  30; csp4->x_right =  35;

  csp5->x_left = -11; csp5->x_right =  -9;

  TEST_ASSERT(csp_list.insert_solid(csp2) == true);
  TEST_ASSERT(csp_list.insert_solid(csp1) == true);
  TEST_ASSERT(csp_list.insert_solid(csp4) == true);
  TEST_ASSERT(csp_list.insert_solid(csp3) == true);

  TEST_ASSERT(csp_list.insert_solid(csp5) == false);
}

void clipped_segment_projections_clip_test1(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3;
  clipped_segment_projection **clipped_csp;
  int num_clipped_csp;
  int x_left, x_right;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -3; csp3->x_right =  25;

  csp_list.insert_solid(csp1);
  csp_list.insert_solid(csp2);
  csp_list.insert_solid(csp3);

  x_left = -40; x_right = -31;
  clipped_csp = csp_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_csp);
  TEST_ASSERT(clipped_csp != NULL);
  TEST_ASSERT_EQUAL(num_clipped_csp, 1);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_right, x_right);
  delete[] clipped_csp;
}

void clipped_segment_projections_clip_test2(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3;
  clipped_segment_projection **clipped_csp;
  int num_clipped_csp;
  int x_left, x_right;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -3; csp3->x_right =  25;

  csp_list.insert_solid(csp1);
  csp_list.insert_solid(csp2);
  csp_list.insert_solid(csp3);

  x_left = 26; x_right = 30;
  clipped_csp = csp_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_csp);
  TEST_ASSERT(clipped_csp != NULL);
  TEST_ASSERT_EQUAL(num_clipped_csp, 1);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_right, x_right);
  delete[] clipped_csp;
}

void clipped_segment_projections_clip_test3(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3;
  clipped_segment_projection **clipped_csp;
  int num_clipped_csp;
  int x_left, x_right;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -3; csp3->x_right =  25;

  csp_list.insert_solid(csp1);
  csp_list.insert_solid(csp2);
  csp_list.insert_solid(csp3);

  x_left = -12; x_right = 10;
  clipped_csp = csp_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_csp);
  TEST_ASSERT(clipped_csp != NULL);
  TEST_ASSERT_EQUAL(num_clipped_csp, 1);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_left , -9);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_right, -4);
  delete[] clipped_csp;
}

void clipped_segment_projections_clip_test4(void)
{
  clipped_segment_projections csp_list;
  clipped_segment_projection *csp1, *csp2, *csp3;
  clipped_segment_projection **clipped_csp;
  int num_clipped_csp;
  int x_left, x_right;

  csp1 = new clipped_segment_projection();
  csp2 = new clipped_segment_projection();
  csp3 = new clipped_segment_projection();

  csp1->x_left = -30; csp1->x_right = -25;
  csp2->x_left = -24; csp2->x_right = -10;
  csp3->x_left =  -3; csp3->x_right =  25;

  csp_list.insert_solid(csp1);
  csp_list.insert_solid(csp2);
  csp_list.insert_solid(csp3);

  x_left = -32; x_right = 30;
  clipped_csp = csp_list.clip_segment(true, x_left, x_right, 0, 0, &num_clipped_csp);
  TEST_ASSERT(clipped_csp != NULL);
  TEST_ASSERT_EQUAL(num_clipped_csp, 3);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_left , -32);
  TEST_ASSERT_EQUAL(clipped_csp[0]->x_right, -31);
  TEST_ASSERT_EQUAL(clipped_csp[1]->x_left ,  -9);
  TEST_ASSERT_EQUAL(clipped_csp[1]->x_right,  -4);
  TEST_ASSERT_EQUAL(clipped_csp[2]->x_left ,  26);
  TEST_ASSERT_EQUAL(clipped_csp[2]->x_right,  30);
  delete[] clipped_csp;
}
#endif

void clipped_segment_projections_test(void)
{
#if 0
  clipped_segment_projections_insert_ordering_test();
  clipped_segment_projections_insert_overlap_test();
  clipped_segment_projections_clip_test1();
  clipped_segment_projections_clip_test2();
  clipped_segment_projections_clip_test3();
  clipped_segment_projections_clip_test4();
#endif
}
