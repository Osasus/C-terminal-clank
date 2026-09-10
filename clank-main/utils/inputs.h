#ifndef INPUTS_H
#define INPUTS_H

void set_raw_mode();
void set_cooked_mode();
int utf8_char_length(unsigned char c);
int count_utf8_characters(const char *str);
size_t utf8_prev_char(const char *buffer, size_t index);
size_t utf8_next_char(const char *buffer, size_t len, size_t index);

#endif
