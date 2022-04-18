#include <stdio.h>
#include <stdlib.h>

#include "GENERATE.h"


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
	GENERATE(argc, &argv[0]);
	
	int i = 0, j=0;
	while (i<argc)
	{
		printf("%d ->", i);
		while (1)
		{
			if (argv[i][j] == '\0') //нет нуль терминатора либо не попадает в строку 
				break;
			printf("%c", argv[i][j]);
			j++;
		}
		printf("\n");
		printf("%s\n", argv[i]);
		i++;
	}
	system("pause");
	return 0;
}
