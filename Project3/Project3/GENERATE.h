#pragma once


typedef struct {
	int flag, lucky[4],
		plenty_a, plenty_A, plenty_D, plenty_S;
}DEF_ALPH_OPT;

typedef struct {
	DEF_ALPH_OPT def_alph;
	int minLen, maxLen, Len;
	char* alph;
}option;

option op;

int GEN(int argc, char** argv);

int get_option(int argc, char** argv);