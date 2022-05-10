#pragma once
#include <stdbool.h>

typedef struct {
	int lucky;
	bool flag;
}pla;
typedef struct {
	int lucky;
	bool flag;
}plA;
typedef struct {
	int lucky;
	bool flag;
}plD;
typedef struct {
	int lucky;
	bool flag;
}plS;

typedef struct {
	bool flag;
	int lucky_flag;
	pla a;
	plA A;
	plD D;
	plS S;
}DEF_ALPH_OPT;

typedef struct {
	bool flag;
	int lucky[72], lucky_flag;
	char alphabet[73];
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
void get_alph_rand_string();
void get_alph_rand_string_withChance();
void check_probability();
void init_options();
void algnment_prob(int prob, int zero_prob);