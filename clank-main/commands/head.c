#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

//Olmedal

int clank_head(int argc, char* argv[]) {
    if (argc < 2){
        printf("File path is a required argument\n");
        return 1;
    }
    if (argc > 3){
        printf("head only takes two arguments\n");
        return 1;  
    }


    int line_count = 10;

    if (argc == 3) {
        line_count = atoi(argv[2]); 
        if (line_count <= 0) {
            printf("Invalid line count. It must be a positive number.\n");
            return 2;
        }
    }


    const char *name = argv[1];

    FILE *file = fopen(name, "r");
    char *line = NULL;
    size_t len = 0;
    int lines_read = 0;

    //Might explode depending on the file
    if (file != NULL) {
        while (lines_read < line_count && getline(&line, &len, file) != -1) {
            printf("%s", line);
            lines_read++;
        }
        
        free(line);
        fclose(file);
    } 
    else {
        printf("Unable to open the file, error code: %d\n", errno);
        printf("%s\n",strerror(errno));
        return 2;
    }
    return 0;
}

void man_head(){
	printf("Prints the first lines of a file \n");
	printf("usage: head <name> [number of lines]\n");
	return;
}