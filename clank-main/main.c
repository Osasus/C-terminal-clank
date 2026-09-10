#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "build/commands.h"
#include "utils.h"
#include <locale.h>

int execute_command(const char *cmd_name, int argc, char* argv[]) {
	PRINT_DEBUG("Command Name:   %s", cmd_name);
	PRINT_DEBUG("Argument Count: %d", argc);
	PRINT_DEBUG("Arguments:");
	for (int i = 0; i < argc; i++) {
		PRINT_DEBUG("  argv[%d]:      %s\n", i, argv[i]);
	}

	for (int i = 0; commands[i].name != NULL; i++) {
		if (strcmp(commands[i].name, cmd_name) == 0) {
			if (
				strcmp(cmd_name, "cd") == 0 ||
			 	strcmp(cmd_name, "exit") == 0 ||
				strcmp(cmd_name, "xplode") == 0 ||
				strcmp(cmd_name, "cog") == 0
			) {
				PRINT_DEBUG("Command '%s' is a builtin, executing in PARENT (PID: %d)...", cmd_name, getpid());
				return commands[i].execute(argc, argv);
			}
			
			PRINT_DEBUG("Command '%s' is external. preparing to fork...", cmd_name);

			pid_t pid = fork();

			if (pid == -1) {
				perror("fork failed");
				return 2;
			} else if (pid == 0) {
				PRINT_DEBUG("(Child Process %d) Started. Executing '%s'...", getpid(), cmd_name);

				int result = commands[i].execute(argc, argv);
				PRINT_DEBUG("(Child Process %d) Execution finished. Exiting with code %d.", getpid(), result);
				exit(result);
			} else {
				int status;
				
				PRINT_DEBUG("(Parent Process) Child spawned with PID %d. Waiting...", pid);

				waitpid(pid, &status, 0);

				if (WIFEXITED(status)) {
					int exit_code = WEXITSTATUS(status);
					PRINT_DEBUG("(Parent Process) Child %d exited normally with code %d.", pid, exit_code);
					if (exit_code) print_error(exit_code);
					return exit_code;
				} else if (WIFSIGNALED(status)) {
					print_error(status);
					return 2;
				}

				return 0;
			}
		}
	}
	printf("%sUnknown or invalid command. Type 'help' for a list of available commands.%s\n", RED_COLOR, RESET_TEXT);
	return 0;
}



