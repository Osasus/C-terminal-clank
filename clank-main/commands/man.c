#include <stdio.h>
#include "build/commands.h"
#include <string.h>

int clank_man(int argc, char* argv[]){
	if(argc == 1) {
		printf("What man page do you want bro, try 'man <name>'\n");
		return 1;
	}

	if(argc > 2) {
		printf("Too many arguments, use as follows 'man <name>'\n");
		return 1;
	}

	for (int i = 0; commands[i].name != NULL; i++) {
		if (strcmp(commands[i].name, argv[1]) == 0) {
			commands[i].man();
			return 0;
		}
	}
	printf("%s is not a command\n", argv[1]);
	return 2;
}

void man_man(){
	printf("Prints the manual for a command\n");
	printf("usage: man <command>\n");
	return;
}
	
