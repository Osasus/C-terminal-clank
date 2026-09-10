#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <commands.h>
#include <utils/inputs.h>
#include <utils/colors.h>

volatile sig_atomic_t timed_out = 0;

void timeout_handler(__attribute__((unused)) int sig) {
	timed_out = 1;
}

int clank_captcha(int argc, __attribute__((unused)) char* argv[]) {
	if (argc > 1) {
		perror("Incorrect usage! clear takes no arguments.\n");
		return 1;
	}
		
	const char *numbers[] = {
		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────\n"
		"─████████───\n"
		"─██░░░░██───\n"
		"─████░░██───\n"
		"───██░░██───\n"
		"───██░░██───\n"
		"───██░░██───\n"
		"───██░░██───\n"
		"───██░░██───\n"
		"─████░░████─\n"
		"─██░░░░░░██─\n"
		"─██████████─\n"
		"────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─██████████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████████─\n"
		"─██░░██─────────\n"
		"─██░░██████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─██████████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─██████████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────────\n"
		"─██████──██████─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██████─\n"
		"────────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████████─\n"
		"─██░░██─────────\n"
		"─██░░██████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─██████████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████████─\n"
		"─██░░██─────────\n"
		"─██░░██████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██░░██─\n"
		"─────────██████─\n"
		"────────────────",
				
		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",

		"────────────────\n"
		"─██████████████─\n"
		"─██░░░░░░░░░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░██──██░░██─\n"
		"─██░░██████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████░░██─\n"
		"─────────██░░██─\n"
		"─██████████░░██─\n"
		"─██░░░░░░░░░░██─\n"
		"─██████████████─\n"
		"────────────────",
	};
	
	clank_clear(1, NULL);
	
	int num_numbers = sizeof(numbers) / sizeof(numbers[0]);
	int indices[4];
	srand(time(0));
	
	printf("%s", YELLOW_COLOR);
	
	for (int i = 0; i < 4; i++) {
		indices[i] = rand() % num_numbers;
	}

	for (int line = 0; line < 13; line++) {
		for (int i = 0; i < 4; i++) {
			const char *number = numbers[indices[i]];
			const char *line_start = number;
			
			for (int l = 0; l < line; l++) {
				line_start = strchr(line_start, '\n');
				
				if (!line_start) {
					break;
				}
				
				line_start++;
			}
			
			const char *line_end = strchr(line_start, '\n');
			
			if (!line_end) {
				line_end = line_start + strlen(line_start);
			}
			
			printf("%.*s", (int)(line_end - line_start), line_start);
		}
		
		printf("\n");
	}

	set_cooked_mode();
	printf("\n%s%sEnter the large numbers above to prove you're not a clanker%s %s>%s ", RESET_TEXT, BOLD_TEXT, RESET_TEXT, BLUE_COLOR, RESET_TEXT);
	fflush(stdout);

	fd_set readfds;
	struct timeval timeout;
	char buffer[256];

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

	if (ready == -1) {
		perror("select");
		set_raw_mode();
		return 2;
	} else if (ready) {
		if (fgets(buffer, sizeof(buffer), stdin)) {
			buffer[strcspn(buffer, "\n")] = '\0';
			int correct = 1;
			
			for (int i = 0; i < 4; i++) {
				if (buffer[i] - '0' != indices[i]) {
					correct = 0;
					break;
				}
			}
			
			if (correct) {
				printf("%sCorrect! You're not a clanker.%s\n\n", GREEN_COLOR, RESET_TEXT);
				set_raw_mode();
				return 0;
			} else {
				printf("%sWrong! Get out of here clanker.%s\n", RED_COLOR, RESET_TEXT);
				set_cooked_mode();
				return 3;
			}
		}
	} else {
		printf("\n%sYou ran out of time! Get out of here clanker.%s\n", RED_COLOR, RESET_TEXT);
		set_cooked_mode();
		return 3;
	}

	set_cooked_mode();
	return 0;
}

void man_captcha(){
	printf("Shows a captcha for the user to prove they're not a human.\n\n");
	printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
	printf("captcha - shows a captcha\n");
	return;
}
