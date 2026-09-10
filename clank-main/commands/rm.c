#include <stdio.h>
#include <errno.h>
#include <string.h>


//Olmedal

int clank_rm(int argc, char* argv[]) {
    if (argc < 2){
        printf("File path is a required argument\n");
        return 1;
    }
    if (argc > 2){
        printf("rm only takes 1 argument\n");
        return 1;
    }

    const char *file = argv[1];

    if (remove(file) == 0) {
        printf("File removed\n");
    } 
    else {
        printf("Unable to remove the file, error code: %d\n", errno);
        printf("%s\n",strerror(errno));
        return 2;
    }

    return 0;
}

void man_rm(){
	printf("Removes a file\n");
	printf("usage: rm <name> \n");
	return;
}