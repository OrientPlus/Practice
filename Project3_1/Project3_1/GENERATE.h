#pragma once

typedef struct {
	int minLen, maxLen, Len;
	char* alph, def_alph[5];
}option;

option op;

void GENERATE(int argc, char** argv);

int get_option(int argc, char** argv);