#include <stdlib.h>
#include <stdio.h>

#include "Source.h"

//найти заданную подстроку
//заменить подстроку

void ReplaceSubstring(char* ptrSM, char* subStr, int sizeSubstr, char* insertedStr, int sizeInsStr) //Ф-я замены подстроки
{
	static int seek_pos = 0;
	FILE* out;
	fopen_s(&out, "output.txt", "a");
	fseek(out, seek_pos, SEEK_SET);

	char* modMass = NULL;
	modMass = (char*)malloc(1024 * sizeof(char)); //Массив хранящий текст с измененными подстроками
	int *massIndex = (int*)malloc(512*sizeof(int)),
		_i = 0,
		sizeIndex = 0,
		it_mod_mass = 0;
	

	for (int i = 0; i <= 512; i++) //Ищет совпадения по первому символу. Если искомая подстрока полностью совпадает, сохраняет индекс первого эл-та в исх. строке
	{
		if (subStr[0] == ptrSM[i])
		{
			if (comparison_of_substrings(0, i, &subStr[0], &ptrSM[0], sizeSubstr) == 1)
			{
				massIndex[_i] = i;
				_i++;
			}	
		}
	}
	sizeIndex = _i+1; //переменная хранящая размер массива.
	massIndex = (int*)realloc(massIndex, sizeIndex * sizeof(int));
	_i = 0;

	//заменить подстроку в исходном тексте
	//пишем в новый массив строку пока не встретим первую замену, пишем замену, пишем дальше исходную строку
	//начиная с элемента (j+длина подстроки  тоесть ab->abcd => +2) пока не встретим очередную замену
	// пишем модифицированную строку в файл, запоминаем позицию курсора.
	for (int i = 0; i<511; i++)
	{
		if (i != massIndex[_i])
		{
			modMass[it_mod_mass] = ptrSM[i];
			fprintf(out, "%c", modMass[it_mod_mass]);
			it_mod_mass++;
		}
		else
		{
			for (int j = 0; j < sizeInsStr; j++)
			{
				modMass[it_mod_mass] = insertedStr[j];
				fprintf(out, "%c", modMass[it_mod_mass]);
				it_mod_mass++;
			}
			_i++;
		}
	}
	seek_pos = seek_pos + 512;
	fclose(out);
}

int comparison_of_substrings(int i, int j, char* subStr, char* sourceStr, int sizeSubstr)
{
	int flag = 0;
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