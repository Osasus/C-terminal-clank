#include <stdio.h>
#include <ctype.h>

int clank_tokenize(char* buffer, char* args[], char maxArgs){
	int argc = 0;
	char* p = buffer;

	while(*p && argc < maxArgs){
		while(isspace(*p)){
			p++;
		}

		if(*p == '\0'){
			break;
		}

		if(*p == '"' || *p == '\''){
			char quote = *p++;
			args[argc++] = p;

			while(*p && *p != quote){
				p++;
			}

			if(*p){
				*p++ = '\0';
			}
		}
		else{
			args[argc++] = p;

			while(*p && !isspace(*p)){
				p++;
			}

			if(*p){
				*p++ = '\0';
			}
		}
	}

	return argc;
}
