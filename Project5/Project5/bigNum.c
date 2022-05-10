#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bigNum.h"
#include "calculate.h"

int get_nineCount(unsigned X, int j);
bigInt* num1 = &a, * num2 = &b;


int bigNum(int argc, char** argv)
{	
	char operation = 0;
	initNumbers(&argv[0]);
	getNumbers(argc, &argv[0]);
	printf("\n\nFirst number: ");
	printBigNum(num1);
	printf("\nSecond number: ");
	printBigNum(num2);

	operation = argv[2][0];
	operation_definition(operation);

	printf("\nResult number: ");
	printBigNum(&result);
	free(num1->val);
	free(num2->val);
	free(result.val);
}

void initNumbers(char** argv)
{
	num1->sign = false;
	num1->zero = NULL;
	num2->sign = false;
	num2->zero = NULL;
	result.sign = false;
	num1->length = strlen(argv[1]) / 9;
	if (strlen(argv[1]) - 9 * num1->length > 0)
		num1->length++;
	num2->length = strlen(argv[3]) / 9;
	if (strlen(argv[3]) - 9 * num1->length > 0)
		num2->length++;
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
		result.length = num1->length + 1;
	else
		result.length = num2->length + 1;
	result.val = (unsigned*)malloc(result.length * sizeof(unsigned));
	result.zero = (int*)malloc(result.length * sizeof(int));

	for (int i = 0; i < result.length; i++)
	{
		result.val[i] = 0;
		result.zero[i] = 0;
	}
}

void getNumbers(int argc, char** argv)
{
	int it = 0,
		strLen, n, flag = 0;
	unsigned tmp = 0;
	
	if (argv[1][0] == '-')
	{
		argv[1][0] = '0';
		num1->sign = true;
	}
	if (argv[3][0] == '-')
	{
		argv[3][0] = '0';
		num2->sign = true;
	}
	
	it = num1->length - 1;
	strLen = strlen(argv[1]);
	for (int i = 0; i < strLen / 9 + 1; i++)
	{
		n = 9 * (i + 1);
		for (int j = 9; j > 0; j--)
		{
			if (strLen - n >=0)
				tmp = tmp * 10 + argv[1][strLen - n] - '0';
			n--;
		}
		num1->val[it] = tmp;
		tmp = 0;
		it--;
	}
	word_alignment(num1);

	tmp = 0;
	it = num2->length-1;
	strLen = strlen(argv[3]);
	for (int i = 0; i < strLen / 9 + 1; i++)
	{
		n = 9 * (i + 1);
		for (int j = 9; j > 0; j--)
		{
			if (strLen - n >= 0)
				tmp = tmp * 10 + argv[3][strLen - n] - '0';
			n--;
		}
		num2->val[it] = tmp;
		tmp = 0;
		it--;
	}
	word_alignment(num2);
}

void printBigNum(bigInt *num)
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


	tmpMass = (int**)malloc(result.length * sizeof(int*));
	for (int i = 0; i < result.length; i++)
		tmpMass[i] = (int*)malloc(9 * sizeof(int));
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < 9; j++)
			tmpMass[i][j] = 0;
	}

	for (int i = 0; i < result.length; i++)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		if (n1_it >=0)
			X = num1->val[n1_it];
		if (n2_it >=0)
			Y = num2->val[n2_it];
		for (int j = 0; j < 9; j++)
		{
			x = X % 10;
			y = Y % 10;
			if ((x == 0 && X == 0) && (y == 0 && Y == 0))
				break;
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
				tmpMass[(result.length - 1) - i][8 - j] = x;
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
			tmpMass[(result.length - 1) - i][8 - j] = x;
			X = X / 10;
			Y = Y / 10;
		}

		n1_it--;
		n2_it--;
	}


	printf("\n\n");
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tmpMass[i][j] == 0 && flag == 0)
				continue;
			else
			{
				result.val[i] = result.val[i] * 10 + tmpMass[i][j];
				flag = 1;
			}
		}
	}
	realloc_result();
	word_alignment(&result);
	if (sign)
		result.sign = true;
}

