#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int clank_neo(int argc, __attribute__((unused))char* argv[]) {
	if (argc > 1) {
        	perror("Incorrect usage! neo takes no arguments.\n");
		return 1;
    	}
	
	system("xdg-open https://neo.mannskar.com/");
	return 0;
}

void man_neo(){
	printf("Opens a beautifully crafted web page.\n");
	return;
}
