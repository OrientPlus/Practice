#include <stdlib.h>
#include <stdio.h>

#include "aitoia.h"


void GENERATE(int argc, char** argv)
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
	fl_a = (int*)malloc(62 * sizeof(int));
	int j = 0, n = 0;
	for (int i = 1; i < argc; i += 2)
	{
		j = 0;
		if (argv[i][1] == 'm')
		{
			fl_m[0] = 1;
			while (argv[i + 1][j] = !"\0")
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
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
			break;
		}
		if (argv[i][1] == 'M')
		{
			fl_M[0] = 1;
			while (argv[i + 1][j] = !"\0")
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
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
			break;
		}
		if (argv[i][1] == 'n')
		{
			fl_n[0] = 1;
			while (argv[i + 1][j] = !"\0")
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
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
			break;
		}
		if (argv[i][1] == 'a')
		{
			fl_a[0] = 1;
			while (argv[i + 1][j] = !"\0")
			{
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
			break;
		}
		if (argv[i][1] == 'C')
		{
			fl_C[0] = 1;
			while (argv[i + 1][j] = !"\0")
			{
				if (argv[i + 1][j] == ('a' || 'A' || 'D' || 'S') && (j < 4))
				{
					fl_C[j + 1] = argv[i + 1][j];
					j++;
				}
				else {
					printf("\n Incorrect arguments in '-C' option!\n");
					system("pause");
					exit(10);
				}
			}
			break;
		}
	}
}