#pragma once


typedef struct {
	int flag, lucky[4], lucky_flag,
		plenty_a, plenty_A, plenty_D, plenty_S;
}DEF_ALPH_OPT;

typedef struct {
	int flag, lucky[72];
	char alphabet[72];
}ALPH;

typedef struct {
	DEF_ALPH_OPT def_alph;
	ALPH alph;
	int minLen, maxLen, Len;
}option;

option op;
char* password;

int GEN(int argc, char** argv);
int get_option(int argc, char** argv);
void get_def_rand_string();
void get_def_rand_string_withChance();