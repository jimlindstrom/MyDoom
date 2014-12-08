#include <stdio.h>

#include "tests.h"
#include "partition_line.h"

static int num_tests_passed;
static int num_tests_failed;

void tests_run(void)
{
  num_tests_passed = 0;
  num_tests_failed = 0;

  partition_line_test();

  printf("%d of %d tests failed\n", num_tests_failed, num_tests_failed+num_tests_passed);
}

void tests_inc_failures(void)
{
  num_tests_failed++;
}

void tests_inc_successes(void)
{
  num_tests_passed++;
}

