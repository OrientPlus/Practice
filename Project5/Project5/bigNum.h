#pragma once

#include <stdbool.h>

typedef struct {
	unsigned* val;
	int length;
	bool sign;
	int *zero;
}bigInt;

bigInt a, b, result;


int bigNum();
void getNumbers(int argc, char** argv, bool flag);
void printBigNum_dec(bigInt *num);
void printBigNum_hex(bigInt* num);
void initNumbers(char** argv);
void check_numbers(int argc, char** argv);

void divide(bool sign);
void multiply(bool sign);
void add(bool sign);
void subtract(bool sign);

void operation_definition(char op);
void swapBigNum();
void word_alignment(bigInt* num);
void realloc_result();
void alignment_mult_val(unsigned** mass, int n, int len, int oldLen);
int get_nineCount(unsigned X, int j);

bool get_numbers_from_console(char** numbers);