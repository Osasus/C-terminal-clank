#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "utils/inputs.h"

int clank_run(int argc, char* argv[]){
	if(argc == 4 && strcmp(argv[1], "car") == 0 && strcmp(argv[2], "snow") == 0 && strcmp(argv[3], "pen") == 0){
		printf(";)\n");
		return 0;
	}

	if(argc == 1){
		return 1;
	}

	char** args = malloc(argc * sizeof(char*));

	if(args == NULL){
		printf("Failed to allocate mimmorri");
		return 2;
	}

	for(int i = 1; i < argc; ++i){
		args[i - 1] = argv[i];
	}

	args[argc - 1] = NULL;

	//signal(SIGINT, SIG_IGN);

	pid_t pid = fork();
	set_cooked_mode();
	//NÄR FORKAD FIXA set_cooked_mode osv och annars byt tillbaka till raw

	if(pid == 0){

		//signal(SIGINT, SIG_DFL);

		execvp(args[0], args);
		perror("Failed to find path or binary");
		exit(1);
	}
	else if(pid < 0){
		perror("Failed to fork");
		//signal(SIGINT, SIG_DFL);
		free(args);
		set_raw_mode();
		return 2;
	}
	else{
		int status;
		waitpid(pid, &status, 0);
	}
	
	//signal(SIGINT, SIG_DFL); //signal interrupt == signal default
	free(args);
	set_raw_mode();
	return 0;
}

void man_run(){
	printf("Runs a binary. Example usage:\nrun make\nrun git commit -m 'a very cool message'\n");
	return;
}
