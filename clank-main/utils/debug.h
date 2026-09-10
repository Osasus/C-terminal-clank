#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdio.h>
#include "colors.h"

#ifdef CLANK_DEBUG

#define PRINT_DEBUG(...) _print_debug (__VA_ARGS__)

void _print_debug(const char* fmt, ...); 

#else

#define PRINT_DEBUG(...)

#endif // CLANK_DEBUG

#endif // DEBUG_H
