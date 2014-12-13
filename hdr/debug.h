#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef DEBUG_PRINTING
#define debug_printf(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define debug_printf(fmt, ...) { }
#endif

#endif
