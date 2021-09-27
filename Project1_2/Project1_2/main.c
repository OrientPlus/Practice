#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *out, *in;
	fopen_s("r", "", &in);

	char* FName[50], *mass = NULL;


	printf("Enter the file name:");
	gets_s(FName, 50);
	

	system("pause");
	return 0;
}