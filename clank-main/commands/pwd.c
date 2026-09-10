#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>


//Olmedal

int clank_pwd(int argc, __attribute__((unused))char* argv[]) {
    if (argc > 1) {
        printf("pwd takes no arguments\n");
        return 1; 
    }

    char cwd[PATH_MAX]; 

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } 
    else {
        printf("getcwd() error %d\n", errno); 
        printf("%s\n",strerror(errno));
        return 2;
    }
    return 0;
}

void man_pwd(){
	printf("prints the current working directory\n");
	printf("usage: pwd \n");
	return;
}
