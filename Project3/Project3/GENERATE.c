#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"
#include "GENERATE.h"



int GEN(int argc, char** argv)
{
	get_option(argc, &argv[0]);

}

int get_option(int argc, char** argv)
{
	char alph[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char* tmp = NULL;
	int fl_m[2], fl_M[2], fl_n[2] = { 0, 0 }, * fl_a, fl_C[5] = { 0, 0, 0, 0, 0 };
	fl_a = (int*)malloc(63 * sizeof(int));
	int j = 0, n = 0;
	for (int i = 1; i < argc; i += 2)
	{
		j = 0;
		n = 0;
		if (argv[i][1] == 'm')
		{
			fl_m[0] = 1;
			
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;

				if (is_digits(argv[i+1][j]))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-m' option!\n");
					system("pause");
					exit(10);
				}
			}

			fl_m[1] = my_atoi(&(argv[i + 1][0]), 10, n);
			op.minLen = fl_m[1];
		}
		if (argv[i][1] == 'M')
		{
			fl_M[0] = 1;
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;
				if (argv[i + 1][j] == '0' || argv[i + 1][j] == '1' || argv[i + 1][j] == '2' || argv[i + 1][j] == '3' || argv[i + 1][j] == '4' ||
					argv[i + 1][j] == '5' || argv[i + 1][j] == '6' || argv[i + 1][j] == '7' || argv[i + 1][j] == '8' || argv[i + 1][j] == '9')
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-M' option!\n");
					system("pause");
					exit(10);
				}
			}
			fl_M[1] = my_atoi(&(argv[i + 1][0]), 10, n);
			op.maxLen = fl_M[1];
		}
		if (argv[i][1] == 'n')
		{
			fl_n[0] = 1;
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;

				if (argv[i + 1][j] == '0' || argv[i + 1][j] == '1' || argv[i + 1][j] == '2' || argv[i + 1][j] == '3' || argv[i + 1][j] == '4' ||
					argv[i + 1][j] == '5' || argv[i + 1][j] == '6' || argv[i + 1][j] == '7' || argv[i + 1][j] == '8' || argv[i + 1][j] == '9')
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-n' option!\n");
					system("pause");
					exit(10);
				}
			}
			fl_n[1] = my_atoi(&(argv[i + 1][0]), 10, n);
			op.Len = fl_n[1];
		}
		if (argv[i][1] == 'a')
		{
			fl_a[0] = 1;
			while (1)
			{
				if (argv[i + 1][j] == '\0')
				{
					fl_a[j + 1] = '\0';
					break;
				}

				for (int _j = 0; _j < 62; _j++)
				{
					if (argv[i + 1][j] == alph[_j])
					{
						fl_a[j + 1] = argv[i + 1][j];
						break;
					}
					else if (_j == 61) {
						printf("\n Incorrect arguments in '-a' option!\n");
						system("pause");
						exit(10);
					}
				}
				j++;
			}
			op.alph = &fl_a[1];
		}
		if (argv[i][1] == 'C')
		{
			op.def_alph.flag = 1;
			while (1)
			{
				if (argv[i][j+1] == '\0') //проверка на пустую опцию -— нужна, может выйти сразу
					break;

				if (check_C_option(&argv[i][j+2])) //обрабатывает корректно веро€тность пока только одного алфавита "а"
				{                                  //не пон€тно пока как обработать все значени€ веро€тности в опции -—
					j++;                           //возможно нужно сначала пробежатьс€ по аргументу и провести анализ на кол-во заходов в ф-ю
				}
				else {
					printf("\n Incorrect arguments in '-C' option!\n");
					system("pause");
					exit(10);
				}
			}
		}
	}
	return 0;
}

int check_C_option(char *argv)
{
	int length = 0, j=0;
	static int it_lucky = 0;
	if ((argv[j] == 'a' && j < 6))
	{
		op.def_alph.plenty_a = 1;


		if (argv[j + 1] == '[')
		{
			while (argv[j] != '\0')
			{
				j+=2;
				for (int i = 0; i < 2; i++)
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-a' is incorrectly set\n");
						system("pause");
						exit(10);
					}
				}
				op.def_alph.lucky[it_lucky] = my_atoi(&argv[j - 2], 10, length);
				it_lucky++;
			}
		}
		return 1;
	}
	if ((argv[j] == 'A' && j < 4))
	{
		op.def_alph.plenty_A = 1;
		return 1;
	}
	if ((argv[j] == 'D' && j < 4))
	{
		op.def_alph.plenty_D = 1;
		return 1;
	}
	if ((argv[j] == 'S' && j < 4))
	{
		op.def_alph.plenty_S = 1;
		return 1;
	}
	return 0;
}

int is_digits(char var)
{
	if (var == '0' || var == '1' || var == '2' || var == '3' || var == '4' ||
		var == '5' || var == '6' || var == '7' || var == '8' || var == '9')
		return 1;
	else
		return 0;
}

int is_a_alphabet(char var)
{
	char alphabet[] = { "abcdefghijklmnopqrstuvwxyz" };
	for (int i = 0; i < 26; i++)
	{
		if (var == alphabet[i])
			return 1;
		if (i == 25)
			return 0;
	}
}