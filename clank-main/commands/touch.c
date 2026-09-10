#include <stdio.h>
#include <unistd.h>

int clank_touch(int argC, char* argV[]) {
    FILE *filePointer;
    if ((argC <= 1) | (argC > 2)) {
        if (argC > 2) {
            printf("Slow down! You can only create one file at a time\n");
        } else {
            printf("You can't create a file without a name\n");
        }
        return 1;
    } 
    if(access(argV[1], F_OK) == 0) {
        printf("File already exists\n");
        return 2;
    } else {
        filePointer = fopen(argV[1], "w");
        fclose(filePointer);
        return 0;
    }
    return 2;
}

void man_touch(){
	printf("Creates a file with the specified name\n");
	printf("usage: <name> \n");
	return;
}