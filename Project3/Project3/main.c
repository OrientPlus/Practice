#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int minLen, maxLen, Len;
	char *alph, *def_alph;
}option;



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
			op.minLen = my_atoi(&user_input[i], 10, 1);
			printf("\n minimum =======> %d", op.minLen);
		}
	}
	
	system("pause");
	return 0;
}