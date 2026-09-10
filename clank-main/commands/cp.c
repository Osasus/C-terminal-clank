#include<stdio.h>    
#include<stdlib.h>
#include "build/utils.h"

int clank_cp(int argc, char* argv[]) {
	if (argc != 3) {
		perror("Incorrect usage! cp takes exactly two arguments.\n");
		return 1;
	}

	
	char* sourcepath = expandFullPath((char*)argv[1]);
	char* destinationpath = expandFullPath((char*)argv[2]);
	
	if (sourcepath == NULL || destinationpath == NULL) {
		perror("Invalid source or destination path.");
	} 
	
	FILE *source = fopen(sourcepath, "r");
	
	if (source == NULL) {
		perror("Invalid source path.");
		return 1;
	}
	
	FILE *destination = fopen(destinationpath, "w");
	
        if (destination == NULL) {
		perror("Invalid destination path.");
		fclose(source);
		return 1;
        }

	char character;
	
	while((character = fgetc(source)) != EOF) {
		fputc(character, destination);
	}
        
        printf("File copied successfully.\n");        
        fclose(source);        
        fclose(destination);
        free(sourcepath);
        free(destinationpath);
	return 0;
}

void man_cp(){
	printf("Copies a file to a new destination.\n\n");
	printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("cp %s<source path> <destination path>%s - copies the source file to the path destination\n", BLUE_COLOR, RESET_TEXT);
	return;
}
