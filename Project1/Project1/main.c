#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "Calculate.h"


int main()
{
	setlocale(0, "ru");
	int n = 0,
		notation,
		size_first_array = 12,
		i = 0,
		switch_on = 0;
	long long int
		ItoA = 0;
	char* first_array = (char*)malloc(size_first_array * sizeof(char)), 
		*ptr=NULL;

	printf("Μενώ:\t(1) - my_atoi\n \t(2) - my_itoa\n:");
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
		printf("Enter value:");
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
				if (i == size_first_array - 1)
				{
					size_first_array = size_first_array + 3;
					first_array = (char*)realloc(first_array, size_first_array * sizeof(char));
				}
			}
		}
		if (i < size_first_array - 1) 
		{
			first_array = (char*)realloc(first_array, i * sizeof(char));
			size_first_array = i;
		}
		n = my_atoi(&first_array[0], notation, size_first_array);
		printf("\nNUMBER = %d\n", n);
		break;

	case 2:
		printf("\n Enter number\n:");
		scanf_s("%lld", &ItoA);
		if (ItoA > INT_MAX || ItoA < INT_MIN)
		{
			printf("\n\tERROR #20. The entered value goes beyond the INT type!\n");
			system("pause");
			exit(20);
		}
		else if (ItoA == 0)
		{
			printf("Translated number: %d", 0);
			printf("\n\n\n");
			system("pause");
			return 0;
		}

		ptr = my_itoa(ItoA, notation);
		i = 0;
		printf("Translated number: ");
		while (ptr[i] != '\0')
		{
			printf("%c", ptr[i]);
			i++;
		}
		break;
	}

	printf("\n\n\n");
	system("pause");
	return 0;
}