#pragma once

#include <stdbool.h>

typedef struct {
	char** val;
	int length;
	bool sign;
}bigInt;

typedef struct {
	unsigned* val;
	int length;
	bool sign;
	int* zero;
}supportMASS;

bigInt result;

supportMASS a, b, c;


int bigNum(int argc, char** argv);
void getNumbers(int argc, char** argv);
void printBigNum_dec(supportMASS *num);
void printBigNum_hex(bigInt* num);
void initNumbers(char** argv);
void check_numbers(int argc, char** argv);

void divide(bool sign, supportMASS *n1, supportMASS *n2);
void multiply(bool sign, supportMASS *n1, supportMASS *n2);
void add(bool sign);
void subtract(bool sign, supportMASS* n1, supportMASS* n2);

void operation_definition(char op);
void swapBigNum(supportMASS *n1, supportMASS *n2);
void word_alignment(supportMASS* num);
void realloc_result();
void alignment_mult_val(unsigned** mass, int n, int len);
int get_nineCount(unsigned X, int j);

bool get_numbers_from_console(char** numbers, int argc, char** argv);
unsigned getLengthDenomination(supportMASS* n);
bool compare(supportMASS* n1, unsigned len, supportMASS* n2);
