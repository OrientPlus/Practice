#pragma once

typedef struct {
	unsigned* val;
	int length;
}bigInt;

bigInt num1, num2, result;


int bigNum(int argc, char** argv);
void getNumbers(int argc, char** argv);
void printBigNum(bigInt *num);
void initNumbers(char** argv);
void divide();
void multiply();
void add();
void subtract();
void remains();