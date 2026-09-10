#include <stdio.h>
#include <string.h>
#include <utils/inputs.h>
#include <stdbool.h>

void print_file(char* buffer) {
    int line_number = 0;  
    char* line_start = buffer;  

    while (*line_start) {
        char* line_end = strchr(line_start, '\n');  

        if (line_end) {
            *line_end = '\0';  
        }

        printf("%d: %s\n", line_number, line_start); 

        line_number++; 
        line_start = line_end ? line_end + 1 : line_end; 
        if (line_end == NULL) {
            break;
        }
    }
}

void clonk_edit(char* buffer, int currentLine, bool itterative, char *Line) {
    char newLine[1024] = { 0 };
    // Prompt the user for the new line input
    if (!itterative) {
        printf("Enter new content for line %d: ", currentLine);
        fgets(newLine, sizeof(newLine), stdin);
        newLine[strcspn(newLine, "\n")] = 0;
    } else {
        strcpy(newLine, Line);
        printf("%d%s", currentLine, newLine);
    }

    // Split the buffer into lines
    char* line_start = buffer;
    int line_number = 0;
    char* line_end;

    // Find the line to be replaced
    while (1) {
        if (line_number == currentLine) {
            char saved[1024] = { 0 };
            bool more_lines = false;
            if(strchr(line_start, '\n')) {
                line_end = strchr(line_start, '\n');
                strcpy(saved, line_end);
                more_lines = true;
            }
            // Replace the current line with the new input
            strncpy(line_start, newLine, 1024);
            if(more_lines) {
                strcpy(line_start + strlen(line_start), saved);
            }
            break;
        }

        // Find the end of the line
        line_end = strchr(line_start, '\n');

        if (line_end) {
            line_start = line_end + 1; // Move to the next line
            line_number++;
        } else {
            if (!line_end) {
                char add_line[] = "\n";
                clonk_edit(add_line, currentLine-line_number, true, newLine);
                strcpy(buffer + strlen(buffer), add_line);
                return;
            }
        }
    }
}


void clonk_main(char* file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }
    
    char buffer[1024] = { 0 };
    fread(buffer, sizeof(buffer) - 1, 1, f);
    fclose(f);

    print_file(buffer);

    int currentLine = 0;
    printf("Enter the line number to edit: ");
    scanf("%d", &currentLine);
    // Consume the newline character left by scanf
    getchar();
    f = fopen(file, "r");
    fread(buffer, sizeof(buffer) - 1, 1, f);
    fclose(f);
    strcpy(buffer + strlen(buffer), "\n");
    clonk_edit(buffer, currentLine, false, NULL);

    f = fopen(file, "w");
    if (f == NULL) {
        perror("Unable to open file for writing");
        return;
    }
    fwrite(buffer, strlen(buffer), 1, f);
    fclose(f);
}

int clank_clonk(int argC, char** argV) {
    if ((argC <= 1) | (argC > 2)) {
        if (argC > 2) {
            printf("Slow down! You can only edit one file at a time.\n");
        } else {
            printf("You can't edit a file with no name.\n");
        }
        return 1;
    }
    char* file = argV[1];
    set_cooked_mode();
    clonk_main(file);
    set_raw_mode();
    return 0;
}
void man_clonk() {
    printf("Simple text editor for clank.\n");
    printf("Usage: <filename>\n");
    return;
}