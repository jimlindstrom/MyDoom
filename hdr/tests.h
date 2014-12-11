#ifndef __TESTS_H
#define __TESTS_H

#include <stdio.h>

#define TEST_ASSERT(x) if(!(x)) { printf("TEST FAILED in %s (%s:%d)\n", __PRETTY_FUNCTION__, __FILE__, __LINE__); tests_inc_failures(); } else { tests_inc_successes(); }

#define TEST_ASSERT_EQUAL(x,y) if((x)!=(y)) { printf("TEST FAILED in %s (%s:%d), expected %.1f to == %.1f\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, (float)x, (float)y); tests_inc_failures(); } else { tests_inc_successes(); }

#define TEST_ASSERT_WITHIN(x,y1,y2) if((x)<(y1) || (x)>(y2)) { printf("TEST FAILED in %s (%s:%d), expected %.1f to be within [%.1f, %.1f]\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, (float)x, (float)y1, (float)y2); tests_inc_failures(); } else { tests_inc_successes(); }

void tests_run(void);
void tests_inc_failures(void);
void tests_inc_successes(void);

#endif
