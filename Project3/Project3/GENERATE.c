#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "calculate.h"
#include "GENERATE.h"


int GEN(int argc, char** argv)
{
	srand(time(NULL));
	op.def_alph.flag = 0;
	op.def_alph.lucky_flag = 0;
	op.alph.flag = 0;
	op.Len = 0;
	op.maxLen = 0;
	op.minLen = 0;
	get_option(argc, &argv[0]);
	if (op.Len == 0)
	{
		if (op.minLen > op.maxLen)
		{
			printf("\n ERROR! The minimum password length cannot be greater than the maximum\n");
			system("pause");
			exit(1);
		}
		op.Len = op.minLen + rand() % (op.maxLen-10);
	}

	if (!op.def_alph.lucky_flag && op.def_alph.flag == 1)
		get_def_rand_string();
	else
		get_def_rand_string_withChance();
	free(password);
}

int get_option(int argc, char** argv)
{
	char* tmp = NULL;
	int j = 0, n = 0;
	for (int i = 1; i < argc; i += 2)
	{
		j = 0;
		n = 0;
		if (argv[i][1] == 'm')
		{
			
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;

				if (is_digits(argv[i+1][j]))
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-m' option!\n");
					system("pause");
					exit(10);
				}
			}

			op.minLen = my_atoi(&(argv[i + 1][0]), 10, n);
		}
		if (argv[i][1] == 'M')
		{
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;
				if (argv[i + 1][j] == '0' || argv[i + 1][j] == '1' || argv[i + 1][j] == '2' || argv[i + 1][j] == '3' || argv[i + 1][j] == '4' ||
					argv[i + 1][j] == '5' || argv[i + 1][j] == '6' || argv[i + 1][j] == '7' || argv[i + 1][j] == '8' || argv[i + 1][j] == '9')
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-M' option!\n");
					system("pause");
					exit(10);
				}
			}
			op.maxLen = my_atoi(&(argv[i + 1][0]), 10, n);
		}
		if (argv[i][1] == 'n')
		{
			while (1)
			{
				if (argv[i + 1][j] == '\0')
					break;

				if (argv[i + 1][j] == '0' || argv[i + 1][j] == '1' || argv[i + 1][j] == '2' || argv[i + 1][j] == '3' || argv[i + 1][j] == '4' ||
					argv[i + 1][j] == '5' || argv[i + 1][j] == '6' || argv[i + 1][j] == '7' || argv[i + 1][j] == '8' || argv[i + 1][j] == '9')
				{
					j++;
					n++;
				}
				else {
					printf("\n Incorrect arguments in '-n' option!\n");
					system("pause");
					exit(10);
				}
			}
			op.Len = my_atoi(&(argv[i + 1][0]), 10, n);
		}
		if (argv[i][1] == 'a')
		{
			op.alph.flag = 1;

			if (argv[i + 1][j] == '-')
			{
				break;
			}
			check_a_option(&argv[i+1][j]);
		}
		if (argv[i][1] == 'C')
		{
			op.def_alph.flag = 1;
			
			if (argv[i][j + 2] == '\0') 
			{
				printf("\nERROR! Option '-C' is empty!\n");
				system("pause");
				exit(10);
			}

			if (check_C_option(&argv[i][j + 2]))
				;
			else {
				printf("\nERROR! Incorrect arguments in '-C' option!\n");
				system("pause");
				exit(10);
			}
		}
	}


	//====================================Check_option==================================================================
	if ( (op.minLen!=0 && op.maxLen == 0) || (op.minLen == 0 && op.maxLen != 0) ) //«адана только одна опци€ из пары -m -M
	{
		printf("\nERROR! Incorrect option paire '-m' and '-M'!\n");
		system("pause");
		exit(1);
	} 
	if (op.minLen != 0 && op.maxLen != 0 && op.Len != 0) //«аданы одновременно -m -M -n
	{
		printf("\nERROR! Options '-m', '-M' and '-n' are not compatible!\n");
		system("pause");
		exit(1);
	}
	if (op.def_alph.flag != 0 && op.alph.flag != 0) //заданы одновременно опции -C и -a
	{
		printf("\nERROR! Options '-C' and '-a' are not compatible!\n");
		system("pause");
		exit(1);
	}
	return 1;
}

