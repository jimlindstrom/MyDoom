#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>

#ifdef DEBUG_PRINTING
#define debug_printf printf
#else
#define debug_printf(fmt, ...) { }
#endif

#endif
