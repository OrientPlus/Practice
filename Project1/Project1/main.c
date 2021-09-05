#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "Calculate.h"

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

	if (i <= size_code_array) //ќптимизируем пам€ть
	{
		i++;
		size_code_array = i;
		code_array = (int*)realloc(code_array, size_code_array * sizeof(int));
	}

	enter_array = (char*)calloc(enter_array, i * sizeof(char));
	translate_number_to_string(size_code_array, &code_array[0], notation, &enter_array[0]);
	return &enter_array[0];
}

int main()
{
	setlocale(0, "ru");
	int n = 0,
		notation,
		size_first_array = 5,
		i = 0,
		switch_on = 0,
		ItoA = 0;
	char* first_array = (char*)malloc(size_first_array * sizeof(char)), 
		*ptr=NULL;

	printf("ћеню:\t(1) - my_atoi\n \t(2) - my_itoa\n:");
	scanf_s("%d", &switch_on);
	if (switch_on < 1 || switch_on > 2)
	{
		printf("\nERROR! #5 Menu does not understand you!\n");
		system("pause");
		exit(5);
	}
	system("cls");

	printf("Enter notation of number:");
	scanf_s("%d", &notation);
	if (notation > 62 || notation < 0 || notation == 1)
	{
		printf("\n\tERROR #1. You entered invalid notation! Try again.\n");
		system("pause");
		exit(1);
	}

	switch (switch_on)
	{
	case 1:
		n = fgetc(stdin);
		while (1)
		{
			n = fgetc(stdin);
			check_enter(n);
			if (n == '\n')
				break;
			else {
				first_array[i] = n;
				i++;
				if (i >= size_first_array - 1)
				{
					size_first_array = size_first_array + 2;
					first_array = (int*)realloc(first_array, size_first_array * sizeof(int));
				}
			}
		}
		if (i <= size_first_array - 1) //ќптимизируем пам€ть, избавл€емс€ от пустых €чеек в массиве
		{
			first_array = (int*)realloc(first_array, i * sizeof(int));
			size_first_array = i;
		}
		n = my_atoi(&first_array[0], notation, size_first_array);
		printf("\nNUMBER = %d\n", n);
		break;

	case 2:
		printf("\n Enter number\n:");
		scanf_s("%d", &ItoA);
		ptr = my_itoa(ItoA, notation);
		i = 0;
		while (ptr[i] != '\0')
		{
			printf("\n TRANSLATED INT ===> %c", ptr[i]);
			i++;
		}
		break;
	}

	printf("\n");
	system("pause");
	return 0;
}