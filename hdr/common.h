#ifndef __COMMON_H
#define __COMMON_H

#include <math.h> // for M_PI

#define MAX(x,y) ((x)>(y) ? (x) : (y))
#define MIN(x,y) ((x)<(y) ? (x) : (y))

#define DEG_TO_RAD(x) ((x)*M_PI/180.0)
#define RAD_TO_DEG(x) ((x)*180.0/M_PI)

#endif
