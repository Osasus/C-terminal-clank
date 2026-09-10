#include <stdio.h>

int clank_exit (int argc, __attribute__((unused)) char* argv[]) {
	if (argc > 1) {
		printf("Incorrect usage! exit takes no arguments.\n");
		printf("Try: man exit\n");
		return 1;
	}
	printf("Goodbye fellow clankophobe!\n");
	return 3;
}

void man_exit(){
	printf("exits clank\n");
	printf("usage: exit\n");
	return;
}