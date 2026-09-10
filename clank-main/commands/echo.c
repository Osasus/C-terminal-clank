#include <stdio.h>

int clank_echo(int argC, char* argsV[]) {
    //No arguments given
    if (argC == 1) { 
        printf("Incorrect usage!");
        return 1;
    }

    //Itterate and print arguments
    for(int i = 1; i < argC; i++) {
        printf("%s", argsV[i]);
        if (i+1 < argC) {
            printf(" ");
        } else {
            printf("\n");
            return 0;
        }
    }
    printf("How... Just how did you manage to get here. I'm dumbfounded\n");
    return 2;
}

void man_echo(){
	printf("Writes text in terminal.\n");
    printf("Usage: <text>\n");
	return;
}