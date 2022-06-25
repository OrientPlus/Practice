#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bigNum.h"
#include "calculate.h"

#define BLOCK_SIZE 4

//==============___1___====================
//получить число из 16-ричной строки
//реализовать деление
//переписать структуру большого числа
//переписать/написать новый вывод числа
//
//=============___2___====================
// получить число из 16-ричной строки
// переписать структуру большого числа 
// переписать выделение памяти
// переписать инициализацию
// переписать сложение
// переписать вычитание
// переписать умножение
// реализовать деление
// переписать вывод
//


supportMASS* num1 = &a, * num2 = &b, *res = &c;


int bigNum(int argc, char** argv)
{	
	bool hexFlag = false;
	char** numbers = (char**)malloc(3 * sizeof(char*));
	numbers[0] = NULL;
	numbers[2] = NULL;
	numbers[1] = (char*)malloc(2 * sizeof(char));

	get_numbers_from_console(&numbers[0], argc, &argv[0]);

	check_numbers(3, &numbers[0]);
	initNumbers(&numbers[0]);
	getNumbers(3, &numbers[0], hexFlag);
	printf("\n\nFirst number: ");
	printBigNum_dec(num1);
	printf("\nSecond number: ");
	printBigNum_dec(num2);

	operation_definition(numbers[1][0]);

	printf("\nResult number: ");
	printBigNum_dec(res);
	free(num1->zero);
	free(num2->zero);
	free(result.val);
}

void check_numbers(int argc, char** argv)
{
	char alph[] = { "-0123456789" };
	char opr[] = { "+-*" },
		ch;
	int it = 0, sFlag = 0;
	
	
	while (ch = argv[0][it])
	{
		if (ch == '\0')
			break;
		for (int i = 0; i < 11; i++)
		{
			if (ch == alph[i])
			{
				if (ch == '-' && sFlag == 1)
				{
					printf("\nERROR! Invalid first number\n");
					system("pause");
					exit(1);
				}
				else if (ch == '-')
					sFlag = 1;
				break;
			}
			else if (i == 10)
			{
				printf("\nERROR! Invalid first number\n");
				system("pause");
				exit(1);
			}
		}
		it++;
	}
	sFlag = 0;
	it = 0;
	while (ch = argv[2][it])
	{
		if (ch == '\0')
			break;
		for (int i = 0; i < 11; i++)
		{
			if (ch == alph[i])
			{
				if (ch == '-' && sFlag == 1)
				{
					printf("\nERROR! Invalid second number\n");
					system("pause");
					exit(1);
				}
				else if (ch == '-')
					sFlag = 1;
				break;
			}
			else if (i == 10)
			{
				printf("\nERROR! Invalid second number\n");
				system("pause");
				exit(1);
			}
		}
		it++;
	}
	ch = argv[1][0];
	for (int i = 0; i < 3; i++)
	{
		if (ch == opr[i])
			break;
		else if (i == 2)
		{
			printf("\nERROR! Invalid operation!\n");
			system("pause");
			exit(1);
		}
	}
}

