#include <stdio.h>

#include "tests.h"
#include "partition_line.h"
#include "vertex.h"
#include "clipped_segment_projections.h"
#include "projector.h"
#include "segment.h"
#include "vector.h"
#include "thing.h"

static int num_tests_passed;
static int num_tests_failed;

void tests_run(void)
{
  num_tests_passed = 0;
  num_tests_failed = 0;

  projector_tests();
  partition_line_test();
  vertex_test();
  clipped_segment_projections_test();
  segment_tests();
  vector_tests();
  thing_tests();

  printf("\n---\n\n");
  if(num_tests_failed > 0)
  {
    printf("%d of %d tests failed\n", num_tests_failed, num_tests_failed+num_tests_passed);
  }
  else
  {
    printf("All %d tests passed\n", num_tests_failed+num_tests_passed);
  }
}

void tests_inc_failures(void)
{
  num_tests_failed++;
}

void tests_inc_successes(void)
{
  num_tests_passed++;
}

