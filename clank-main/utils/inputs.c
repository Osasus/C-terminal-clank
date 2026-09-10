#include <termios.h>
#include <string.h>
#include <unistd.h>  
#include <stdio.h>    
#include <stdint.h>
#include <stddef.h>

void set_raw_mode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void set_cooked_mode() {
    struct termios reset;
    tcgetattr(STDIN_FILENO, &reset);
    reset.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &reset);
}

int utf8_char_length(unsigned char c) {
    if ((c & 0x80) == 0) return 1; 
    else if ((c & 0xE0) == 0xC0) return 2; 
    else if ((c & 0xF0) == 0xE0) return 3; 
    else if ((c & 0xF8) == 0xF0) return 4; 
    return 1;
}


int count_utf8_characters(const char *str) {
    int count = 0;
    
    while (*str) {
        int length = utf8_char_length((unsigned char)*str);
        
        if (length == 0) {
            break;
        }
        str += length;
        count++;
    }
    return count;
}


size_t utf8_prev_char(const char *buffer, size_t index) {
    if (index == 0) return 0;
    index--;

    while (index > 0 && ((buffer[index] & 0xC0) == 0x80)) {
        index--;
    }
    return index;
}


size_t utf8_next_char(const char *buffer, size_t len, size_t index) {
    if (index >= len) return len;
    index++;
    
    while (index < len && ((buffer[index] & 0xC0) == 0x80)) {
        index++;
    }
    return index;
}
