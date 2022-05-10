#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "calculate.h"
#include "GENERATE.h"


/*
	=============================Реализованные_проверки=============================
		1. Опция -С
	1.1 Повторение переданных алфавитов
	1.2 Суммарная вероятность алфавита для пароля (==100)
	1.3 Корректность передавамого значения вероятности алфавита
	1.4 Корректность подопции алфавитов внутри опции -С
	1.5 Проверка на пустоту опции
	1.6 Заданная вероятность алфавитов <100

		2. Общие проверки
	2.1 Совместимость опций -m,-M и -n
	2.2 Совместимость опций -m и -n
	2.3 Совместимость опций -M и -n
	2.4 Совместимость опций -C и -a
	2.5 Заданного алфавита (не задана ни одна из опций алфавита)
	2.7 Заданная длина пароля (не задана ни одна из опций длины пароля)
	2.6 Проверка длины пароля (10 <= length <= 45)

		3. Опция -a
	3.1 Повторение переданных символов алфавита
	3.2 Суммарная вероятность алфавита для пароля (==100)
	3.3 Корректность передавамого значения вероятности символа
	3.4 Корректность передаваемого символа (допустимый символ)
	3.5 Проверка на пустоту опции
	3.6 Заданная вероятность символов <100

	================================================================================
*/

int GEN(int argc, char** argv)
{
	printf("\nWARNING! If you specify the '-m' and '-M' options, the maximum length is 100, the minimum is 10!\n");
	if (argc < 3)
	{
		printf("\nERROR! There are not enough parameters to generate a password!\n");
		system("pause");
		exit(1);
	}
	printf("\nPassed arguments:\n");
	for (int i = 1; i < argc; i++)
	{
		printf("%d -> ", i);
		printf("%s\n", argv[i]);
	}
	init_options();

	srand(time(NULL));
	
	get_option(argc, &argv[0]);
	if (op.Len == 0)
	{
		if (op.minLen > op.maxLen)
		{
			printf("\n ERROR! The minimum password length cannot be greater than the maximum\n");
			system("pause");
			exit(1);
		}
		op.Len = op.minLen + rand() % (op.maxLen - op.minLen);
	}
	printf("\nGenerated length: %d\n", op.Len);

	if (op.def_alph.flag == 1 && op.def_alph.lucky_flag == 0)
		get_def_rand_string();
	else if (op.def_alph.flag == 1 && op.def_alph.lucky_flag != 0)
		get_def_rand_string_withChance();
	else if (op.alph.flag == 1 && op.alph.lucky_flag == 0)
		get_alph_rand_string();
	else if (op.alph.flag == 1 && op.alph.lucky_flag == 1)
		get_alph_rand_string_withChance();
	free(password);
}

void init_options()
{
	op.def_alph.flag = false;
	op.def_alph.lucky_flag = false;
	op.def_alph.a.flag = false;
	op.def_alph.a.lucky = 0;
	op.def_alph.A.flag = false;
	op.def_alph.A.lucky = 0;
	op.def_alph.D.flag = false;
	op.def_alph.D.lucky = 0;
	op.def_alph.S.flag = false;
	op.def_alph.S.lucky = 0;
	
	op.alph.flag = false;
	op.alph.lucky_flag = 0;

	op.Len = 0;
	op.maxLen = 0;
	op.minLen = 0;
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
			continue;
		}
		else if (argv[i][1] == 'M')
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
			continue;
		}
		else if (argv[i][1] == 'n')
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
			continue;
		}
		else if (argv[i][1] == 'a')
		{
			op.alph.flag = true;
			if ( i+1<argc && argv[i+1][j] != NULL)
				check_a_option(&argv[i+1][j]);
			else {
				printf("\nERROR! Empty option '-a'\n");
				system("pause");
				exit(1);
			}
			continue;
		}
		else if (argv[i][1] == 'C')
		{
			op.def_alph.flag = true;
			
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
			i--;
			continue;
		}
		else {
			printf("\nERROR! Invalid option!\n");
			system("pause");
			exit(1);
		}
	}

	//====================================Сheck_the_set_of_options======================================
	if ( (op.minLen != 0 && op.maxLen == 0) || (op.minLen == 0 && op.maxLen != 0) ) //Задана только одна опция из пары -m -M
	{
		printf("\nERROR! Incorrect option paire '-m' and '-M'!\n");
		system("pause");
		exit(1);
	} 
	if (op.minLen != 0 && op.maxLen != 0 && op.Len != 0) //Заданы одновременно -m -M -n
	{
		printf("\nERROR! Options '-m', '-M' and '-n' are not compatible!\n");
		system("pause");
		exit(1);
	}
	if ((op.minLen != 0 || op.maxLen != 0) && op.Len != 0)
	{
		printf("\nERROR! The '-n' option is not compatible with the '-m' and '-M' options\n");
		system("pause");
		exit(1);
	}
	if (op.alph.flag == true && op.def_alph.flag == true) //заданы одновременно опции -C и -a
	{
		printf("\nERROR! Options '-C' and '-a' are not compatible!\n");
		system("pause");
		exit(1);
	}
	if (op.alph.flag == false && op.def_alph.flag == false)
	{
		printf("\nERROR! The alphabet/character set for the password is not set!\n");
		system("pause");
		exit(1);
	}
	if ((op.minLen < 10 && op.minLen != 0) || (op.maxLen > 100 && op.maxLen != 0))
	{
		printf("\nERROR! Incorrect password length range!\n");
		system("pause");
		exit(1);
	}

	return 1;
}

