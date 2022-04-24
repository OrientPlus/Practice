#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

#include "calculate.h"


int my_atoi(char* array_symbols, int not, int size_array_symbols)
{
	if (size_array_symbols == 0 || array_symbols == NULL || array_symbols[0] == '\0')
	{
		printf("\n#my_aitoia::ERROR! You entered empty string.\n");
		system("pause");
		exit(3);
	}
	int tmp = 0, *array_codes = NULL, it = 0, output = 0, flag = 0;
	array_codes = (int*)calloc(array_codes, size_array_symbols * sizeof(int));

	if (array_symbols[0] == 45) //Обработка отрицательных значений, убираем минус в 0 элементе массива
	{
		for (int i = 0; i < size_array_symbols - 1; i++)
		{
			array_symbols[i] = array_symbols[i + 1];
		}
		array_symbols = (char*)realloc(array_symbols, (size_array_symbols - 1) * sizeof(char));
		flag = 1;
		size_array_symbols--;
	}

	for (int j = 0; j < size_array_symbols; j++)
	{
		if ((array_symbols[j] >= '0') & (array_symbols[j] <= '9'))
		{
			tmp = tmp * 10 + (array_symbols[j] - '0');
			array_codes[it] = tmp;
			it++;
			tmp = 0;
		}
		if ((array_symbols[j] >= 'a') & (array_symbols[j] <= 'z'))
		{
			tmp = tmp * 10 + (array_symbols[j] - '0') - 13;
			array_codes[it] = tmp;
			it++;
			tmp = 0;
		}
		if ((array_symbols[j] >= 'A') & (array_symbols[j] <= 'Z')) {
			tmp = tmp * 10 + (array_symbols[j] - '0') - 7;
			array_codes[it] = tmp;
			it++;
			tmp = 0;
		}
	}

	output = translate_string_to_number(&array_codes[0], size_array_symbols, not);
	if (flag == 1)
	{
		output = output * (-1);
	}
	if (output == 0)
	{
		printf("\n#my_aitoia::WARNING! Zero was passed to the function!\n");
	}
	return output;
}

int my_itoa(int N, int notation)
{
	if (notation <= 1)
	{
		printf("\n#my_aitoia::ERROR! When translating from a number to a string, the number system must be specified! (not>=2)\n");
		system("pause");
		exit(3);
	}
	int a = 0, b = 0, size_code_array = 0, i = 0, flag=0;
	int* code_array = NULL;
	char* enter_array = NULL;
	if (N < 0)
	{
		N = N*(-1);
		flag = 1;
	}
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

	enter_array = (char*)calloc(enter_array, (i+1) * sizeof(char));
	translate_number_to_string(size_code_array+1, &code_array[0], notation, &enter_array[0]);
	if (flag == 1)
	{
		enter_array[0] = '-';
	}
	else {
		for (int j = 0; j < size_code_array-1; ++j)
		{
			enter_array[j] = enter_array[j + 1];
		}
		enter_array[size_code_array - 1] = '\0';
	}
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
			if ((tmp * base) > INT_MAX)
			{
				printf("\n#my_aitoia::ERROR #3! You entered so big value! The value is outside the INT type.\n");
				system("pause");
				exit(3);
			}
			number = number * base;
			tmp = tmp * base;
		}
		return number;
	}
}

int translate_string_to_number(int* mass, int size, int notation)
{
	int _notation = check_max_notation(&mass[0], size);
	if (notation == 0)
	{
		notation = check_max_notation(&mass[0], size);
	}
	else if (_notation > notation )
	{
		printf("\n#my_aitoia::ERROR #2! The entered character does not match the specified number system!\n");
		system("pause");
		exit(2);
	}
	unsigned long long int result = 0, Sqr = 0;
	for (int i = 0, power = (size - 1); i < size; i++, power--)
	{
		Sqr = sqr(notation, power);
		if ((result + mass[i] * Sqr) > INT_MAX)
		{
			printf("\n#my_aitoia::ERROR #3! You entered so big value! The value is outside the int type.\n");
			system("pause");
			exit(3);
		}
		result = result + mass[i] * Sqr;
	}
	return result;
}

int check_max_notation(int* mass, int size)
{
	int max_Notation = 0;
	for (int i = 0; i < size; i++)
	{
		if (mass[i] > max_Notation)
		{
			max_Notation = mass[i];
		}
	}
	return max_Notation+1;
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
				char_array[i+1] = mass[j];
				break;
			}
		}
	}

	n = mass_size - 2;
	for (int i = 1; i < mass_size/2; i++)
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
	static int point = 0;
	if ((N >= '0' & N <= '9') || (N >= 'A' & N <= 'Z') || (N >= 'a' & N <= 'z') || (N == '\n'))
	{
		return 0;
	}
	else if (N == 45 & point == 0)
	{
		point = 1;
		return 0;
	}
	else
	{
		printf("\n#my_aitoia::ERROR #4! Invalid symbols!\n");
		system("pause");
		exit(4);
	}
}
