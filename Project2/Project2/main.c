#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "Source.h"



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".1251");
	REPLACE(argc, &argv[0]);
	system("pause");
	return 0;
}