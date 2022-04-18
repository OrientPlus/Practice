#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

#include "GENERATE.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int j = 0;
	for (int i = 0; i < argc; i++)
	{
		printf("%d -> ", i);
		printf("%s\n", argv[i]);
	}
	j = 0;
	while (argv[2][j] != '\0')
	{
		printf("%c", argv[2][j]);
		j++;
	}
	GEN(argc, &argv[0]);
	system("pause");
	return 0;
}