#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include "build/utils.h"

int clank_mkdir(int argc, char* argv[]){
	if(argc < 2 || argc > 3){
		return 1;
	}

	char* temp = expandFullPath((char*)argv[1]);
	char* token = strtok(temp, "/");

	char currentPath[1024] = ""; //riktig hackfix, gör bättre sen
	
	while(token){
		if(strlen(currentPath) > 0)
			strcat(currentPath, "/");
		strcat(currentPath, token);

	if(argc == 2){
		if(mkdir(currentPath, 0700) == -1){
			//free(temp);
			//return 2;
		}
	}
	else{
		if(mkdir(currentPath, atoi(argv[2])) == -1){
			//free(temp);
			//return 2;
			printf("Use a number you clankuh\n");
		}
	}

	token = strtok(NULL, "/");
	}

	free(temp);
	return 0;
}

void man_mkdir(){
	printf("Makes a new directory.\nIf there are multiple directories needed to be created it will do that recursively\n");
	return;
}
