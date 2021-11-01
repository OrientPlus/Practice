#include <stdlib.h>
#include <stdio.h>

#include "Source.h"

//найти заданную подстроку
//заменить подстроку

void ReplaceSubstring(char* ptrSM, char* subStr, int sizeSubstr, char* insertedStr, int sizeInsStr) //Ф-я замены подстроки
{
	char* modMass = NULL;
	modMass = (char*)malloc(1024 * sizeof(char)); //Массив хранящий текст с измененныим подстроками
	int i = 0, tmpJ=0;


	for (int j=0; j < 512; j++) //находит первое совпадение в тексте с подстрокой 
	{
		if (subStr[i] == ptrSM[j] && j==tmpJ++ && i<sizeSubstr-1)
		{
			tmpJ = j;
			i++;
		}
		if (i == sizeSubstr)
		{
			tmpJ = j - sizeSubstr; //записывает позицию найденного совпадения во временную переменную
			break;
		}
	}
	for (int it = 0; it < 512; it++)
	{
		if (it != tmpJ)
		{
			modMass[it] = ptrSM[it];
		}
		else {
			for (int j = it; j < sizeInsStr; j++)
			{
				modMass[j]= insertedStr[j]
			}
		}
	}


}