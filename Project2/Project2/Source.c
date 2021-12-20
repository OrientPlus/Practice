#include <stdlib.h>
#include <stdio.h>

#include "Source.h"

//����� �������� ���������
//�������� ���������

void ReplaceSubstring(char* ptrSM, char* subStr, int sizeSubstr, char* insertedStr, int sizeInsStr) //�-� ������ ���������
{
	static int seek_pos = 0;
	FILE* out;
	fopen_s(&out, "output.txt", "a");
	fseek(out, seek_pos, SEEK_SET);

	char* modMass = NULL;
	modMass = (char*)malloc(1024 * sizeof(char)); //������ �������� ����� � ����������� �����������
	int *massIndex = (int*)malloc(512*sizeof(int)),
		_i = 0,
		sizeIndex = 0,
		it_mod_mass = 0;
	

	for (int i = 0; i <= 512; i++) //���� ���������� �� ������� �������. ���� ������� ��������� ��������� ���������, ��������� ������ ������� ��-�� � ���. ������
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
	sizeIndex = _i+1; //���������� �������� ������ �������.
	massIndex = (int*)realloc(massIndex, sizeIndex * sizeof(int));
	_i = 0;

	//�������� ��������� � �������� ������
	//����� � ����� ������ ������ ���� �� �������� ������ ������, ����� ������, ����� ������ �������� ������
	//������� � �������� (j+����� ���������  ������ ab->abcd => +2) ���� �� �������� ��������� ������
	// ����� ���������������� ������ � ����, ���������� ������� �������.
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