int check_C_option(char* argv) //корректно работает только дл€ двузначной веро€тности 
{
	int length = 0, j = 0;

	while (argv[j] != '\0')
	{
		if (argv[j] == 'a' )
		{
			op.def_alph.plenty_a = 1;


			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				for (int i = 0; i < 2; i++) //цикл рассчитан на двузначное число веро€тности
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-a' is incorrectly set\n");
						system("pause");
						exit(10);
					}
				}
				op.def_alph.lucky[0] = my_atoi(&argv[j - 2], 10, length);
			}
			j++;
		}
		else if (argv[j] == 'A' )
		{
			length = 0;
			op.def_alph.plenty_A = 1;

			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				for (int i = 0; i < 2; i++)
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-A' is incorrectly set\n");
						system("pause");
						exit(10);
					}
				}
				op.def_alph.lucky[1] = my_atoi(&argv[j - 2], 10, length);
			}
			j++;
		}
		else if (argv[j] == 'D' )
		{
			op.def_alph.plenty_D = 1;
			
			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				for (int i = 0; i < 2; i++)
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-D' is incorrectly set\n");
						system("pause");
						exit(10);
					}
				}
				op.def_alph.lucky[2] = my_atoi(&argv[j - 2], 10, length);
				j++;
			}
			j++;
		}
		else if (argv[j] == 'S')
		{
			op.def_alph.plenty_S = 1;
			
			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				for (int i = 0; i < 2; i++)
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-S' is incorrectly set\n");
						system("pause");
						exit(10);
					}
				}
				op.def_alph.lucky[3] = my_atoi(&argv[j - 2], 10, length);
			}
			j++;
		}
		else {
		printf("\nERROR! Incorrect arguments in the '-C' option\n");
		system("pause");
		exit(1);
		}
	}

	j = 0;
	for (int i = 0; i < 4; i++)
	{
		j = j + op.def_alph.lucky[i];
		if (j > 100)
		{
			printf("\nERROR! The total specified probability in the '-C' option exceeds 100%\n");
			system("pause");
			exit(1);
		}
	}
	return 1;
}

int check_a_option(char* argv) 
{
	char alph[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '#', '/', '+', '-', '=', '_', '*', '&', '%' };
	int j = 0, length = 0, it=0, flag_option =0;

	for (int i = 0; i < 72; i++)
	{
		if (argv[j] == '\0')
			break;

		length = 0;
		if (argv[j] == alph[i])
		{
			if (argv[j + 1] == '[')
			{
				flag_option = 1;
				j+=2;
				if (!is_digits(argv[j]))
				{
					printf("\nERROR! invalid character in option '-a'\n");
					system("pause");
					exit(1);
				}
				length++;
				if (argv[j + 1] != ']' && argv[j+2] == ']')
				{
					j++;
					if (!is_digits(argv[j]))
					{
						printf("\nERROR! invalid character in option '-a'\n");
						system("pause");
						exit(1);
					}
					length++;
				}
				op.alph.lucky[it] = my_atoi(&argv[j - (length-1)], 10, length);
			}
			else if (flag_option || j == 71)
			{
				printf("\nERROR! Invalid probability in option '-a'\n");
				system("pause");
				exit(1);
			}
			op.alph.alphabet[it] = argv[j - (length+1)];
			it++;
			if (length != 0)
				j = j + 2;
			else
				j++;
		}
	}
	op.alph.alphabet[it] = '\0';

	j = 0;
	for (int i = 0; i < it; i++)
	{
		j = j + op.alph.lucky[i];
		if (j > 100)
		{
			printf("\nERROR! The total specified probability in the '-a' option exceeds 100%\n");
			system("pause");
			exit(1);
		}
	}
	
	return 1;
}

int is_digits(char var)
{
	if (var == '0' || var == '1' || var == '2' || var == '3' || var == '4' ||
		var == '5' || var == '6' || var == '7' || var == '8' || var == '9')
		return 1;
	else
		return 0;
}

