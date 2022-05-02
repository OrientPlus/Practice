#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bigNum.h"



int bigNum(int argc, char** argv)
{	
	char operation = 0;
	initNumbers(&argv[0]);
	getNumbers(argc, &argv[0]);
	printBigNum(&num1);
	printBigNum(&num2);

	operation = argv[2][0];
	if (operation == '/')
		divide();
	else if (operation == '*')
		multiply();
	else if (operation == '+')
		add();
	else if (operation == '-')
		subtract();
	else if (operation == '%')
		remains();
	else {
		printf("\nERROR! Invalid operation!\n");
		system("pause");
		exit(1);
	}

	free(num1.val);
	free(num2.val);
}

void initNumbers(char** argv)
{
	num1.length = strlen(argv[1]) / 9;
	if (strlen(argv[1]) - 9 * num1.length > 0)
		num1.length++;
	num2.length = strlen(argv[3]) / 9;
	if (strlen(argv[3]) - 9 * num1.length > 0)
		num2.length++;
	num1.val = (unsigned*)malloc(num1.length * sizeof(unsigned));
	num2.val = (unsigned*)malloc(num2.length * sizeof(unsigned));
	
	for (int i = 0; i < num1.length; i++)
		num1.val[i] = 0;
	for (int i = 0; i < num2.length; i++)
		num2.val[i] = 0;
}

void getNumbers(int argc, char** argv)
{
	int it = 0,
		strLen, n;
	unsigned tmp = 0;
	
	
	
	it = num1.length - 1;;
	strLen = strlen(argv[1]);
	for (int i = 0; i < strLen / 9 + 1; i++)
	{
		n = 9 * (i + 1);
		for (int j = 9; j > 0; j--)
		{
			if (strLen - n >=0)
				tmp = tmp * 10 + argv[1][strLen - n] - '0';
			n--;
		}
		num1.val[it] = tmp;
		tmp = 0;
		it--;
	}

	tmp = 0;
	it = num2.length-1;
	strLen = strlen(argv[3]);
	for (int i = 0; i < strLen / 9 + 1; i++)
	{
		n = 9 * (i + 1);
		for (int j = 9; j > 0; j--)
		{
			if (strLen - n >= 0)
				tmp = tmp * 10 + argv[3][strLen - n] - '0';
			n--;
		}
		num2.val[it] = tmp;
		tmp = 0;
		it--;
	}
	
}

void printBigNum(bigInt *num)
{
	printf("\nBig num: ");
	for (int i = 0; i < num->length; i++)
	{
		if (num->val[i] != 0)
			printf("%u", num->val[i]);
	}
	printf("\n");
}

void add()
{
	unsigned x = 0, y = 0, divide = 0,
		X = 0, Y = 0;
	int n1_it = num1.length - 1, n2_it = num2.length - 1;
	int str[4][9]; //память нужна в куче, под длину максимального числа

	if (num1.length > num2.length)
		result.length = num1.length + 1;
	else
		result.length = num2.length + 1;
	result.val = (unsigned)malloc(result.length * sizeof(unsigned));
	for (int i = 0; i < result.length; i++)
	{
		if (n1_it != -1)
			X = num1.val[n1_it];
		if (n2_it != -1)
			Y = num2.val[n2_it];
		if (n1_it == -1 && n2_it == -1)
			break;
		if (result.length == 2)
			;
		else {
			for (int j = 0; j < 9; j++)
			{
				x = X % 10;
				y = Y % 10;
				if (x == 0 || y == 0)
				{
					if (divide == 1)
					{
						x += divide;
						divide = 0;
					}
					str[3 - i][8 - j] = x;
					X = X / 10;
					Y = Y / 10;
					continue;
				}
				x += y + divide;
				if (x >= 10)
				{
					divide = 1;
					x = x % 10;
				}
				else 
					divide = 0;
				str[3-i][8-j] = x;
				X = X / 10; 
				Y = Y / 10;
			}
		}
			n1_it--;
			n2_it--;
	}
	printf("\nRESULT: ");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d", str[i][j]);
		}
	}
}

void subtract()
{

}

void multiply()
{

}

void divide()
{

}

void remains()
{

}