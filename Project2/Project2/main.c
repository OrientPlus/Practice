#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "Source.h"



int main(int argc, char* argv[])
{
	int done = 0;
	done = REPLACE(argc, &argv[0]);
	if (done == 0)
		printf("\nThe replacement was successful!\n");
	else
		printf("\nThe replacement function failed with an error!\n");
	system("pause");
	return 0;
}