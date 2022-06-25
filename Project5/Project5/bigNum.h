#pragma once

#include <stdbool.h>

typedef struct {
	char** val;
	int length;
	bool sign;
}bigInt;

bigInt result, a, b;



int bigNum(int argc, char** argv);
void getNumbers(int argc, char** argv);
void printBigNum(bigInt *num);
void initNumbers(char** argv);
void check_numbers(int argc, char** argv);

void MULTIPLY(bool sign, bigInt *n1, bigInt *n2);
void ADD(bool sign, bigInt *n1, bigInt *n2);
void SUBTRACT(bool sign, bigInt* n1, bigInt* n2);
void DIVIDE(bool sign, bigInt* n1, bigInt* n2);

void operation_definition(char op);
void swapBigNum(bigInt *n1, bigInt *n2);

void alignment_mult_val(unsigned** mass, bigInt* n1, bigInt* n2);
int get_zero_count(bigInt* num, int i, int j);

void get_numbers_from_console(char** numbers, int argc, char** argv);
int plus_div(char num1[2], int div, int *tmp);


bool clean_cell(int cell);
void plus_interm_val(int* res, int** tmp, int it, int len);
int char_to_int(char ch);
char int_to_char(int n);
