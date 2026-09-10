#include <string.h>
#include <stdio.h>

/*
 *
 * HOW TO USE!!
 *
 * char myFlags[mySize];
 * int flagCount = getFlags(&argc, argv, myFlags, mySize);
 *
 * if(containsFlag(myFlags, 'x') == 0) {
 * 	doStuff();
 * }
 *
 */

int getFlags(int* argc, char* argv[], char flags[], int flagSize) {
    int count = 0;
    int newArgc = 1;

    for (int i = 1; i < *argc; i++) {

        if (argv[i][0] == '-') {

            if (argv[i][1] != '\0') {

                for (int j = 1; argv[i][j] != '\0'; j++) {
			if(count < flagSize){
                    		flags[count++] = argv[i][j];
			}
		}

            }

        } 
	else {
		argv[newArgc++] = argv[i];
        }
    }

    flags[count] = '\0';

    *argc = newArgc;

    return count;
}

int containsFlag(char flags[], char c){
	int i = 0;
	while(flags[i] != '\0'){
		if(flags[i] == c){
			return 0;
		}
		i++;
	}
	return -1;
}
