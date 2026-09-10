#include <stdio.h>
#include "commands.h"

int clank_mv(int argc, char* argv[]){
	if(argc != 3){
		return 1;
	}

	if(clank_cp(3, argv) != 0){
		return 2;
	}

	if(clank_rm(2, argv)){
		return 2;
	}

	return 0;
}

void man_mv(){
	printf("\n");
	return;
}
