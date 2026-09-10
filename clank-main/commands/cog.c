#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <commands.h>
#include <limits.h>
#include <libgen.h>
#include <utils/colors.h>

void build_and_restart() {
	printf("Cleaning up previous versions...\n");
	
	char *clean_args[] = { "run", "make", "clean", NULL };
	clank_run(3, clean_args);
	
	printf("Building clank...\n");
	
	char *build_args[] = { "run", "make", NULL };
	clank_run(2, build_args);
	
	printf("Restarting clank...\n");
	clank_clear(1, NULL);
	execl("./build/clank", "clank", NULL);
	return;
}

int clank_cog(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Incorrect usage! cog takes exactly two arguments.\n");
        	return 1;
	}
	
	char* argument = argv[1];
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL && strcmp(basename(cwd), "clank") == 0) {
		if (strcmp(argument, "update") == 0) {
			printf("Updating clank...\n");

			char *update_args[] = { "run", "git", "pull", NULL };
			clank_run(3, update_args);
		
			build_and_restart();
			return 0;	
		} else if (strcmp(argument, "restart") == 0) {
			build_and_restart();
			return 0;
		} else if (strcmp(argument, "debug") == 0) {
			printf("Cleaning up previous versions...\n");
	
			char *clean_args[] = { "run", "make", "clean", NULL };
			clank_run(3, clean_args);
			
			printf("Building clank...\n");
			
			char *build_args[] = { "run", "make", "debug", NULL };
			clank_run(3, build_args);
			
			printf("Restarting clank...\n");
			clank_clear(1, NULL);
			execl("./build/clank", "clank", NULL);
			return 0;
		} else {
			printf("Invalid argument.\n");
			return 1;
		}
	} else {
		printf("%sYou must run cog from the clank root directory! You're currently in %s.%s\n", RED_COLOR, basename(cwd), RESET_TEXT);
	}
	
	return 2;
}

void man_cog(){
	printf("Provides various development options for the clank shell.\n\n");
	printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("cog %supdate%s - updates the shell and restarts\n", BLUE_COLOR, RESET_TEXT);
	printf("cog %srestart%s - rebuilds the shell and restarts\n", BLUE_COLOR, RESET_TEXT);
	printf("cog %sdebug%s - rebuilds the shell and restarts in debug mode\n", BLUE_COLOR, RESET_TEXT);
	return;
}