void initNumbers(char** argv)
{
	int tmp=0;
	num1->sign = false;
	num1->zero = NULL;
	num2->sign = false;
	num2->zero = NULL;
	result.sign = false;
	
	num1->length = strlen(argv[0]);
	if (argv[0][0] == '-')
		num1->length--;
	num1->length /= BLOCK_SIZE;
	tmp = strlen(argv[0]) - BLOCK_SIZE * num1->length;
	if (tmp > 0)
	{
		if (argv[0][0] == '-' && tmp > 1)
			num1->length++;
		else if (argv[0][0] != 0 && tmp > 0)
			num1->length++;
	}
	
	num2->length = strlen(argv[2]);
	if (argv[2][0] == '-')
		num2->length--;
	num2->length /= BLOCK_SIZE;
	tmp = strlen(argv[2]) - BLOCK_SIZE * num2->length;
	if (tmp > 0)
	{
		if (argv[2][0] == '-' && tmp > 1)
			num2->length++;
		else if (argv[2][0] != 0 && tmp > 0)
			num2->length++;
	}

	
	num1->val = (unsigned*)malloc(num1->length * sizeof(unsigned));
	num1->zero = (int*)malloc(num1->length * sizeof(int));
	num2->val = (unsigned*)malloc(num2->length * sizeof(unsigned));
	num2->zero = (int*)malloc(num2->length * sizeof(int));

	
	for (int i = 0; i < num1->length; i++)
	{
		num1->val[i] = 0;
		num1->zero[i] = 0;
	}
	for (int i = 0; i < num2->length; i++)
	{
		num2->val[i] = 0;
		num2->zero[i] = 0;
	}

	//------------------Initializing the result-----------------//
	if (num1->length > num2->length)
		res->length = num1->length + 1;
	else
		result.length = num2->length + 1;
	res->val = (unsigned*)malloc(res->length * sizeof(unsigned));
	res->zero = (int*)malloc(res->length * sizeof(int));

	for (int i = 0; i < res->length; i++)
	{
		res->val[i] = 0;
		res->zero[i] = 0;
	}
	
	result.length = 10;
	result.val = (char**)malloc(result.length * sizeof(char*));
	for (int i = 0; i < result.length; i++)
		result.val[i] = (char*)malloc(8 * sizeof(char));
}

void getNumbers(int argc, char** argv)
{
	int it = 0,
		strLen, n, flag = 0, hexF =0;
	unsigned tmp = 0;
	
	if (argv[0][0] == '-')
	{
		argv[0][0] = '0';
		num1->sign = true;
	}
	if (argv[2][0] == '-')
	{
		argv[2][0] = '0';
		num2->sign = true;
	}

	it = num1->length - 1;
	strLen = strlen(argv[0]);
	for (int i = 0; i < strLen / BLOCK_SIZE + 1; i++)
	{
		n = BLOCK_SIZE * (i + 1);
		for (int j = BLOCK_SIZE; j > 0; j--)
		{
			if (strLen - n >= 0)
				tmp = tmp * 10 + argv[0][strLen - n] - '0';
			n--;
		}
		num1->val[it] = tmp;
		tmp = 0;
		it--;
	}
	word_alignment(num1);

	tmp = 0;
	it = num2->length-1;
	strLen = strlen(argv[2]);
	for (int i = 0; i < strLen / BLOCK_SIZE + 1; i++)
	{
		n = BLOCK_SIZE * (i + 1);
		for (int j = BLOCK_SIZE; j > 0; j--)
		{
			if (strLen - n >= 0)
				tmp = tmp * 10 + argv[2][strLen - n] - '0';
			n--;
		}
		num2->val[it] = tmp;
		tmp = 0;
		it--;
	}
	word_alignment(num2);
}

void printBigNum_dec(supportMASS *num)
{
	if (num->sign)
		printf("-");
	for (int i = 0; i < num->length; i++)
	{
		if (i > 0)
		{
			while (num->zero[i] > 0) {
				num->zero[i]--;
				printf("%d", 0);
			}
		}
		if (num->val[i] != 0)
			printf("%u", num->val[i]);
	}
}

