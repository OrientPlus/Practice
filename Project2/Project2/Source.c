#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "Source.h"


void ReplaceSubstring(char* sourceMass, int sizeSM, char* subStr, int sizeSubstr, char* insertedStr, int sizeInsStr) 
{
	FILE* out;
	fopen_s(&out, "output.txt", "a");

	int _i = 0,
		* massIndex = (int*)malloc(512 * sizeof(int));

	for (int i = 0; i < 512; i++) 
	{
		if (sourceMass[i] == '\0')
			break;
		if (sourceMass[i] == subStr[0])
		{
			if (comparison_of_substrings(i, &subStr[0], &sourceMass[0], sizeSubstr) == 1)
			{
				massIndex[_i] = i;
				_i++;
			}	
		}
	}

	massIndex = (int*)realloc(massIndex, _i * sizeof(int)); 

	if (massIndex == NULL)
	{
		for (int i = 0; i < sizeSM; i++)
		{
			fprintf(out, "%c", sourceMass[i]);
		}
		fclose(out);
		return 1;
	}

	_i = 0;
	for (int i=0; i < sizeSM; i++)
	{
		if (i != massIndex[_i])
		{ 
			fprintf(out, "%c", sourceMass[i]); 
		}
		else {
			for (int j = 0; j < sizeInsStr; j++)
			{
				fprintf(out, "%c", insertedStr[j]);
			}
			i = i + (sizeSubstr-1);
			_i++;
		}
	}
	free(massIndex);
	fclose(out);
}

int comparison_of_substrings(int j, char* subStr, char* sourceStr, int sizeSubstr)
{
	int i=0;
	while (i<sizeSubstr)
	{
		if (subStr[i] == sourceStr[j])
		{
			i++; j++;
		}
		else {
			return 0;
		}
	}
	return 1;
}

int REPLACE(int argc, char* argv[])
{
	if (argv < 3)
	{
		printf("\nERROR #1. Not enough arguments passed!\n");
		return 1;
	}

	FILE* in;
	char* sourceString = NULL, * subStr = NULL, * insertedStr = NULL;
	int sizeFile = 0, sizeSubstr = 0, sizeInsertedStr = 0, sizeSM = 0, i = 0, it_read = 0, tmp = 1;

	sourceString = (char*)malloc(512 * sizeof(char));

	printf("Source file: %s\n", argv[1]);
	printf("Source string: %s\nReplaced string: %s\n", argv[2], argv[3]);

	fopen_s(&in, argv[1], "r");
	if (!in)
	{
		printf("\nERROR #2. File cannot open!\n");
		return 2;
	}
	while (!feof(in))
	{
		tmp = fgetc(in);
		sizeFile++;
	}

	if (sizeFile == 1)
	{
		printf("ERROR #3. File is empty!\n");
		return 3;
	}
	insertedStr = &argv[3][0];
	subStr = &argv[2][0];

	while (1) 
	{
		if (subStr[i] != '\0') { i++; }
		else
			break;
	}
	sizeSubstr = i;
	i = 0;

	if (sizeSubstr == sizeFile)
	{
		for (int it = 0; it < sizeFile; i++)
		{
			fprintf(in, "%c", subStr[i]);
		}
		return 0;
	}

	while (1) 
	{
		if (insertedStr[i] != '\0') { i++; }
		else
			break;
	}
	sizeInsertedStr = i;

	i = (sizeFile / 512) + 1;
	fseek(in, 0, SEEK_SET);
	if (sizeFile >= 512) 
	{
		while (i != 0)
		{
			it_read = 0;
			while (it_read < 512 && !feof(in))
			{
				fscanf_s(in, "%c", &sourceString[it_read]);
				it_read++;
			}
			i--;
			if (i == 0) sourceString = (char*)realloc(sourceString, (it_read - 1) * sizeof(char));
			it_read--;
			ReplaceSubstring(&sourceString[0], it_read, &subStr[0], sizeSubstr, &insertedStr[0], sizeInsertedStr); 
		}
	}
	else
	{
		for (int j = 0; j < sizeFile; j++)
			fscanf_s(in, "%c", &sourceString[j]);
		sourceString[sizeFile - 1] = '\0';
		sizeFile--;
		ReplaceSubstring(&sourceString[0], sizeFile, &subStr[0], sizeSubstr, &insertedStr[0], sizeInsertedStr); 
	}
	free(sourceString);
	fclose(in);
	return 0;
}

//void checkLastBlock(char* sourceMass, int sizeSM, char* subStr, int sizeSubstr)
//{
//	static int lastBlock[1024], flag = 1;
//	int it = 512 - sizeSubstr;
//	if (flag % 2 == 1)
//	{
//		for (int i = 0; i < 512; i++)
//		{
//			lastBlock[i] = sourceMass[i];
//		}
//	}
//	else {
//		for (int i = 512; i < 1024; i++)
//		{
//			lastBlock[i] = sourceMass[i-512];
//		}
//	}
//
//	for (int i=0; i<sizeSubstr; i++)
//	{
//		if (lastBlock[it] == subStr[0])
//		{
//			while (it < sizeSubstr)
//			{
//				if (subStr[i] == lastBlock[it])
//				{
//					it++;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//	}
//}