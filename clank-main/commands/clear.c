#include <unistd.h>
#include <stdio.h>
#include <utils/colors.h>

int clank_clear(int argc, __attribute__((unused)) char* argv[]) {
	if (argc > 1) {
        	perror("Incorrect usage! clear takes no arguments.\n");
		return 1;
    	}
    	
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);
	return 0;
}

void man_clear(){
	printf("Clears the terminal window.\n\n");
	printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("clear - clears the terminal window\n");
	return;
}
