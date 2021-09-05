#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "calculate.h"


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

	for (int i = 0; i < mass_size; i++)
	{
		for (int j = 0; j < 63; j++)
		{
			if (int_array[i] == j)
			{
				if (int_array[i] <= 9)
				{
					char_array[i] = mass[j];
					printf("\n CHAR == %c // INT == %d\n", char_array[i], int_array[i]);
					break;
				}
				else
				{
					char_array[i] = mass[j-1];
					printf("\n CHAR == %c // INT == %d\n", char_array[i], int_array[i]);
					break;
				}
			}
		}
	}
}