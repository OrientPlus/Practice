#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include "calculate.h"

int main(int argc, char* argv[])
{
	printf("Entered file: %s\n", argv[1]);
	int tmp = 0, i=0, move=0, iterator_mass=0;
	char* ptr = NULL, *tmp_mass = NULL;
	tmp_mass = (char*)malloc(32 * sizeof(char));
	FILE* in;
	fopen_s(&in, argv[1], "r");
	while (1)
	{
		tmp = fgetc(in);
		if (tmp == EOF)
			break;

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
			printf("%c", ptr[i]);
			i++;
		}
		printf(" ");
		move++;
		iterator_mass++;
		if (move == 16)
		{
		/*	tmp_mass[iterator_mass++] = '\0';*/
			printf("   | ");
			for (int I = 0; I < iterator_mass; I++)
			{
				printf("%c", tmp_mass[I]);
			}
			printf("\n");
			move = 0;
			iterator_mass = 0;
		}
		i = 0;
	}

	printf("   | ");
	for (int I = 0; I < iterator_mass; I++)
	{
		printf("%c", tmp_mass[I]);
	}
	free(tmp_mass);
	printf("\n");
	system("pause");
	return 0;
}