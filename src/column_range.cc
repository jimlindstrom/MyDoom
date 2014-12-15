#include <stdlib.h>
#include <string.h>
#include "column_range.h"
#include "tests.h"

#include "common.h"

column_range_list::column_range_list()
{
  left_range = NULL;
}

column_range_list::~column_range_list()
{
  column_range *cur_range = left_range, *next_range;;
  while(cur_range)
  {
    next_range = cur_range->next_range;
    delete cur_range;
    cur_range = next_range;
  }
}

bool column_range_list::insert(column_range *new_range)
{
  new_range->next_range = NULL;

  if(left_range == NULL)
  {
    left_range = new_range;
    return true;
  }
  if(new_range->x_right <= left_range->x_left)
  {
    new_range->next_range = left_range;
    left_range = new_range;
    return true;
  }

  column_range *cur_range = left_range;
  while(cur_range)
  {
    if(cur_range->x_right <= new_range->x_left)
    {
      if(!cur_range->next_range || (new_range->x_right <= cur_range->next_range->x_left))
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

column_range **column_range_list::clip_segment(bool store_clipping, int16_t x_left, int16_t x_right, int *num_clipped_crs)
{
  int max_ranges = 2;
  column_range **cr_ptrs = new column_range *[max_ranges];
  column_range *cur_range = left_range;

  *num_clipped_crs = 0;

  //printf("\nstarting: [%d,%d]\n", x_left, x_right);
  while(cur_range && (x_left <= x_right))
  {
    //printf("iteration [%d,%d]\n", x_left, x_right);
    // allocate more pointers, if needed
    if(((*num_clipped_crs)+1) >= max_ranges)
    {
      column_range **new_cr_ptrs = new column_range *[max_ranges*2];
      memcpy(new_cr_ptrs, cr_ptrs, max_ranges*sizeof(column_range *));
      cr_ptrs = new_cr_ptrs;
      max_ranges *= 2;
    }

    // if there's a gap, and it's more than big enough, we're done.
    if(x_right < cur_range->x_left)
    {
      //printf("  Case 1: big enough gap. Adding [%d,%d]\n", x_left, x_right);
      (*num_clipped_crs)++;
      cr_ptrs[(*num_clipped_crs)-1] = new column_range;
      cr_ptrs[(*num_clipped_crs)-1]->x_left  = x_left;
      cr_ptrs[(*num_clipped_crs)-1]->x_right = x_right;
      if(store_clipping) { insert(cr_ptrs[(*num_clipped_crs)-1]); }
      x_left = x_right + 1; // DONE
    }
    // okay, well is there *any* gap?
    else if(x_left < cur_range->x_left)
    {
      //printf("  Case 2: small gap. Adding [%d,%d]\n", x_left, cur_range->x_left-1);
      (*num_clipped_crs)++;
      cr_ptrs[(*num_clipped_crs)-1] = new column_range;
      cr_ptrs[(*num_clipped_crs)-1]->x_left  = x_left;
      cr_ptrs[(*num_clipped_crs)-1]->x_right = cur_range->x_left-1;
      if(store_clipping) { insert(cr_ptrs[(*num_clipped_crs)-1]); }
      x_left = cur_range->x_right + 1;
    }
    // no? then just advance the left past this range
    else
    {
      //printf("  Case 3: no gap. Advancing\n");
      x_left = MAX(x_left, cur_range->x_right + 1);
    }

    cur_range = cur_range->next_range;
  }

  // add any remaining, from after the right edge
  if(x_left <= x_right)
  {
    //printf("Post-iteration. Adding [%d,%d]\n", x_left, x_right);
    (*num_clipped_crs)++;
    cr_ptrs[(*num_clipped_crs)-1] = new column_range;
    cr_ptrs[(*num_clipped_crs)-1]->x_left  = x_left;
    cr_ptrs[(*num_clipped_crs)-1]->x_right = x_right;
    if(store_clipping) { insert(cr_ptrs[(*num_clipped_crs)-1]); }
  }

  return cr_ptrs;
}

bool column_range_list::any_unclipped_columns_in_range(int16_t x_left, int16_t x_right) const
{
  column_range *cur_range = left_range;

  while(cur_range && (x_left <= x_right))
  {
    // if there's a gap, and it's more than big enough, we're done.
    if(x_right < cur_range->x_left)
    {
      return true;
    }
    // okay, well is there *any* gap?
    else if(x_left < cur_range->x_left)
    {
      return true;
    }
    // no? then just advance the left past this range
    else
    {
      x_left = MAX(x_left, cur_range->x_right + 1);
    }

    cur_range = cur_range->next_range;
  }

  // add any remaining, from after the right edge
  if(x_left <= x_right)
  {
    return true;
  }

  return false;
}

column_range const *column_range_list::get_left_range() const
{
  return left_range;
}

/******************************************************************************
 * TETS
 ******************************************************************************/

void column_range_list_insert_ordering_test(void)
{
  column_range_list cr_list;
  column_range *cr1, *cr2, *cr3, *cr4;
  column_range const *cur_cr;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();
  cr4 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -8; cr3->x_right =  25;
  cr4->x_left =  30; cr4->x_right =  35;

  TEST_ASSERT(cr_list.insert(cr2));
  TEST_ASSERT(cr_list.insert(cr1));
  TEST_ASSERT(cr_list.insert(cr4));
  TEST_ASSERT(cr_list.insert(cr3));

  cur_cr = cr_list.get_left_range();
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
  column_range *cr1, *cr2, *cr3, *cr4, *cr5;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();
  cr4 = new column_range();
  cr5 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -8; cr3->x_right =  25;
  cr4->x_left =  30; cr4->x_right =  35;

  cr5->x_left = -11; cr5->x_right =  -9;

  TEST_ASSERT(cr_list.insert(cr2) == true);
  TEST_ASSERT(cr_list.insert(cr1) == true);
  TEST_ASSERT(cr_list.insert(cr4) == true);
  TEST_ASSERT(cr_list.insert(cr3) == true);

  TEST_ASSERT(cr_list.insert(cr5) == false);
}

void column_range_list_clip_test1(void)
{
  column_range_list cr_list;
  column_range *cr1, *cr2, *cr3;
  column_range **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert(cr1);
  cr_list.insert(cr2);
  cr_list.insert(cr3);

  x_left = -40; x_right = -31;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, x_right);
  delete[] clipped_crs;
}

void column_range_list_clip_test2(void)
{
  column_range_list cr_list;
  column_range *cr1, *cr2, *cr3;
  column_range **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert(cr1);
  cr_list.insert(cr2);
  cr_list.insert(cr3);

  x_left = 26; x_right = 30;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , x_left);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, x_right);
  delete[] clipped_crs;
}

