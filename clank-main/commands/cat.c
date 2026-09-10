#include <stdlib.h>
#include <stdio.h>

int clank_cat (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Incorrect usage! Correct usage: cat [filename]\n");
		printf("Try: man cat\n");
		printf("No clanking!\n");
		return 1;
	}	
	
	char *filename = argv[1];	
	char currentChar;

	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Could not open file %s!\n", filename);
		return 2;
	}
	
	//Get file size
	fseek(file, 0, SEEK_END);		//Goto end of file
	long int fileSize = ftell(file);	//Get position
	fseek(file, 0, SEEK_SET); 		//Goto beginning of file
	
	float fileSizeInChars = fileSize/sizeof(char);
	int errorCheck;
	
	if ((fileSizeInChars > 0) && (fileSizeInChars < 1)) {
		printf("File is to small to make up even a single character!\n");
		return 2;
	}

	for (long int i=1; i<fileSizeInChars; i++) {       
		currentChar = fgetc(file);
		fseek(file, -1L, SEEK_CUR);	//Go back one, since we advance twice otherwise
		errorCheck = fgetc(file);
		if (errorCheck == EOF) {
			printf("Error was incountered while reading file!\n");
			return 2;
		}	
		printf("%c", currentChar);
	}
	printf("\n");
	fclose(file);
	return 0;
}

void man_cat(){
	printf("\n");
	return;
}
