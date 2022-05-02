#include <stdio.h>
#include <stdlib.h>

#include "bigNum.h"

int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		printf("\narg[%d] = %s", i, argv[i]);
	}
	bigNum(argc, &argv[0]);
	
	
	printf("\n\n");
	system("pause");
	return 0;
}