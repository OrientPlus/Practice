#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

#include "GENERATE.h"

int main(int argc, char* argv[])
{
	int j = 0;
	int choise = 0;
	
	GEN(argc, &argv[0]);

	while (1)
	{
		printf("\n\tGENERATE AGAIN? \n(ENTER - yes, another key - no):");
		choise = 0;
		choise = getch(stdin);
		if (choise == 13)
			GEN(argc, &argv[0]);
		else
			break;
	}
	printf("\n");
	system("pause");
	return 0;
}