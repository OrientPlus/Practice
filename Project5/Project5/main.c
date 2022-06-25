#include <stdio.h>
#include <stdlib.h>

#include "bigNum.h"

int main(int argc, char** argv)
{
	bigNum(argc, &argv[0]);
	printf("\n\n");
	system("pause");
	return 0;
}