void add(bool sign)
{
	unsigned x = 0, y = 0, divide = 0,
		X = 0, Y = 0;
	int n1_it = num1->length - 1, n2_it = num2->length - 1, flag = 0;
	int** tmpMass = NULL;


	tmpMass = (int**)malloc(res->length * sizeof(int*));
	for (int i = 0; i < res->length; i++)
		tmpMass[i] = (int*)malloc(BLOCK_SIZE * sizeof(int));
	for (int i = 0; i < res->length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
			tmpMass[i][j] = 0;
	}

	for (int i = 0; i < res->length; i++)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		if (n1_it >=0)
			X = num1->val[n1_it];
		if (n2_it >=0)
			Y = num2->val[n2_it];
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			x = X % 10;
			y = Y % 10;
			if ((x == 0 && X == 0) && (y == 0 && Y == 0))
			{
				if (divide == 1)
				{
					tmpMass[(res->length - 1) - i][(BLOCK_SIZE - 1) - j] = divide;
				}
				break;
			}
			if ((x == 0 && X == 0) || (y == 0 && Y == 0))
			{
				if (x == 0)
					x = y;
				x += divide;
				if (x >= 10)
				{
					divide = 1;
					x = x % 10;
				}
				else
					divide = 0;
				tmpMass[(res->length - 1) - i][(BLOCK_SIZE-1) - j] = x;
				X = X / 10;
				Y = Y / 10;
				continue;
			}
			x += y + divide;
			if (x >= 10)
			{
				divide = 1;
				x = x % 10;
			}
			else
				divide = 0;
			tmpMass[(res->length - 1) - i][(BLOCK_SIZE-1) - j] = x;
			X = X / 10;
			Y = Y / 10;
		}

		n1_it--;
		n2_it--;
	}


	printf("\n\n");
	for (int i = 0; i < res->length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (tmpMass[i][j] == 0 && flag == 0)
				continue;
			else
			{
				res->val[i] = res->val[i] * 10 + tmpMass[i][j];
				flag = 1;
			}
		}
	}
	realloc_result();
	word_alignment(res);
	if (sign)
		res->sign = true;
}

void subtract(bool sign, supportMASS *n1, supportMASS *n2)
{
	int x, y, X, Y;
	int div = 0, nine_count = -2, it_I = 0, zero_count = 0;
	int n1_it = n1->length - 1, n2_it = n2->length - 1, flag = 0;
	int** tmpMass = NULL;

	tmpMass = (int**)malloc(res->length * sizeof(int*));
	for (int i = 0; i < res->length; i++)
		tmpMass[i] = (int*)malloc(BLOCK_SIZE * sizeof(int));
	for (int i = 0; i < res->length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
			tmpMass[i][j] = 0;
	}

	for (int i = 0; i < res->length; i++)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		if (n1_it >= 0)
			X = n1->val[n1_it];
		if (n2_it >= 0)
			Y = n2->val[n2_it];
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			x = X % 10;
			y = Y % 10;
			if (nine_count >= 0 && x == 0)
			{
				x = 9;
				nine_count--;
			}
			else if (div == 1 || nine_count == -1)
			{
				x--;
				nine_count--;
			}
			if ((x == 0 && X == 0) && (y == 0 && Y == 0))
				break;
			if (x < y)
			{
				unsigned t = X;
				t = X / 10;
				if (t % 10 == 0)
				{
					nine_count = get_nineCount(X, j);
					x = 10 + x;
					x -= y;
					tmpMass[(res->length - 1) - i][(BLOCK_SIZE-1) - j] = x;
					X = X / 10;
					Y = Y / 10;
					div = 0;
					continue;
				}
				x = 10 + x;
				div = 1;
			}
			else
				div = 0;
			x -= y;
			tmpMass[(res->length - 1) - i][(BLOCK_SIZE-1) - j] = x;
			X = X / 10;
			Y = Y / 10;
		}
		n2_it--;
		n1_it--;
	}

	printf("\n\n");
	for (int i = 0; i < res->length; i++) //Формируем слово большого числа из полученных значений разрядов
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (tmpMass[i][j] == 0 && flag == 0)
				continue;
			else
			{
				res->val[i] = res->val[i] * 10 + tmpMass[i][j];
				flag = 1;
			}
		}
	}
	realloc_result();
	word_alignment(res);
	if (sign)
		res->sign = true;
}

