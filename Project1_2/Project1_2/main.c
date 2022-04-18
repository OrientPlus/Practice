#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include "calculate.h"

int check_file(FILE *in)
{
	int ch = 0, empty=0;
	while (1)
	{
		ch = fgetc(in);
		if (ch != EOF)
		{
			empty++;
		}
		else
			break;
	}
	if (empty <= 1)
	{
		printf("File is empty!\n");
		return -1;
	}
	else {
		fseek(in, 0, SEEK_SET);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	printf("Entered file: %s\n", argv[1]);
	int tmp = 0, i=0, move=0, iterator_mass=0, empty_flag=0;
	char *ptr = NULL, *tmp_mass = NULL;
	tmp_mass = (char*)malloc(32 * sizeof(char));
	FILE* in;
	fopen_s(&in, argv[1], "r");
	empty_flag = check_file(in);
	if (empty_flag == -1)
	{
		system("pause");
		return -1;
	}
	if (!in)
	{
		printf("\nFile cannot open!\n");
		system("pause");
		exit(1);
	}
	while (1)
	{
		tmp = fgetc(in);
		if (tmp == EOF)
			break;
		if (tmp == ('\n' || '\a' || '\b' || '\t' || '\v' || '\f' || '\r' || '\e'))
			continue;

		if (tmp == 92)
		{
			tmp = fgetc(in);
			tmp_mass[iterator_mass] = '?';
			if (tmp == 97)
				tmp = 7;
			else if (tmp == 98)
				tmp = 8;
			else if (tmp == 116)
				tmp = 9;
			else if (tmp == 110)
				tmp = 10;
			else if (tmp == 118)
				tmp = 11;
			else if (tmp == 102)
				tmp = 12;
			else if (tmp == 114)
				tmp = 13;
			else if (tmp == 0)
				tmp == 0;
			else if (tmp == 101)
				tmp = 27;
		}
		else {
			tmp_mass[iterator_mass] = tmp;
		}

		ptr = my_itoa(tmp, 16);
		while (ptr[i] != '\0')
		{
			if (ptr[1]== '\0')
				printf("0");
			printf("%c", ptr[i]);
			i++;
		}
		printf(" ");
		move++;
		iterator_mass++;
		if (move == 16)
		{
			printf("   | ");
			for (int it = 0; it < iterator_mass; it++)
			{
				printf("%c", tmp_mass[it]);
			}
			printf("\n");
			move = 0;
			iterator_mass = 0;
		}
		i = 0;
	}
	if (empty_flag == 0)
	{
		for (move; move < 16; move++) //выравнивание символьной строки
		{
			printf("   ");
		}

		printf("   | ");
		for (int it = 0; it < iterator_mass; it++)
		{
			printf("%c", tmp_mass[it]);
		}
	}
	else {
		printf("File is empty!\n");
	}
	free(tmp_mass);
	fclose(in);
	printf("\n");
	system("pause");
	return 0;
}