#include <stdio.h>

#include "error.h"

static const char* get_error_msg(ErrorCode code) {
	switch(code) {
		case SUCCESS:
		    return NULL;  // No error
		case ERROR_TOO_MANY_ARGS:
		    return "Too many arguments provided.";
		case ERROR_TOO_FEW_ARGS:
		    return "Too few arguments provided.";
		case ERROR_INVALID_COMMAND:
		    return "Invalid command entered.";
		case ERROR_EXECUTION_FAILURE:
		    return "Execution failure occurred.";
		case ERROR_MEMORY_ALLOCATION:
		    return "Memory allocation failed.";
		default:
		    return "Unknown error code.";
	}
}

void print_error(int error_code) {
	fprintf(stderr, "%s[ERROR] %s%s\n", RED_COLOR, get_error_msg((ErrorCode)error_code), RESET_TEXT);
	return;
}

