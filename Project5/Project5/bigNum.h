#pragma once

#include <stdbool.h>

typedef struct {
	unsigned* val;
	int length;
	bool sign;
	int *zero;
}bigInt;

bigInt a, b, result;


int bigNum(int argc, char** argv);
void getNumbers(int argc, char** argv);
void printBigNum(bigInt *num);
void initNumbers(char** argv);

void divide();
void multiply();
void add(bool sign);
void subtract(bool sign);
void remains();

void operation_definition(char op);
void swapBigNum();
void word_alignment(bigInt* num);
void realloc_result();
void mult_block(unsigned X, unsigned Y);