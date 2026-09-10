#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define HISTORY_FILE "/tmp/.clankstory"
#define HISTORY_SIZE 100 

static char *history[HISTORY_SIZE];
static int history_index = -1;  
static int current_view_index = -1;


void add_to_history(const char *command) {
    if (command == NULL) return;

    FILE *file = fopen(HISTORY_FILE, "a");
    if (file == NULL) {
        perror("Failed to open history file");
        return;
    }
    fprintf(file, "%s\n", command);
    fclose(file);

    char *new_command = strdup(command);
    if (new_command == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    if (history_index < HISTORY_SIZE - 1) {
        history_index++;
    } else {
        free(history[0]);
        for (int i = 1; i < HISTORY_SIZE; i++) history[i - 1] = history[i];
    }
    history[history_index] = new_command;
    current_view_index = history_index;
}

const char* upp_history() {
    if (current_view_index > 0) {
        return history[current_view_index--];
    }
    if (history_index){
        return history[current_view_index];
    } 
    else {
        return "";
    }
}


const char* down_history() {
    if (current_view_index < history_index) {
        return history[++current_view_index];
    }    
    return "";
}


const char* load_history(void) {
    current_view_index = -1;
    FILE *file = fopen(HISTORY_FILE, "ab+");
    if (file == NULL) {
        return "";
    }

    char line[PATH_MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char *new_command = strdup(line);
        if (!new_command) {
            perror("Failed to allocate memory");
            fclose(file);
            return "";
        }
        if (history_index < HISTORY_SIZE - 1) {
            history[++history_index] = new_command;
        } else {
            free(history[0]);
            for (int i = 1; i < HISTORY_SIZE; i++) history[i - 1] = history[i];
            history[HISTORY_SIZE - 1] = new_command;
        }
    }
    fclose(file);
    current_view_index = history_index;
    return (current_view_index >= 0) ? history[current_view_index] : "";
}

void reload_history(void) {
    for (int i = 0; i <= history_index; i++) {
        free(history[i]);
        history[i] = NULL;
    }
    history_index = -1;
    current_view_index = -1;
    load_history();
    add_to_history("");
}