int check_C_option(char* argv) 
{
	int length = 0, j = 0, indx;

	while (argv[j] != '\0')
	{
		indx = 2;
		if (argv[j] == 'a' )
		{
			if (op.def_alph.a.flag)
			{
				printf("\nERROR! Re-set option '-a'\n");
				system("pause");
				exit(10);
			}
			else
				op.def_alph.a.flag = true;

			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				if (argv[j + 1] == ']')
					indx = 1;

				for (int i = 0; i < indx; i++) //цикл рассчитан на двузначное число вероятности
				{
					if (is_digits(argv[j]))
					{
						length++;
						j++;
					}
					else {
						printf("\nError in option -C. The probability of occurrence of the alphabet characters '-a' is incorrectly set\n");
						system("pause");
						exit(1);
					}
				}
				op.def_alph.a.lucky = my_atoi(&argv[j - indx], 10, length);
			}
			j++;
		}
		else if (argv[j] == 'A' )
		{
			if (op.def_alph.A.flag)
			{
				printf("\nERROR! Re-set option '-A'\n");
				system("pause");
				exit(10);
			}
			else
				op.def_alph.A.flag = true;

			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;
				
				if (argv[j + 1] == ']')
					indx = 1;

				for (int i = 0; i < indx; i++)
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
				op.def_alph.A.lucky = my_atoi(&argv[j - indx], 10, length);
			}
			j++;
		}
		else if (argv[j] == 'D' )
		{
			if (op.def_alph.D.flag)
			{
				printf("\nERROR! Re-set option '-D'\n");
				system("pause");
				exit(1);
			}
			else
				op.def_alph.D.flag = true;
			
			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;

				if (argv[j + 1] == ']')
					indx = 1;

				for (int i = 0; i < indx; i++)
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
				op.def_alph.D.lucky = my_atoi(&argv[j - indx], 10, length);
			}
			j++;
		}
		else if (argv[j] == 'S')
		{
			if (op.def_alph.S.flag)
			{
				printf("\nERROR! Re-set option '-S'\n");
				system("pause");
				exit(1);
			}
			else
				op.def_alph.S.flag = true;
			
			length = 0;
			if (argv[j + 1] == '[')
			{
				op.def_alph.lucky_flag++;
				j += 2;

				if (argv[j + 1] == ']')
					indx = 1;

				for (int i = 0; i < indx; i++)
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
				op.def_alph.S.lucky = my_atoi(&argv[j - indx], 10, length);
			}
			j++;
		}
		else {
		printf("\nERROR! Incorrect arguments in the '-C' option\n");
		system("pause");
		exit(1);
		}
	}

	check_probability();
	return 1;
}

