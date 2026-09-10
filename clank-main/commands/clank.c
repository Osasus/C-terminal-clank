#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <utils/colors.h>

float CLANK_DELAY = 2;


int clank_clank(__attribute__((unused))int argc, __attribute__((unused))char* argv[]) {

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

	unsigned int number = (unsigned int) pow(1.01, CLANK_DELAY);

	sleep(number);
	CLANK_DELAY = CLANK_DELAY * 2;
	return 0;
}

void man_clank(){
	printf("Prints a clanker.\n");
	return;
}
