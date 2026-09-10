#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* expandFullPath(char* path){

	/*
	 * HOW TO USE!
	 * #include "build/utils.h"
	 * char* temp = expandFullPath((char*)argv[num]) 
	 * där num är t.ex. 1 eller två för funktioner som cd mv etc
	 * där 1 är första pathen och 2 är den andra
	 *
	 * GLÖM INTE! använd free på din variabel innan funktionen returnerar för att inte slösa minne. Se nedan:
	 * free(temp);
	 * return x;
	 */

	if(path[0] != '~'){
		return strdup(path);
	}

	const char* home = getenv("HOME");

	if(!home){
		return NULL;
	}

	if(path[1] == '\0'){
		return strdup(home);
	}

	size_t sizeH = strlen(getenv("HOME"));
	path++;
	size_t sizeC = strlen(path);

	char* expandedPath = malloc(sizeH + sizeC + 1);

	if(!expandedPath){
		return NULL;
	}

	strcpy(expandedPath, home);
	strcat(expandedPath, path);

	return expandedPath;
}
