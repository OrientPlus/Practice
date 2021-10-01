#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include "calculate.h"

int main()
{
	FILE *in;
	int size_fn = 1, i = 0, size_mass = 150, concl=0;
	char* ptr_fn = (char*)malloc(250 * sizeof(char)),
		* mass = (char*)calloc(size_mass, 150 * sizeof(char));

	printf("Enter file name:");
	gets(ptr_fn);
	while (ptr_fn[size_fn] != '\0')
	{
		size_fn++;
	}
	size_fn++;
	ptr_fn = (char*)realloc(ptr_fn, size_fn * sizeof(char)); //Оптимизируем память под имя файла


	fopen_s(&in, ptr_fn, "r");
	while (!feof(in))
	{
		if (i == size_mass)
		{
			size_mass += 100;
			mass = (char*)realloc(mass, size_mass * sizeof(char));
		}
		fscanf_s(in, "%c", &mass[i]);
		i++;
	}
	for (int j = 0; j < i; ++j)
	{
		concl = my_atoi(&mass[j], 16, 1);
		printf(" ==> %d\n", concl);
	}
	

	system("pause");
	return 0;
}