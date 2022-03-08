#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "Source.h"



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".1251");
	FILE* in;
	char *sourceString = NULL, *subStr = NULL, *insertedStr=NULL;
	int sizeFile = 0, sizeSubstr=0, sizeInsertedStr=0, sizeSM=0, i=0, it_read=0, tmp =1;

	sourceString = (char*)malloc(512 * sizeof(char));
	
	printf("Source file: %s\n", argv[1]);
	printf("Source string: %s\nReplaced string: %s\n", argv[2], argv[3]);
	
	fopen_s(&in, argv[1], "r");
	while (!feof(in))
	{
		tmp = fgetc(in);
		sizeFile++;
	}

	insertedStr = &argv[3][0];
	subStr = &argv[2][0];

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

	i = (sizeFile / 512) + 1;
	fseek(in, 0, SEEK_SET);
	if (sizeFile >= 512) //если файл больше 512 байт считываем блоками
	{
		while (i != 0)
		{
			it_read = 0;
			while(it_read < 512 && !feof(in))
			{
				fscanf_s(in, "%c", &sourceString[it_read]);
				it_read++;
			}
			i--;
			if (i == 0) sourceString = (char*)realloc(sourceString, (it_read-1)*sizeof(char));
			it_read--;
			ReplaceSubstring(&sourceString[0], it_read, &subStr[0], sizeSubstr, &insertedStr[0], sizeInsertedStr); //ф-я замены подстроки
		}
	}
	else
	{
		for (int j = 0; j < sizeFile; j++)
			fscanf_s(in, "%c", &sourceString[j]);//если меньше считываем весь файл
		sourceString[sizeFile - 1] = '\0';
		sizeFile--;
		ReplaceSubstring(&sourceString[0], sizeFile, &subStr[0], sizeSubstr, &insertedStr[0], sizeInsertedStr); //ф-я замены подстроки
	}
	free(sourceString);
	fclose(in);
	system("pause");
	return 0;
}