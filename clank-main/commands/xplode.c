#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

#include "commands.h"
#include "utils.h"

static int xplode_path(const char *path, int useS) {
	DIR *dir = opendir(path);
	if (!dir) {
		return 2;
	}

    	struct dirent *dp;

    	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
			continue;
		}

        	char full_path[PATH_MAX];
	
        	snprintf(full_path, sizeof(full_path), "%s/%s", path, dp->d_name);

        	struct stat st;
        	if (lstat(full_path, &st) == -1) {
        	    perror("stat");
        	    continue;
        	}
	
	        if (S_ISDIR(st.st_mode)) {
	            xplode_path(full_path, useS);
	            if (rmdir(full_path) != 0) {
	                perror("rmdir");
		    }
		} 
		else {

            		if (remove(full_path) != 0) {
                		perror("remove");
			}	
		}

		if(useS != 0)
			printf("%s%s<Removing> %s%s\n", RED_COLOR, BOLD_TEXT, full_path, RESET_TEXT);
	
	}

	closedir(dir);
	return 0;
}

int clank_xplode(int argc, char *argv[]) {
	char flags[8];
	getFlags(&argc, argv, flags, 8);
	
	int success = containsFlag(flags, 'f');
	if(success != 0){
		success = clank_captcha(argc, argv);
	}

	if (argc == 1 && success == 0) {
		char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            return 2;
        }

        if (strcmp(cwd, "/") == 0 && success != 0) {
            printf("Can't explode root\n");
            return 2;
        }
	int useS = containsFlag(flags, 's');
	if(useS != 0)
		printf("\n%s%s<Exploding> %s%s\n\n", RED_COLOR, BOLD_TEXT, cwd, RESET_TEXT);

        xplode_path(cwd, useS);

	if(chdir("..") != 0){
		perror("chdir");
		return 2;
	}

        if (rmdir(cwd) != 0) {
		perror("rmdir");
		return 2;
        }

        return 0;
    }

    return 1;
}


void man_xplode(){
	printf("Explodes the current directory\nExample usage:\ncd <where/to/xplode>\nxplode\n");
	return;
}