int main(void) {
	char cwd[PATH_MAX];
	char buffer[PATH_MAX];
	struct passwd *pw = getpwuid(getuid());
	const char *home_dir = pw->pw_dir;

	int index = 0;

	//testar anti ctr+c
	signal(SIGINT, SIG_IGN);

	printf("%sWelcome to CLANK v0.5.2%s\n", BLUE_COLOR, RESET_TEXT);

	// Kolla om det finns uppdateringar
	FILE *fp;
	char output[1024];

	fp = popen("git rev-list --count HEAD..@{u} 2>/dev/null", "r");

	if (fp != NULL && fgets(output, sizeof(output), fp) != NULL) {
		int commits_ahead = atoi(output);
		
		if (commits_ahead > 0) {
			printf("There's a new version available! Run %s%scog update%s to update.\n", BOLD_TEXT, BLUE_COLOR, RESET_TEXT);
		}
	}

	pclose(fp);

	PRINT_DEBUG("Debug is on.");
	printf("   %s__,_,%s\n", GREEN_COLOR, RESET_TEXT);
	printf("  %s[_|_/ %s\n", BLUE_COLOR, RESET_TEXT);
	printf("   %s//%s\n", GREEN_COLOR, RESET_TEXT);
	printf(" %s_//    __%s\n", BLUE_COLOR, RESET_TEXT);
	printf("%s(_|)   |@@|%s\n", GREEN_COLOR, RESET_TEXT);
	printf(" %s\\ \\__ \\--/ __%s\n", BLUE_COLOR, RESET_TEXT);
	printf("  %s\\o__|----|  |   __%s\n", GREEN_COLOR, RESET_TEXT);
	printf("      %s\\ }{ /\\ )_ / _\\%s\n", BLUE_COLOR, RESET_TEXT);
	printf("      %s/\\__/\\ \\__O (__%s\n", GREEN_COLOR, RESET_TEXT);
	printf("     %s(--/\\--)    \\__/ %s\n", BLUE_COLOR, RESET_TEXT);
	printf("     %s_)(  )(_%s\n", GREEN_COLOR, RESET_TEXT);
	printf("    %s`---''---`%s\n", BLUE_COLOR, RESET_TEXT);

	set_raw_mode();
	load_history();

	while (1) {
		if (getcwd(cwd, sizeof(cwd)) == NULL) {
			perror("getcwd() error");
			*cwd = ' ';
		}
		
		if (strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
			char output[1024];
			sprintf(output, "~%s", cwd + strlen(home_dir));
			printf("%s╭─%s %sCLANK%s %s─ (%s%s%s) ─\n", BLUE_COLOR, RESET_TEXT, BOLD_TEXT, RESET_TEXT, BLUE_COLOR, RESET_TEXT, output, BLUE_COLOR);
		} else {
			printf("%s╭─%s %sCLANK%s %s─ (%s%s%s) ─\n", BLUE_COLOR, RESET_TEXT, BOLD_TEXT, RESET_TEXT, BLUE_COLOR, RESET_TEXT, cwd, BLUE_COLOR);
		}
		
		printf("╰──» %s", RESET_TEXT);

		//if (!fgets(input, sizeof(input), stdin)) break;

		//Whacky input handling:
		memset(buffer, 0, sizeof(buffer));
		index = 0;
		
		while (1) {
			int input = getchar();
			
			switch (input) {
				case EOF:
				case '\n':
					goto end_check;

				case 8:
				case 127:
					if (index > 0) {
						size_t buf_len = strlen(buffer);
						index = utf8_prev_char(buffer, index);

						memmove(buffer + index, buffer + index + 1, buf_len - index);

						printf("\b");
						printf("%s ", buffer + index);

						size_t len_after = strlen(buffer + index);
						
						for (size_t i = 0; i <= len_after; i++) {
							printf("\b");
						}
					}
					break;


				case '\033': {
					int next = getchar(); // Expect '['
					if (next != '[') break;

					int code = getchar();
					if (code == 'A' || code == 'B') {
						while (index > 0) {
							printf("\b");
							index = utf8_prev_char(buffer, index);
						}

						printf("\033[J");

						if (code == 'A') {
							strcpy(buffer, upp_history());
						} else {
							strcpy(buffer, down_history());
						}

						printf("%s", buffer);
						index = strlen(buffer);
					} else if (code == 'C' && index < (int)strlen(buffer)) {
						printf("\033[1C");
						index = utf8_next_char(buffer, strlen(buffer), index);
					}
					else if (code == 'D' && index > 0) {
						printf("\033[1D");
						index = utf8_prev_char(buffer, index);
					}
					
					break;
				}

				default: {
					size_t buf_len = strlen(buffer);
					
					if (buf_len < sizeof(buffer) - 1) {
						memmove(buffer + index + 1, buffer + index, buf_len - index + 1);
						buffer[index] = (char)input;
				 
						printf("%c%s", input, buffer + index + 1);

						for (size_t i = index + 1; i < buf_len + 1; i++) {
							printf("\b");
						}
						
						index++;
					}
					break;
				}
			}
		}
		end_check:
		printf("\n");

		buffer[strcspn(buffer, "\r\n")] = 0;

		if (strlen(buffer) == 0) continue;
		add_to_history(buffer);

		char* args[100];
		int argc = clank_tokenize(buffer, args, 100); //tokenize all

		args[argc] = NULL; // Null terminator	

		// Environment variables
		if (args[0] != NULL && args[0][0] == '$') {

			if (args[0][1] == '\0') {
				continue;
			}

			if (args[1] != NULL && strcmp(args[1], "=") == 0) {

				if (args[2] != NULL) {
					if (setenv(args[0] + 1, args[2], 1) < 0) {
						perror("setenv");
					} else {
						printf("%s\n", args[2]);
						PRINT_DEBUG("setenv: name='%s', value='%s' (SUCCESS)", args[0] + 1, args[2]);
					}
					continue;
				}
				continue;
			}

			char *val = getenv(args[0] + 1);
			if (val) { 
				printf("%s\n", val);
				PRINT_DEBUG("getenv: name='%s', value='%s'", args[0] + 1, val);
			} else {
				printf("\n");
				PRINT_DEBUG("getenv: name='%s' not found (NULL)", args[0] + 1);
			}
			continue;
		}

		if (args[0] != NULL && strcmp(args[0], "unset") == 0) {
			if (args[1] != NULL && args[1][0] == '$') {
				if (args[1][1] == '\0') {
					continue;
				}
				if (unsetenv(args[1] + 1) < 0) {
					perror("unsetenv");
				}
				PRINT_DEBUG("unsetenv: Removed variable '%s'", args[1] + 1);
			}
			continue;
		}
		
		if (argc > 0) {
			int result = execute_command(args[0], argc, args);
			
			if (result == 0) {
				if (strcmp(args[0], "history") == 0) {
					reload_history();
				}
			} else if (result == 3) {
				break;
			}
		}
	}
	return 0;
}