void multiply(bool sign, supportMASS *n1, supportMASS *n2)
{
	unsigned
		* firstStepNumber = (unsigned*)malloc((n2->length + 1) * sizeof(unsigned)),
		* divideFS = (unsigned*)malloc(BLOCK_SIZE * sizeof(unsigned)),
		** secondStepMass = (unsigned**)malloc(n1->length * sizeof(unsigned*));
	for (int i = 0; i < n1->length; i++)
		secondStepMass[i] = (unsigned*)malloc((n2->length + 1) * sizeof(unsigned));

	int oldLen = 0;
	res->val = (unsigned*)realloc(res->val, (n1->length + n2->length) * sizeof(unsigned));
	res->zero = (unsigned*)realloc(res->zero, (n1->length + n2->length) * sizeof(unsigned));
	for (int i = 0; i < n1->length + n2->length; i++)
	{
		res->val[i] = 0;
		res->zero[i] = 0;
	}
	res->length = n1->length + n2->length;
	unsigned divide = 0;
	int x, y;
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = n1->length - 1; i >= 0; i--)
	{
		x = n1->val[i];
		for (int j = n2->length; j > 0; j--)
		{
			y = n2->val[j - 1];
			firstStepNumber[j] = x * y;

			//===========разделяем на блоки по BLOCK_SIZE================================================================
			if (firstStepNumber[j] > 9999)                    //Если число больше блока, то берем последние BLOCK_SIZE цифры, остальное в остаток 
			{
				divideFS[j] = firstStepNumber[j] / 10000;
				firstStepNumber[j] %= 10000;
			}
			else
				divideFS[j] = 0;
			//printf("\nDIVIDE = %u, NUMB = %u\n", divideFS[j], firstStepNumber[j]);
			//================Если не нулевая итерация, прибавляем остаток из предыдущего перемножения===================
			if (j != num2->length)
				firstStepNumber[j] = firstStepNumber[j] + divideFS[j + 1];
			if (firstStepNumber[j] > 9999)          //Если оно больше блка, то переносим 1 в остаток, и берем посследние 4 цифры
			{
				divideFS[j]++;
				firstStepNumber[j] %= 10000;
			}
		}

		//===================цикл записи полученного числа в массив второго этапа========================================
		for (int j = 0; j < n2->length + 1; j++)
		{
			if (j == 0)
				secondStepMass[i][j] = divideFS[j + 1];
			else
				secondStepMass[i][j] = firstStepNumber[j];
			//printf("\nSEC MASS[%d][%d] = %u\n", i, j, secondStepMass[i][j]);
		}
	}
	for (int i = 0; i < n1->length; i++)
		secondStepMass[i] = (unsigned*)realloc(secondStepMass[i], (n1->length + n2->length) * sizeof(unsigned));
	
	alignment_mult_val(&secondStepMass[0], n1->length, n1->length + n2->length);

	divide = 0;
	for (int i = n1->length + n2->length - 1; i >= 0; i--)
	{
		for (int j = 0; j < n1->length; j++)
		{
			res->val[i] += secondStepMass[j][i];
		}
		res->val[i] += divide;
		if (res->val[i] > 9999)
		{
			divide = res->val[i] / 10000;
			res->val[i] %= 10000;
		}
		else
			divide = 0;
	}

	for (int t = 0; t < n1->length + n2->length; t++)
		printf("\nRESULT VAL [%d] = %u", t, res->val[t]);
	word_alignment(res);
	if (sign)
		res->sign = true;
}

void divide(bool sign, supportMASS *n1, supportMASS *n2)
{
	unsigned lenDen = 0;
	lenDen = getLengthDenomination(n2);
	
	unsigned frst, scnd;
	if (compare(n1, lenDen, n2)) // true - (tmp > denom) else - false
	{
		lenDen++;
	}

	
}

int get_nineCount(unsigned X, int j)
{
	int n = -1;
	X /= 10;
	if (X == 0)
		return 3 -j;
	while (1)
	{
		if (X % 10 == 0)
		{
			n++;
			X = X / 10;
		}
		else
			break;
	}
	return n;
}

