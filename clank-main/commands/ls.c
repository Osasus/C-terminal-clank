#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include "build/utils.h"

int clank_ls(int argc, char* argv[]) {
    DIR *dir;

    if (argc > 2) {
        printf("Incorrect usage! ls takes at most a single argument.\n");
        return 1;
    }

    char* path = (argv[1] != NULL) ? expandFullPath((char*)argv[1]) : ".";
    dir = opendir(path);

    if (dir == NULL) {
        perror(path);
        if (argv[1] != NULL) free(path);
        return 2;
    }

    struct dirent *entry;

    printf("%s╭%s\n", BLUE_COLOR, RESET_TEXT);

    while ((entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        char *filecolor = RESET_TEXT;
        const char *filetype = "Other:    ";

        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
            continue;
        }

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, filename);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                filetype = "Directory:";
                filecolor = BLUE_COLOR;
            } else if (S_ISREG(st.st_mode)) {
                filetype = "File:     ";

                if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
                    filecolor = GREEN_COLOR;
                }
            }
        } else {
            filetype = "Unknown:  ";
            filecolor = RED_COLOR;
        }

        printf("%s│%s %s %s%s%s\n",
               BLUE_COLOR, RESET_TEXT,
               filetype, filecolor, filename, RESET_TEXT);
    }

    printf("%s╰%s\n", BLUE_COLOR, RESET_TEXT);

    closedir(dir);
    if (argv[1] != NULL) free(path);
    return 0;
}

void man_ls() {
    printf("Prints the contents of the current directory.\n\n");
    printf("%sUsage:%s\n", BOLD_TEXT, RESET_TEXT);
    printf("ls - lists the contents of the current directory\n");
    printf("ls %s<path>%s - lists the contents of the given directory\n", BLUE_COLOR, RESET_TEXT);
}

