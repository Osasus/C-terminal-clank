#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "build/utils.h"

//reutrn 0 -> good return, 1 -> bad args, 2 -> othrerrors

int clank_cd(int argc, char* argv[]){
	if(argc < 2){ //if there are 0 arguments return bad args
		printf("where are the args?? GRRRR!\n");
		return 1;
	}

	if(argc == 2){ //if there is one argument, which is expected
		char* temp = expandFullPath((char*)argv[1]);

		int ret;
		ret = chdir(temp); //change dir

		if(ret == -1){ //if given dir doesnt exist or path was wrong
			printf("Could not find that clancuh ass directory: %s\n", temp);
			free(temp);
			return 1;
		}
		free(temp);
	}
	else{ //if there are too many arguments
		printf("Too many arguments! Take a look at the manual. Dont use a clanker..\n");
		return 1;
	}

	return 0;
}

void man_cd(){
	printf("Changes the directory path\nUsage:\ncd path\noptional\n'~' marks the home directory and can be used as such:\ncd ~\ncd ~/mypath/myfileetc\n");
	return;
}