int is_a_alphabet(char var)
{
	char alphabet[] = { "abcdefghijklmnopqrstuvwxyz" };
	for (int i = 0; i < 26; i++)
	{
		if (var == alphabet[i])
			return 1;
		if (i == 25)
			return 0;
	}
}

void get_def_rand_string()
{
	char optA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
		opta[] = { "abcdefghijklmnopqrstuvwxyz" },
		optD[] = { "0123456789" },
		optS[] = { "@#/+-=_*&%" },
		userALPH[72] = {"\0"};
	password = (char*)malloc((op.Len+1) * sizeof(char));
	int length = 0, pos=0;

	if (op.def_alph.plenty_A)
		{
			if (userALPH != NULL)
				userALPH = strcat(userALPH, optA);
			else
			{
				userALPH = (char*)malloc(28 * sizeof(char));
				userALPH[27] = '\0';
				strcpy(userALPH, optA);
			}
		}
	if (op.def_alph.plenty_a)
		{
			if (userALPH != NULL)
				userALPH = strcat(userALPH, opta);
			else
			{
				userALPH = (char*)malloc(28 * sizeof(char));
				userALPH[27] = '\0';
				strcpy(userALPH, opta);
			}
		}		
	if (op.def_alph.plenty_D)
		{
			if (userALPH != NULL)
				userALPH = strcat(userALPH, optD);
			else
			{
				userALPH = (char*)malloc(11 * sizeof(char));
				userALPH[10] = '\0';
				strcpy(userALPH, optD);
			}
		}
	if (op.def_alph.plenty_S)
		{
			if (userALPH != NULL)
				userALPH = strcat(userALPH, optS);
			else
			{
				userALPH = (char*)malloc(11 * sizeof(char));
				userALPH[10] = '\0';
				strcpy(userALPH, optS);
			}
		}
	
	length = strlen(userALPH);
	for (int i = 0; i < op.Len; i++)
	{
		pos = rand() % (length - 1);
		password[i] = userALPH[pos];
	}
	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n", password);
}

void get_def_rand_string_withChance()
{
	char optA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
		opta[] = { "abcdefghijklmnopqrstuvwxyz" },
		optD[] = { "0123456789" },
		optS[] = { "@#/+-=_*&%" };
	int length = 0, pos = 0, chance = 0, distr[8] = {0}, up = 0;
	password = (char*)malloc((op.Len + 1) * sizeof(char));

	if (op.def_alph.lucky[0])
	{
		distr[0] = 0;
		distr[1] = op.def_alph.lucky[0];
		up = op.def_alph.lucky[0];
	}
	if (op.def_alph.lucky[1])
	{
		distr[2] = up;
		distr[3] = up + op.def_alph.lucky[1];
		up = distr[3];
	}
	if (op.def_alph.lucky[2])
	{
		distr[4] = up;
		distr[5] = up + op.def_alph.lucky[2];
		up = distr[5];
	}
	if (op.def_alph.lucky[3])
	{
		distr[6] = up;
		distr[7] = up + op.def_alph.lucky[3];
	}
	

	for (int i = 0; i < op.Len; i++)
	{
		chance = rand() % 100;
		if (chance >= distr[0] && chance < distr[1] && op.def_alph.lucky[0] != 0)
		{
			pos = rand() % 27;
			password[i] = opta[pos];
			continue;
		}
		if (chance >= distr[2] && chance < distr[3] && op.def_alph.lucky[1] != 0)
		{
			pos = rand() % 27;
			password[i] = optA[pos];
			continue;
		}
		if (chance >= distr[4] && chance < distr[5] && op.def_alph.lucky[2] != 0)
		{
			pos = rand() % 10;
			password[i] = optD[pos];
			continue;
		}
		if (chance >= distr[6] && chance < distr[7] && op.def_alph.lucky[3] != 0)
		{
			pos = rand() % 10;
			password[i] = optS[pos];
			continue;
		}
	}
	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n", password);
}