void operation_definition(char op)
{
	int size1 = 0, size2 = 0;
	if (num1->length > num2->length)
		size1 = 1;
	else if (num1->length < num2->length)
		size2 = 1;
	else {
		for (int i = 0; i < result.length - 1; i++) 
		{
			if (num1->val[i] > num2->val[i] || i == result.length - 2)
			{
				size1 = 1;
				break;
			}
			else
			{
				size2 = 1;
				break;
			}
		}
	}
	if (num2->sign == true)
	{
		if (op == "-")
		{
			num2->sign = false;
			op = "+";
		}
		else if (op == "+")
		{
			op = "-";
			num2->sign == false;
		}
	}
	if (op == '-')
	{
		if (num1->sign == true && num2->sign == false)
			add(true);
		else if (size1 > size2 && num1->sign == false)
			subtract(false, num1, num2);
		else if (num1->sign == false && size1 < size2)
		{
			swapBigNum(num1, num2);
			subtract(true, num1, num2);
		}
	}
	 else if (op == '+')
	{
		if (num1->sign == false && num2->sign == false)
			add(false);
		else if (num1->sign == true && size1 > size2)
			subtract(true);
		else if (num1->sign == true && size1 < size2)
		{
			swapBigNum();
			subtract(false);
		}
	}
	else if (op == '*')
	{
		if (size1 < size2)
			swapBigNum();
		if (num1->sign == true && num2->sign == true)
			multiply(false);
		else if (num1->sign == true || num2->sign == true)
			multiply(true);
		else if (num1->sign == false && num2->sign == false)
			multiply(false);
	}
	else if (op == '/')
	{
		if (size1 < size2)
			swapBigNum(num1, num2);
		if (num1->sign == true && num2->sign == true)
			divide(false, num1, num2);
		else if (num1->sign == true || num2->sign == true)
			divide(true, num1, num2);
		else if (num1->sign == false && num2->sign == false)
			divide(false, num1, num2);
	}
	else
	{
		printf("\nERROR Invalid operation!\n");
		system("pause");
		exit(1);
	}
}
 
void swapBigNum(supportMASS* n1, supportMASS *n2)
{
	supportMASS *tmp;
	tmp = n1;
	n1 = n2;
	n2 = tmp;
}

void word_alignment(supportMASS *num)
{
	int flag = 0, tmp = 0;
	for (int i = 0; i < num->length; i++)
	{
		tmp = num->val[i];
		while (tmp < pow(10, BLOCK_SIZE-1))
		{
			if (tmp == 0 && flag == 0)
				break;
			num->zero[i]++;
			if (tmp == 0)
			{
				tmp = 1;
				continue;
			}
			tmp *= 10;
			flag = 1;
		}
		flag = 1;
	}
}

void realloc_result()
{
	unsigned n = 0, tmp, indx;
	for (int i = 0; i < res->length; i++)
	{
		if (res->val[i] != 0)
		{
			indx = i;
			n = i;
			break;
		}
	}
	res->length = res->length - indx;
	while (n > 0)
	{
		for (int i = 0; i < res->length; i++)
		{
			res->val[indx-1] = res->val[indx];
			indx++;
		}
		indx = indx - res->length;
		n--;
	}
	res->val = (unsigned*)realloc(res->val, res->length * sizeof(unsigned));
	res->zero = (int*)realloc(res->zero, res->length * sizeof(int));
}

void alignment_mult_val(unsigned** mass, int n,  int len)
{
	int minus = n - 1, it;
	unsigned tmp = 0;

	//забиваем нулями новые ячейки
	for (int i = 0; i < n; i++)
	{
		for (int j = num2->length+1; j < len; j++)
		{
			mass[i][j] = 0;
		}
	}

	printf("\nBEFORE SWAP:");
	for (int i = 0; i < n; i++)
	{
		printf("\nMASS[%d] => ", i);
		for (int j = 0; j < len; j++)
		{
			printf("|%u", mass[i][j]);
			tmp = mass[i][j];
			if (tmp > 99 && tmp <= 999)
				printf(" ");
			else if (tmp > 9 && tmp <= 99)
				printf("  ");
			else if (tmp >= 0 && tmp <= 9)
				printf("   ");
		}
	}
	//================свапаем числа в массиве для дальнейшего корректного сложения================= 
	for (int i = 0; i < num2->length + 1; i++)
	{
		it = n - 1;
		for (int j = 0; j < ( (n - 1)/2 +1); j++)
		{
			tmp = mass[j][i];
			mass[j][i] = mass[it][i];
			mass[it][i] = tmp;
			it--;
		}
	}
	printf("\nAFTER SWAP:");
	for (int i = 0; i < n; i++)
	{
		printf("\nMASS[%d] => ", i);
		for (int j = 0; j < len; j++)
		{
			printf("|%u", mass[i][j]);
			tmp = mass[i][j];
			if (tmp > 99 && tmp <= 999)
				printf(" ");
			else if (tmp > 9 && tmp <= 99)
				printf("  ");
			else if (tmp >= 0 && tmp <= 9)
				printf("   ");
		}
	}


	//сдвигаем числа в строке для корректного сложения по столбикам
	for (int i = 0; i < n; i++)
	{
		if (minus == 0)
			break;
		for (int j = len-1; j >= minus; j--)
		{
			mass[i][j] = mass[i][j - minus];
			mass[i][j - minus] = 0;
		}
		minus--;
	}

	printf("\nALIGMENT MASS:");
	for (int i = 0; i < n; i++)
	{
		printf("\nMASS[%d] => ", i);
		for (int j = 0; j < len; j++)
		{
			printf("|%u", mass[i][j]);
			tmp = mass[i][j];
			if (tmp > 99 && tmp <= 999)
				printf(" ");
			else if (tmp > 9 && tmp <= 99)
				printf("  ");
			else if (tmp >= 0 && tmp <= 9)
				printf("   ");
		}
	}

}

