#include <stdlib.h>
#include <stdio.h>

#include "Source.h"

//����� �������� ���������
//�������� ���������

void ReplaceSubstring(char* ptrSM, char* subStr, int sizeSubstr, char* insertedStr, int sizeInsStr) //�-� ������ ���������
{
	char* modMass = NULL;
	modMass = (char*)malloc(1024 * sizeof(char)); //������ �������� ����� � ����������� �����������
	int i = 0, tmpJ=0;


	for (int j=0; j < 512; j++) //������� ������ ���������� � ������ � ���������� 
	{
		if (subStr[i] == ptrSM[j] && j==tmpJ++ && i<sizeSubstr-1)
		{
			tmpJ = j;
			i++;
		}
		if (i == sizeSubstr)
		{
			tmpJ = j - sizeSubstr; //���������� ������� ���������� ���������� �� ��������� ����������
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