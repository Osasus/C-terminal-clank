#include <stdio.h>
#include "build/commands.h"
#include <utils/colors.h>

// Olmedal

int clank_help(__attribute__((unused)) int argc, __attribute__((unused)) char* argv[]) {
	printf("%sCLANK%s v.0.5\n", BLUE_COLOR, RESET_TEXT);
	printf("%sCreated by:%s Helge Erik\n\n", BOLD_TEXT, RESET_TEXT);
	printf("%sAvailable Commands:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("%s╭%s\n", BLUE_COLOR, RESET_TEXT);
    
	int i;
	for (i = 0; commands[i].name != NULL; i++) {
		printf("%s│%s ∙ %s\n", BLUE_COLOR, RESET_TEXT, commands[i].name);
	}
	printf("%s╰%s\n", BLUE_COLOR, RESET_TEXT);
	printf("%s%d%s available commands\n", BOLD_TEXT, i, RESET_TEXT);
	return 0;
}

void man_help(){
	printf("Prints all the available commands\n");
	printf("usage: help\n");
	return;
}
