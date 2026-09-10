#include "debug.h"

#ifdef CLANK_DEBUG

void _print_debug(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	printf("%s[DEBUG] ", YELLOW_COLOR);
	vprintf(fmt, args);
	printf("%s\n", RESET_TEXT);
	va_end(args);
}

#endif // CLANK_DEBUG
