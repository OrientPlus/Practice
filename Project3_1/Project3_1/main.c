#include <stdio.h>
#include <stdlib.h>

#include "aitoia.h"

typedef struct {
	int minLen, maxLen, Len;
	char* alph, * def_alph;
}option;

int translate(char* tmp)
{
	int conclusion = 0, i = 0;
	while (tmp[i] == '0' || tmp[i]=='1' || tmp[i]=='2')
	{
		conclusion = conclusion*10 + (tmp[i] - '0');
		i++;
	}
	return conclusion;
}

int main(int argc, char** argv)
{
	option op;
	char* user_input = NULL;
	int j = 0, i = 0;
	user_input = (char*)calloc(user_input, 50 * sizeof(char));
	for (int _i = 1; _i < argc; _i++)
	{
		j = 0;
		while (argv[_i][j] != '\0')
		{
			user_input[i] = argv[_i][j];
			j++; i++;
		}
	}
	user_input[i] = '\0';

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == 'm')
		{
			op.minLen = translate(&user_input[i+1]);
			printf("\n minimum =======> %d", op.minLen);
		}
		i++;
	}

	system("pause");
	return 0;
}