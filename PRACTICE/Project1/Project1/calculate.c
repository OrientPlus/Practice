#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "calculate.h"


int my_atoi(char* array_symbols, int not, int size_array_symbols)
{
	int tmp = 0, * array_codes, i = 0, output = 0;
	long int Ltmp = 0;
	array_codes = (int*)malloc(size_array_symbols * sizeof(int));
	for (int j = 0; j < size_array_symbols; j++)
	{
		array_codes[j] = 0;
	}

	for (int j = 0; j < size_array_symbols; j++)
	{
		if ((array_symbols[j] >= '0') & (array_symbols[j] <= '9'))
		{
			tmp = tmp * 10 + (array_symbols[j] - '0');
			array_codes[i] = tmp;
			i++;
			tmp = 0;
		}
		if ((array_symbols[j] >= 'a') & (array_symbols[j] <= 'z'))
		{
			tmp = tmp * 10 + (array_symbols[j] - '0') - 13;
			array_codes[i] = tmp;
			i++;
			tmp = 0;
		}
		if ((array_symbols[j] >= 'A') & (array_symbols[j] <= 'Z')) {
			tmp = tmp * 10 + (array_symbols[j] - '0') - 7;
			array_codes[i] = tmp;
			i++;
			tmp = 0;
		}
	}

	output = translate_code_to_number(&array_codes[0], size_array_symbols, not);
	return output;
}

int my_itoa(int N, int notation)
{
	int a = 0, b = 0, size_code_array = 0, i = 0;
	int* code_array = NULL;
	char* enter_array = NULL;
	a = N;
	while (a != 0)
	{
		b = N % notation;
		a = N / notation;
		N = N / notation;
		if (i == size_code_array)
		{
			size_code_array += 4;
			code_array = (int*)realloc(code_array, size_code_array * sizeof(int));
		}
		code_array[i] = b;
		i++;
	}

	if (i <= size_code_array) //Оптимизируем память
	{
		i++;
		size_code_array = i;
		code_array = (int*)realloc(code_array, size_code_array * sizeof(int));
	}

	enter_array = (char*)calloc(enter_array, i * sizeof(char));
	translate_number_to_string(size_code_array, &code_array[0], notation, &enter_array[0]);
	return &enter_array[0];
}


int sqr(int number, int power)
{
	unsigned long long int tmp = number;
	int base = number;
	if (power == 0)
	{
		number = 1;
		return number;
	}
	else if (power == 1)
		return number;
	else {
		for (int i = 0; i < (power - 1); i++)
		{
			if (tmp * base > INT_MAX)
			{
				printf("\n\tERROR #3! You entered so big value! The value is outside the int type.\n");
				system("pause");
				exit(3);
			}
			number = number * base;
			tmp = tmp * base;
		}
		return number;
	}
}

int translate_code_to_number(int* mass, int size, int notation)
{
	int _notation = check_notation(&mass[0], size);
	if (notation == 0)
	{
		notation = check_notation(&mass[0], size);
	}
	else if (_notation > notation - 1)
	{
		printf("\n\tERROR #2! The entered character does not match the specified number system!\n");
		system("pause");
		exit(2);
	}
	int result = 0, Sqr = 0;
	for (int i = 0, power = size - 1; i < size; i++, power--)
	{
		Sqr = sqr(notation, power);
		if ((result + mass[i] * Sqr) > INT_MAX)
		{
			printf("\n\tERROR #3! You entered so big value! The value is outside the int type.\n");
			system("pause");
			exit(3);
		}
		result = result + mass[i] * Sqr;
	}
	return result;
}

int check_notation(int* mass, int size)
{
	int max_Notation = 0;
	for (int i = 0; i < size; i++)
	{
		if (mass[i] > max_Notation)
		{
			max_Notation = mass[i];
		}
	}
	return max_Notation;
}

int translate_number_to_string(int mass_size, int* int_array, int notation, char* char_array)
{
	char mass[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	char tmp = 0;
	int n = 0;

	for (int i = 0; i < mass_size; i++)
	{
		for (int j = 0; j < 63; j++)
		{
			if (int_array[i] == j)
			{
				char_array[i] = mass[j];
				break;
			}
		}
	}

	n = mass_size - 2;
	for (int i = 0; i < mass_size/2; i++)
	{
		tmp = char_array[i];
		char_array[i] = char_array[n];
		char_array[n] = tmp;
		n--;
	}
	char_array[mass_size - 1] = '\0';

}

int check_enter(int N)
{
	if ((N >= '0' & N <= '9') || (N >= 'A' & N <= 'Z') || (N >= 'a' & N <= 'z') || (N == '\n'))
	{
		return 0;
	}
	else
	{
		printf("\n\tERROR #4! Invalid symbols!\n");
		system("pause");
		exit(4);
	}
}