void subtract(bool sign)
{
	unsigned x, y, X, Y;
	int div = 0, nine_count = -2, it_I = 0, zero_count = 0;
	int n1_it = num1->length - 1, n2_it = num2->length - 1, flag = 0;
	int** tmpMass = NULL;

	tmpMass = (int**)malloc(result.length * sizeof(int*));
	for (int i = 0; i < result.length; i++)
		tmpMass[i] = (int*)malloc(9 * sizeof(int));
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < 9; j++)
			tmpMass[i][j] = 0;
	}

	for (int i = 0; i < result.length; i++)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		if (n1_it >= 0)
			X = num1->val[n1_it];
		if (n2_it >= 0)
			Y = num2->val[n2_it];
		for (int j = 0; j < 9; j++)
		{
			x = X % 10;
			y = Y % 10;
			if (nine_count >=0 && x == 0)
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
					tmpMass[(result.length - 1) - i][8 - j] = x;
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
			tmpMass[(result.length - 1) - i][8 - j] = x;
			X = X / 10;
			Y = Y / 10;
		}
		n2_it--;
		n1_it--;
	}

	printf("\n\n");
	for (int i = 0; i < result.length; i++) //Формируем слово большого числа из полученных значений разрядов
	{
		for (int j = 0; j < 9; j++)
		{
			if (tmpMass[i][j] == 0 && flag == 0)
				continue;
			else
			{
				result.val[i] = result.val[i] * 10 + tmpMass[i][j];
				flag = 1;
			}
		}
	}
	realloc_result();
	word_alignment(&result);
	if (sign)
		result.sign = true;
}

void multiply()
{
	int n1_it = num1->length - 1, n2_it = num2->length - 1, flag = 0;
	unsigned X, Y;
	
	
	for (int i = 0; i < num1->length; i++)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		if (n1_it >= 0)
			X = num1->val[n1_it];
		if (n2_it >= 0)
			Y = num2->val[n2_it];
		mult_block(X, Y);
		n1_it--;
		n2_it--;
	}
}

void divide()
{

}

void remains()
{

}

int get_nineCount(unsigned X, int j)
{
	int n = -1;
	X /= 10;
	if (X == 0)
		return 7 -j;
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
			subtract(false);
		else if (num1->sign == false && size1 < size2)
		{
			swapBigNum();
			subtract(true);
		}
	}
	if (op == '+')
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
	if (op == '*')
	{
		multiply();
	}
	if (op == '/')
	{

	}
	if (op == '%')
	{

	}
}

void swapBigNum()
{
	/*unsigned* tmp = (unsigned*)malloc(result.length - 1 * sizeof(unsigned)), tmpLen=0;
	if (num1.length > num2.length)
	{
		num2.val = (unsigned*)realloc(num2.val, num1.length * sizeof(unsigned));
		for (int i = 0; i < (num1.length - num2.length); i++)
			num2.val[i] = 0;
	}
	else {
		num1.val = (unsigned*)realloc(num1.val, num2.length * sizeof(unsigned));
		for (int i = 0; i < (num1.length - num2.length); i++)
			num1.val[i] = 0;
	}
	for (int i = 0; i < result.length - 1; i++)
	{
		tmp[i] = num1.val[i];
		num1.val[i] = num2.val[i];
	}
	if (num1.length > num2.length)
		num1.val = */

	bigInt *tmp;
	tmp = num1;
	num1 = num2;
	num2 = tmp;
}

void word_alignment(bigInt *num)
{
	int flag = 0, tmp = 0;
	for (int i = 0; i < num->length; i++)
	{
		tmp = num->val[i];
		while (tmp < 100000000)
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
	}
}

void realloc_result()
{
	unsigned n = 0, tmp, indx;
	for (int i = 0; i < result.length; i++)
	{
		if (result.val[i] != 0)
		{
			indx = i;
			n = i;
			break;
		}
	}
	result.length = result.length - indx;
	while (n > 0)
	{
		for (int i = 0; i < result.length; i++)
		{
			result.val[indx-1] = result.val[indx];
			indx++;
		}
		indx = indx - result.length;
		n--;
	}
	result.val = (unsigned*)realloc(result.val, result.length * sizeof(unsigned));
	result.zero = (int*)realloc(result.zero, result.length * sizeof(int));
}

void mult_block(unsigned X, unsigned Y)
{
	char ALPH[] = { "0123456789ABCDEF" };
	int it = 0, len1 = 0, len2 = 0, len3=0;
	char* str1, *str2, str3 = NULL, tmp = NULL;
	str1 = my_itoa(X, 16);
	str2 = my_itoa(Y, 16);
	while (str1[it] != '\0')
	{
		len1++;
		it++;
	}
	it = 0;
	while (str2[it] != '\0')
	{
		len2++;
		it++;
	}
	if (len1 > len2)
		len3 = len1;
	else
		len3 = len2;
	len3+=2;
	str3 = (char*)malloc(len3 * sizeof(char));
	tmp = (char*)malloc(len3 * sizeof(char));

}