int check_a_option(char* argv) 
{
	char alph[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#/+-=_*&%"};
	int j = 0, length = 0, it=0, flag_option =0, lenARG=0;
	char ch1, ch2;
	while (argv[j] != '\0')
	{
		lenARG++;
		j++;
	}
	j = 0;
	for (int i = 0; i < lenARG; i++)
	{
		for (int _i = 0; _i < 72; _i++)
		{
			length = 0;
			if (argv[i] == alph[_i])
			{
				if (argv[i + 1] == '[')
				{
					op.alph.lucky_flag++;
					
					if (!is_digits(argv[i+2]))
					{
						printf("\nERROR! invalid character in option '-a'\n");
						system("pause");
						exit(1);
					}
					length++;
					if (argv[i + 4] == ']')
					{
						
						if (!is_digits(argv[i+3]))
						{
							printf("\nERROR! invalid character in option '-a'\n");
							system("pause");
							exit(1);
						}
						length++;
					}
					op.alph.lucky[it] = my_atoi(&argv[i+2], 10, length);
				}
				op.alph.alphabet[it] = alph[_i];
				it++;
				if (length != 0)
					i = i + length + 2;
				break;
			}
			else if (_i == 71)
			{
				printf("\nERROR! Invalid probability in option '-a'\n");
				system("pause");
				exit(1);
			}

		}
	}
	op.alph.alphabet[it] = '\0';
	length = it + 1;

	j = 0;
	for (int i = 0; i < length; i++)
	{
		j = j + op.alph.lucky[i];
		if (j > 100)
		{
			printf("\nERROR! The total specified probability in the '-a' option exceeds 100%%\nNow tottal probability: %d\n%%", j);
			system("pause");
			exit(1);
		}
	}
	if (op.alph.lucky_flag == length - 1 && j < 100)
	{
		printf("\nERROR! If you set the probability of all characters manually, the total probability should be 100%%\nNow total probability: %d\n%%", j);
		system("pause");
		exit(1);
	}
	

	
	j = 0;
	for (int i = 0; i < 73; i++)
	{
		j = 0;
		for (int _i = 0; _i < length; _i++)
		{
			if (alph[i] == argv[_i])
				j++;
			if (j > 1)
			{
				printf("\nERROR! Resetting a character '%c' in the '-a' option\n", argv[_i]);
				system("pause");
				exit(1);
			}
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
		userALPH[73] = {'\0'};
	password = (char*)malloc((op.Len+1) * sizeof(char));
	int length = 1, pos=0;

	if (op.def_alph.A.flag)
	{
		length += strlen(optA);
		strcat_s(userALPH, length, optA);
	}
	if (op.def_alph.a.flag)
	{
		length += strlen(opta);
		strcat_s(userALPH, length, opta);
	}		
	if (op.def_alph.D.flag)
	{
		length += strlen(optD);
		strcat_s(userALPH, length, optD);
	}
	if (op.def_alph.S.flag)
	{
		length += strlen(optS);
		strcat_s(userALPH, length, optS);
	}
	
	for (int i = 0; i < op.Len; i++)
	{
		pos = rand() % (length - 1);
		password[i] = userALPH[pos];
	}
	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n=====================================================\n", password);
}

void get_def_rand_string_withChance()
{
	char optA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
		 opta[] = { "abcdefghijklmnopqrstuvwxyz" },
		 optD[] = { "0123456789" },
		 optS[] = { "@#/+-=_*&%" };
	int length = 0, pos = 0, chance = 0, distr[8] = { 0 }, up = 0;
	password = (char*)malloc((op.Len + 1) * sizeof(char));


	if (op.def_alph.a.flag)
	{
		distr[0] = 0;
		distr[1] = op.def_alph.a.lucky;
		up = op.def_alph.a.lucky;
	}
	if (op.def_alph.A.flag)
	{
		distr[2] = up;
		distr[3] = up + op.def_alph.A.lucky;
		up = distr[3];
	}
	if (op.def_alph.D.flag)
	{
		distr[4] = up;
		distr[5] = up + op.def_alph.D.lucky;
		up = distr[5];
	}
	if (op.def_alph.S.flag)
	{
		distr[6] = up;
		distr[7] = up + op.def_alph.S.lucky;
	}

	for (int i = 0; i < op.Len; i++)
	{
		chance = rand() % 100;
		if (chance >= distr[0] && chance < distr[1] && op.def_alph.a.lucky > 0)
		{
			pos = rand() % 26;
			password[i] = opta[pos];
			continue;
		}
		if (chance >= distr[2] && chance < distr[3] && op.def_alph.A.lucky > 0)
		{
			pos = rand() % 26;
			password[i] = optA[pos];
			continue;
		}
		if (chance >= distr[4] && chance < distr[5] && op.def_alph.D.lucky > 0)
		{
			pos = rand() % 10;
			password[i] = optD[pos];
			continue;
		}
		if (chance >= distr[6] && chance < distr[7] && op.def_alph.S.lucky > 0)
		{
			pos = rand() % 10;
			password[i] = optS[pos];
			continue;
		}
	}
	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n=====================================================\n", password);
}

void get_alph_rand_string()
{
	password = (char*)malloc((op.Len + 1) * sizeof(char));
	int length = 0, pos = 0, it=0;
	while (op.alph.alphabet[it] != '\0')
	{
		length++;
		it++;
	}
	length++;
	for (int i = 0; i < op.Len; i++)
	{
		pos = rand() % (length - 1);
		password[i] = op.alph.alphabet[pos];
	}
	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n=====================================================\n", password);
}

void get_alph_rand_string_withChance()
{
	password = (char*)malloc((op.Len + 1) * sizeof(char));
	int length = 0, pos = 0, it = 0, chance =0, overall_prob=0, NULLprob=1, tmp=0;
	char* userALPH = (char*)malloc(101 * sizeof(char));

	while (op.alph.alphabet[it] != '\0')
	{
		overall_prob += op.alph.lucky[it];
		if (op.alph.lucky[it] == 0)
			NULLprob++;
		length++;
		it++;
	}
	it = 0;
	overall_prob = (100 - overall_prob) / (NULLprob);
	
	
	for (int i = 0; i < length; i++)
	{
		if (op.alph.lucky[i] == 0)
			op.alph.lucky[i] = overall_prob;
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < op.alph.lucky[it]; j++)
		{
			userALPH[tmp+j] = op.alph.alphabet[i];
		}
		tmp = tmp + op.alph.lucky[it];
		it++;
	}
	if (tmp < 100) //Выравнивание алфавита. Недостающие позиции забиваются случайными символами из имеющегося алфавита
	{
		printf("\nWARNING! It is impossible to evenly divide the probabilities between all the characters of the password alphabet. \n\
The remaining probability (%d%%) will be randomly distributed.\n", 100-tmp);
		for (int i = tmp; i < 100; i++)
		{
			pos = rand() % tmp;
			userALPH[i] = userALPH[pos];
		}
	}
	userALPH[100] = '\0';

	for (int i = 0; i < op.Len; i++)
	{
		pos = rand() % 100;
		password[i] = userALPH[pos];
	}

	password[op.Len] = '\0';
	printf("\nGENERATED PASSWORD: %s\n=====================================================\n", password);
}

void check_probability()
{
	int prob = 0, n_flags=0, zero_prob=0;
	
	if (op.def_alph.a.flag == true)
	{
		prob = prob + op.def_alph.a.lucky;
		n_flags++;
		if (op.def_alph.a.lucky == 0)
			zero_prob++;
	}
	if (op.def_alph.A.flag == true)
	{
		prob = prob + op.def_alph.A.lucky;
		n_flags++;
		if (op.def_alph.A.lucky == 0)
			zero_prob++;
	}
	if (op.def_alph.D.flag == true)
	{
		prob = prob + op.def_alph.D.lucky;
		n_flags++;
		if (op.def_alph.D.lucky == 0)
			zero_prob++;
	}
	if (op.def_alph.S.flag == true)
	{
		prob = prob + op.def_alph.S.lucky;
		n_flags++;
		if (op.def_alph.S.lucky == 0)
			zero_prob++;
	}

	if (prob > 100)
	{
		printf("\nERROR! The total specified probability in the '-C' option exceeds 100%%\nNow total probability: %d%%\n", prob);
		system("pause");
		exit(1);
	}
	if (prob < 100 && zero_prob == 0)
	{
		printf("\nERROR! If the probability is set manually for all sets. Its sum should be equal to 100%%\nNow total probability: %d%%\n", prob);
		system("pause");
		exit(1);
	}

	/* Распределение вероятности между множествами */
	if (zero_prob > 0)
		algnment_prob(prob, zero_prob);
	
	
}

void algnment_prob(int prob, int zero_prob)
{
	int alg_var, //распределенная вероятность
		tmpv = 0; //остаток вероятности, если невозможно разделить нацело между алфавитами

	if (zero_prob > 1)
	{
		alg_var = (100 - prob) / zero_prob;
		tmpv = 100 - (alg_var * zero_prob + prob);
		
		
		/* Задаем вероятность, если изначально она = 0 */
		if (op.def_alph.a.flag == true && op.def_alph.a.lucky == 0)
			op.def_alph.a.lucky += alg_var;
		if (op.def_alph.A.flag == true && op.def_alph.A.lucky == 0)
			op.def_alph.A.lucky = alg_var;
		if (op.def_alph.D.flag == true && op.def_alph.D.lucky == 0)
			op.def_alph.D.lucky = alg_var;
		if (op.def_alph.S.flag == true && op.def_alph.S.lucky == 0)
			op.def_alph.S.lucky += alg_var;
		
		/* Добиваем общую вероятность до 100%, если есть остаток */
		if (tmpv != 0)
		{
			printf("\nWARNING! It is impossible to evenly divide the probabilities between all the characters of the password alphabet. \n\
The remaining probability (%d%%) will be divided into special characters or small Latin characters.\n", tmpv);
			if (op.def_alph.a.flag == true)
				op.def_alph.a.lucky += tmpv;
			else if (op.def_alph.S.flag == true)
				op.def_alph.S.lucky += tmpv;
		}
	}
	else
	{
		alg_var = 100 - prob;

		/* Задаем вероятность, если изначально она = 0 */
		if (op.def_alph.a.flag == true && op.def_alph.a.lucky == 0)
			op.def_alph.a.lucky += alg_var;
		if (op.def_alph.A.flag == true && op.def_alph.A.lucky == 0)
			op.def_alph.A.lucky = alg_var;
		if (op.def_alph.D.flag == true && op.def_alph.D.lucky == 0)
			op.def_alph.D.lucky = alg_var;
		if (op.def_alph.S.flag == true && op.def_alph.S.lucky == 0)
			op.def_alph.S.lucky += alg_var;
	}
}