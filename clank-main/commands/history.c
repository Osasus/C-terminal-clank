#include <stdio.h>
#include <string.h>
#include "commands.h"
#include <unistd.h>
#include "utils.h"

#define HISTORY_FILE "/tmp/.clankstory"

int clank_history(int argc, char* argv[]){
    if (argc != 1 && argc != 2) {
    	printf("Incorrect usage! history takes either one or two arguments.\n");
        return 1;
    }

    char* argument = argv[1];

    if (argument == NULL) {
	    char *args[] = { "cat", HISTORY_FILE, NULL };
	    return clank_cat(2, args);
    } else if (strcmp(argument, "clear") == 0) {
    	    char *args[] = { "rm", HISTORY_FILE, NULL };
	    int result = clank_rm(2, args);
	    return result;
    }
    
    return 2;
}


void man_history(){
	printf("Manages clank command history.\n\n");
	printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("history - shows the command history\n");
	printf("history %sclear%s - clears the command history\n", BLUE_COLOR, RESET_TEXT);
	return;
}