void column_range_list_clip_test3(void)
{
  column_range_list cr_list;
  column_range *cr1, *cr2, *cr3;
  column_range **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert(cr1);
  cr_list.insert(cr2);
  cr_list.insert(cr3);

  x_left = -12; x_right = 10;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, &num_clipped_crs);
  TEST_ASSERT(clipped_crs != NULL);
  TEST_ASSERT_EQUAL(num_clipped_crs, 1);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_left , -9);
  TEST_ASSERT_EQUAL(clipped_crs[0]->x_right, -4);
  delete[] clipped_crs;
}

void column_range_list_clip_test4(void)
{
  column_range_list cr_list;
  column_range *cr1, *cr2, *cr3;
  column_range **clipped_crs;
  int num_clipped_crs;
  int x_left, x_right;

  cr1 = new column_range();
  cr2 = new column_range();
  cr3 = new column_range();

  cr1->x_left = -30; cr1->x_right = -25;
  cr2->x_left = -24; cr2->x_right = -10;
  cr3->x_left =  -3; cr3->x_right =  25;

  cr_list.insert(cr1);
  cr_list.insert(cr2);
  cr_list.insert(cr3);

  x_left = -32; x_right = 30;
  clipped_crs = cr_list.clip_segment(true, x_left, x_right, &num_clipped_crs);
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

void column_range_list_test(void)
{
  column_range_list_insert_ordering_test();
  column_range_list_insert_overlap_test();
  column_range_list_clip_test1();
  column_range_list_clip_test2();
  column_range_list_clip_test3();
  column_range_list_clip_test4();
}