bool get_numbers_from_console(char** numbers, int argc, char** argv)
{
	int len1 = 150, len2 = 150, it = 0;
	numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));
	numbers[2] = (char*)realloc(numbers[2], len1 * sizeof(char));

	char ch;
	if (argc > 1)
	{
		while (1)
		{
			ch = argv[1][it];
			if (ch == '\0')
			{
				numbers[0][it] = ch;
				break;
			}
			if (it == len1 - 1)
			{
				len1 += 50;
				numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));
			}
			numbers[0][it] = argv[1][it];
			it++;
		}
		ch = 0;
		it = 0;
		while (1)
		{
			ch = argv[3][it];
			if (ch == '\0')
			{
				numbers[2][it] = ch;
				break;
			}
			if (it == len1 - 1)
			{
				len1 += 50;
				numbers[2] = (char*)realloc(numbers[0], len1 * sizeof(char));
			}
			numbers[2][it] = argv[3][it];
			it++;
		}
		numbers[1][0] = argv[2][0];
		numbers[1][1] = '\0';
		return false;
	}
	printf("\nEnter first number: ");
	while (1)
	{
		ch = getc(stdin);
		if (ch == '\n')
			break;
		numbers[0][it] = ch;
		if (it == len1 - 2)
		{
			len1 += 50;
			numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));
		}
		it++;
	}
	numbers[0][it] = '\0';
	len1 = ++it;
	numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));

	printf("\nEnter second number: ");
	ch = 0;
	it = 0;
	while (1)
	{
		ch = getc(stdin);
		if (ch == '\n')
			break;
		numbers[2][it] = ch;
		if (it == len2 - 2)
		{
			len2 += 50;
			numbers[2] = (char*)realloc(numbers[2], len2 * sizeof(char));
		}
		it++;
	}
	numbers[2][it] = '\0';
	len2 = ++it;
	numbers[2] = (char*)realloc(numbers[2], len2 * sizeof(char));

	printf("\nEnter operation: ");
	scanf_s("%c", &ch);
	numbers[1][0] = ch;
	numbers[1][1] = '\0';

}

void trandlate_to_dec(char** numbers)
{
	int len1 = 0, len2 = 0,
		it=0, tmp =0;
	while (numbers[0][it] != '\0')
	{
		len1++;
		it++;
	}
	it = 0;
	while (numbers[2][it] != '\0')
	{
		len2++;
		it++;
	}
}

unsigned getLengthDenomination(supportMASS* n)
{
	unsigned tmp = 0, len = 1;
	if (n->val[0] != 0)
		tmp = n->val[0];
	else
		tmp = n->val[1];
	while (1)
	{
		tmp /= 10;
		if (tmp == 0)
			break;
		len++;
	}
	return len;
}

bool compare(supportMASS* n1, unsigned len, supportMASS* n2)
{

}