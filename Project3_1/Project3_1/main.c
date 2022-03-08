#include <stdio.h>
#include <stdlib.h>

#include "aitoia.h"

typedef struct {
	int minLen, maxLen, Len;
	char* alph, * def_alph;
}option;

int translate(char* tmp)
{
	int conclusion = 0, i = 0;
	while (tmp[i] == '0' || tmp[i]=='1' || tmp[i]=='2')
	{
		conclusion = conclusion*10 + (tmp[i] - '0');
		i++;
	}
	return conclusion;
}

int main(int argc, char** argv)
{
	option op;
	char* user_input = NULL;
	int j = 0, i = 0;
	user_input = (char*)calloc(user_input, 50 * sizeof(char));
	for (int _i = 1; _i < argc; _i++)
	{
		j = 0;
		while (argv[_i][j] != '\0')
		{
			user_input[i] = argv[_i][j];
			j++; i++;
		}
	}
	user_input[i] = '\0';

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == 'm')
		{
			op.minLen = translate(&user_input[i+1]);
			printf("\n minimum =======> %d", op.minLen);
		}
		i++;
	}

	system("pause");
	return 0;
}

int get_option(int argc, char** argv)
{
	int fl_m[2], fl_M[2], fl_n[2] = 0, *fl_a, fl_C[5] = 0;
	fl_a = (int*)malloc(40 * sizeof(int));
	int j = 0, n = 0;
	for (int i = 0; i < argc; i+=2)
	{
		if (argv[i][1] == 'm')
		{
			fl_m[0] = 1;
			while (argv[i + 1][j] = !'\0')
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments!");
					exit(10);
					system("pause");
				}
			}
			fl_m[1] = my_atoi(argv[i + 1][0], 10, n);
		}
		if (argv[i][1] == 'M')
		{
			fl_M[0] = 1;
			while (argv[i + 1][j] = !'\0')
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments!");
					exit(10);
					system("pause");
				}
			}
			fl_M[1] = my_atoi(argv[i + 1][0], 10, n);
		}
		if (argv[i][1] == 'n')
		{
			fl_n[0] = 1;
			while (argv[i + 1][j] = !'\0')
			{
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9'))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments!");
					exit(10);
					system("pause");
				}
			}
			fl_n[1] = my_atoi(argv[i + 1][0], 10, n);
		}
		if (argv[i][1] == 'a')
		{
			fl_a[0] = 1;
			while (argv[i + 1][j] = !'/0')
			{
				while (1)
				{
					if (argv[i+1][j] == alph[])
				}
				if (argv[i + 1][j] == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' ||))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments!");
					exit(10);
					system("pause");
				}
			}
			fl_M[1] = my_atoi(argv[i + 1][0], 10, n);
		}
		if (argv[i][1] == 'C')
		{
			fl_C[0] = 1;
			while (argv[i + 1][j] =! '\0')
			{
				if (argv[i + 1][j] == ('a'|| 'A' || 'D' || 'S') && (j<4))
				{
					j++;
					fl_C[j+1] = argv[i + 1][j];
				}
				else {
					printf("\n Incorrect arguments!");
					exit(10);
					system("pause");
				}
			}
		}
	}
}

int translate()
{

}