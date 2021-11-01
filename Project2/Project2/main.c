#include <stdlib.h>
#include <stdio.h>

#include "Source.h"



int main(int argc, char* argv[])
{
	FILE* in, * out;
	char SourceMass[512], * ptrSM = &SourceMass[0], *subStr = NULL, *insertedStr=NULL;
	int sizeFile = 0, sizeSubstr=0, sizeInsertedStr=0, i=0;
	printf("File opened: %s", argv[1]);
	printf("Source string: %s   Replaced string: %s", argv[2], argv[3]);
	fopen_s(&in, argv[1], "r");
	fopen_s(&in, "output.txt", "w");
	fseek(in, SEEK_END, 0);
	
	sizeFile = ftell(in);
	insertedStr = argv[3][0];
	subStr = argv[2][0];
	while (1) //получить размер искомой подстроки
	{
		if (subStr[i] != '\0') { i++; }
		else 
			break;
	}
	sizeSubstr = i;
	i = 0;
	while (1) //получить размер заменяемой подстроки
	{
		if (insertedStr[i] != '\0') { i++; }
		else
			break;
	}
	sizeInsertedStr = i;

	if (sizeFile >= 512)
	{
		fgets(ptrSM, 512, in);
	}
	else {
		fgets(ptrSM, sizeFile, in);
	}
	ReplaceSubstring(*ptrSM, *subStr, sizeSubstr, *insertedStr, sizeInsertedStr);

	sytem("pause");
	return 0;
}