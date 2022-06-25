#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "bigNum.h"
#include "calculate.h"

#define BLOCK_SIZE 4

bigInt* num1 = &a, * num2 = &b;


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
	printBigNum(num1);
	printf("\nOperation: %c", numbers[1][0]);
	printf("\nSecond number: ");
	printBigNum(num2);

	operation_definition(numbers[1][0]);

	printf("\nResult number: ");
	printBigNum(&result);
}

void check_numbers(int argc, char** argv)
{
	char alph[] = { "-0123456789ABCDEF" };
	char opr[] = { "+-*/" },
		ch;
	int it = 0, sFlag = 0;
	
	
	while (ch = argv[0][it])
	{
		if (ch == '\0')
			break;
		for (int i = 0; i < 17; i++)
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
			else if (i == 16)
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
		for (int i = 0; i < 17; i++)
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
			else if (i == 16)
			{
				printf("\nERROR! Invalid second number\n");
				system("pause");
				exit(1);
			}
		}
		it++;
	}
	ch = argv[1][0];
	for (int i = 0; i < 4; i++)
	{
		if (ch == opr[i])
			break;
		else if (i == 3)
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
	num2->sign = false;
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

	
	num1->val = (char**)malloc(num1->length * sizeof(char*));
	num2->val = (char**)malloc(num2->length * sizeof(char*));

	
	for (int i = 0; i < num1->length; i++)
	{
		num1->val[i] = (char*)malloc(BLOCK_SIZE * sizeof(char));
		for (int j = 0; j < BLOCK_SIZE; j++)
			num1->val[i][j] = 'N';
	}
	for (int i = 0; i < num2->length; i++)
	{
		num2->val[i] = (char*)malloc(BLOCK_SIZE * sizeof(char));
		for (int j = 0; j < BLOCK_SIZE; j++)
			num2->val[i][j] = 'N';
	}

	//------------------Initializing the result-----------------//
	if (argv[1][0] == '+' && num1->length == num2->length && (argv[0][0] + argv[2][0] >= 120))
		result.length = num1->length + 1;
	else if (argv[1][0] == '+')
	{
		if (num1->length > num2->length)
			result.length = num1->length;
		else
			result.length = num2->length;
	}
	else if (argv[1][0] == '-')
	{
		if (num1->length > num2->length)
			result.length = num1->length;
		else
			result.length = num2->length;
	}
	else if (argv[1][0] == '*')
		result.length = num1->length + num2->length;
	else if (argv[1][0] == '/')
		result.length = num2->length; //заглушка; необходимо корректно опеределить длину при делении

	result.val = (char**)malloc(result.length * sizeof(char*));
	for (int i = 0; i < result.length; i++)
	{
		result.val[i] = (char*)malloc(BLOCK_SIZE * sizeof(char));
		for (int j = 0; j < BLOCK_SIZE; j++)
			result.val[i][j] = 'N';
	}
}

void getNumbers(int argc, char** argv)
{
	int it = 0,
		strLen, n, flag = 0, hexF =0;
	char tmp = 0;
	
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

	strLen = strlen(argv[0]);
	n = strLen -1;
	for (int i = num1->length-1; i>=0;  i--)
	{
		for (int j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			if (n == -1)
				break;
			num1->val[i][j] = argv[0][n];
			n--;
		}
	}

	strLen = strlen(argv[2]);
	n = strLen - 1;
	for (int i = num2->length - 1; i >= 0; i--)
	{
		for (int j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			if (n == -1)
				break;
			num2->val[i][j] = argv[2][n];
			n--;
		}
	}
	
}

void printBigNum(bigInt *num)
{
	if (num->sign)
		printf("-");
	for (int i = 0; i < num->length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (num->val[i][j] != 'N' )
				printf("%c", num->val[i][j]);
		}
	}
}

void ADD(bool sign, bigInt *n1, bigInt *n2)
{
	char TABLE[16][16][2] = {
		{ {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"} },
		{ {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"} },
		{ {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"} },
		{ {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"} },
		{ {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"} },
		{ {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"} },
		{ {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"} },
		{ {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"} },
		{ {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"} },
		{ {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"} },
		{ {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"} },
		{ {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"} },
		{ {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"} },
		{ {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"} },
		{ {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"} },
		{ {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"}, {"1E"} }
	};
	int n1_it = n1->length - 1, 
		n2_it = n2->length - 1, 
		 div=0,
		x, y, j = 0;
	char** tmpMass = NULL;
	bool flag = false;


	tmpMass = (char**)malloc(result.length * sizeof(char*));
	for (int i = 0; i < result.length; i++)
		tmpMass[i] = (char*)malloc(BLOCK_SIZE * sizeof(char));
	for (int i = 0; i < result.length; i++)
	{
		for (int _j = 0; _j < BLOCK_SIZE; _j++)
			tmpMass[i][_j] = 0;
	}

	for (int i = result.length -1; i >= 0; i--)
	{
		if (n1_it <= -1 && n2_it <= -1)
		{
			if (div != 0)
			{
				if (j == -1)
					j = BLOCK_SIZE - 1;
				tmpMass[i][j] = int_to_char(div);
			}
			break;
		}
		for (j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			if (n1_it >= 0 && n2_it >= 0)
			{
				if (n2->val[n2_it][j] == 'N')
					n2->val[n2_it][j] = '0';
				if (n1->val[n1_it][j] == 'N')
				{
					tmpMass[i][j] = 'N';
					break;
				}
				x = char_to_int(n1->val[n1_it][j]);
				y = char_to_int(n2->val[n2_it][j]);

				if (x != 15)
					x = x + div;
				else if (y != 15)
					y = y + div;
				else if (flag)
				{
					tmpMass[i][j] = TABLE[x][y][1]+1;
					if (TABLE[x][y][0] != '0')
						div = 1;
					else
						div = 0;
					continue;
				}
				tmpMass[i][j] = TABLE[x][y][1];
				if (TABLE[x][y][0] != '0')
					div = 1;
				else
					div = 0;
				flag = true;
			}
			else if (n1_it >= 0 && n2_it < 0)
			{
				if (div != 0)
				{
					if (n1->val[n1_it][j] == 'N')
						n1->val[n1_it][j] = '0';
					x = char_to_int(n1->val[n1_it][j]);
					y = div;
					tmpMass[i][j] = TABLE[x][y][1];
					if (TABLE[x][y][0] != '0')
						div = char_to_int(TABLE[x][y][0]);
					else
						div = 0;
				}
				else
					tmpMass[i][j] = n1->val[n1_it][j];
			}
		}
		n1_it--;
		n2_it--;
	}


	printf("\n\n");
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			result.val[i][j] = tmpMass[i][j];
		}
	}
	if (sign)
		result.sign = true;
}

void SUBTRACT(bool sign, bigInt *n1,  bigInt *n2)
{
	int n1_it = n1->length - 1,
		n2_it = n2->length - 1,
		flag = 0, div = 0,
		x, y, X, Y, nine_count = -2;
	char** tmpMass = NULL;

	tmpMass = (char**)malloc(result.length * sizeof(char*));
	for (int i = 0; i < result.length; i++)
		tmpMass[i] = (char*)malloc(BLOCK_SIZE * sizeof(char));
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
			tmpMass[i][j] = 0;
	}

	for (int i = result.length-1; i >= 0;  i--)
	{
		if (n1_it <= -1 && n2_it <= -1)
			break;
		for (int j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			//===========================================================
			X = n1->val[n1_it][j];
			if (n2_it >= 0)
				Y = n2->val[n2_it][j];
			else 
				Y = '0';
			if (Y == 'N')
				Y = '0';
			//===========================================================
			x = char_to_int(X);
			y = char_to_int(Y);

			
			if (nine_count >= 0 && x == 0)
			{
				x = 'F' - '0' - 7;
				nine_count--;
			}
			else if (div == 1 || nine_count == -1)
			{
				x = x-div;
				div = 0;
				nine_count--;
			}
			if ((x == 0 && X == '0') && (y == 0 && Y == '0'))
				break;

			x = x - div;
			if (x < y)
			{
				if (n1->val[n1_it][j - 1] == '0')
				{
					nine_count = get_zero_count(n1, n1_it, j);
					x += 16;
					x -= y;
					tmpMass[i][j] = int_to_char(x);
					div = 0;
					continue;
				}
				x += 16;
				x -= y;
				tmpMass[i][j] = int_to_char(x);
				div = 1;
				continue;
			}
			else
				div = 0;
			x -= y;
			tmpMass[i][j] = int_to_char(x);
		}
		n2_it--;
		n1_it--;
	}

	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			result.val[i][j] = tmpMass[i][j];
		}
	}
	if (sign)
		result.sign = true;

}

void MULTIPLY(bool sign, bigInt *n1, bigInt *n2)
{
	char TABLE[16][16][2] = {
		{ {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"}, {"00"} },
		{ {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"} },
		{ {"00"}, {"02"}, {"04"}, {"06"}, {"08"}, {"0A"}, {"0C"}, {"0E"}, {"10"}, {"12"}, {"14"}, {"16"}, {"18"}, {"1A"}, {"1C"}, {"1E"} },
		{ {"00"}, {"03"}, {"06"}, {"09"}, {"0C"}, {"0F"}, {"12"}, {"15"}, {"18"}, {"1B"}, {"1E"}, {"21"}, {"24"}, {"27"}, {"2A"}, {"2D"} },
		{ {"00"}, {"04"}, {"08"}, {"0C"}, {"10"}, {"14"}, {"18"}, {"1C"}, {"20"}, {"24"}, {"28"}, {"2C"}, {"30"}, {"34"}, {"38"}, {"3C"} },
		{ {"00"}, {"05"}, {"0A"}, {"0F"}, {"14"}, {"19"}, {"1E"}, {"23"}, {"28"}, {"2D"}, {"32"}, {"37"}, {"3C"}, {"41"}, {"46"}, {"4B"} },
		{ {"00"}, {"06"}, {"0C"}, {"12"}, {"18"}, {"1E"}, {"24"}, {"2A"}, {"30"}, {"36"}, {"3C"}, {"42"}, {"48"}, {"4E"}, {"54"}, {"5A"} },
		{ {"00"}, {"07"}, {"0E"}, {"15"}, {"1C"}, {"23"}, {"2A"}, {"31"}, {"38"}, {"3F"}, {"46"}, {"4D"}, {"54"}, {"5B"}, {"62"}, {"69"} },
		{ {"00"}, {"08"}, {"10"}, {"18"}, {"20"}, {"28"}, {"30"}, {"38"}, {"40"}, {"48"}, {"50"}, {"58"}, {"60"}, {"68"}, {"70"}, {"78"} },
		{ {"00"}, {"09"}, {"12"}, {"1B"}, {"24"}, {"2D"}, {"36"}, {"3F"}, {"48"}, {"51"}, {"5A"}, {"63"}, {"6C"}, {"75"}, {"7E"}, {"87"} },
		{ {"00"}, {"0A"}, {"14"}, {"1E"}, {"28"}, {"32"}, {"3C"}, {"46"}, {"50"}, {"5A"}, {"64"}, {"6E"}, {"78"}, {"82"}, {"8C"}, {"96"} },
		{ {"00"}, {"0B"}, {"16"}, {"21"}, {"2C"}, {"37"}, {"42"}, {"4D"}, {"58"}, {"63"}, {"6E"}, {"79"}, {"84"}, {"8F"}, {"9A"}, {"A5"} },
		{ {"00"}, {"0C"}, {"18"}, {"24"}, {"30"}, {"3C"}, {"48"}, {"54"}, {"60"}, {"6C"}, {"78"}, {"84"}, {"90"}, {"9C"}, {"A8"}, {"B4"} },
		{ {"00"}, {"0D"}, {"1A"}, {"27"}, {"34"}, {"41"}, {"4E"}, {"5B"}, {"68"}, {"75"}, {"82"}, {"8F"}, {"9C"}, {"A9"}, {"B6"}, {"C3"} },
		{ {"00"}, {"0E"}, {"1C"}, {"2A"}, {"38"}, {"46"}, {"54"}, {"62"}, {"70"}, {"7E"}, {"8C"}, {"9A"}, {"A8"}, {"B6"}, {"C4"}, {"D2"} },
		{ {"00"}, {"0F"}, {"1E"}, {"2D"}, {"3C"}, {"4B"}, {"5A"}, {"69"}, {"78"}, {"87"}, {"96"}, {"A5"}, {"B4"}, {"C3"}, {"D2"}, {"E1"} }
	};

	int** IntermediateMass = (int**)malloc((n1->length * BLOCK_SIZE) * sizeof(int*));
	for (int i = 0; i < n1->length*BLOCK_SIZE; i++)
		IntermediateMass[i] = (int*)malloc((n1->length*BLOCK_SIZE+1) * sizeof(int));
	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		for (int j = 0; j < n1->length * BLOCK_SIZE+1; j++)
			IntermediateMass[i][j] = '0';
	}
	int* res_mass = (int*)malloc((n1->length * BLOCK_SIZE * 2) * sizeof(int));
	for (int i = 0; i < n1->length * BLOCK_SIZE * 2; i++)
		res_mass[i] = '0';

	int div = 0, div_flag = 0, flag = 0,
		n1_it = n1->length - 1, n2_it = n2->length - 1,
		IM_it_char, IM_it_word,
		x, y, X, Y;
	int temp[2] = {0};

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	IM_it_word = n1->length * BLOCK_SIZE;
	for (int k = n2->length - 1; k >= 0; k--)
	{
		for (int f = BLOCK_SIZE - 1; f >= 0; f--)
		{
			IM_it_char = n1->length * BLOCK_SIZE;
			Y = n2->val[k][f];
			if (Y == 'N')
				Y = '0';
			IM_it_word--;

			for (int i = n1->length - 1; i >= 0; i--)
			{
				for (int j = BLOCK_SIZE - 1; j >= 0; j--)
				{
					IM_it_char--;
					X = n1->val[i][j];
					if (X != 'N')
					{
						x = char_to_int(X);
						if (Y == 'N')
							Y = '1';
						y = char_to_int(Y);


						if (div != 0)
						{
							plus_div(TABLE[x][y], div, &temp);
							IntermediateMass[IM_it_word][IM_it_char] = temp[1];
							div = temp[0];
							//printf("%c", IntermediateMass[IM_it_word][IM_it_char]);
							continue;
						}
						else
						{
							IntermediateMass[IM_it_word][IM_it_char] = TABLE[x][y][1];
							//printf("%c", IntermediateMass[IM_it_word][IM_it_char]);
						}

						if (TABLE[x][y][0] != '0')
							div = char_to_int(TABLE[x][y][0]);
						else
							div = 0;
					}
					else
					{
						IntermediateMass[IM_it_word][IM_it_char] = int_to_char(div);
						div = 0;
						//printf("\nSMASS [%d][%d] = %c", f, IM_it_char, IntermediateMass[f][IM_it_char]);
						break;
					}
				}
			}
		}
	}
	/*for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		printf("\n [%d] mass = ", i);
		for (int j = 0; j < n1->length * BLOCK_SIZE; j++)
			printf("%c", IntermediateMass[i][j]);
	}*/


	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		IntermediateMass[i] = (int*)realloc(IntermediateMass[i], ((n1->length * BLOCK_SIZE) * 2) * sizeof(int));
	}

	/*for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		printf("\n [%d] mass = ", i);
		for (int j = 0; j < n1->length * BLOCK_SIZE * 2; j++)
			printf("%c", IntermediateMass[i][j]);
	}*/
	alignment_mult_val(&IntermediateMass[0], n1, n2);

	//Функция сложения промежуточных блоков большого числа
	for (int i = 0; i < n1->length*BLOCK_SIZE; i++)
	{
		plus_interm_val(&res_mass[0], &IntermediateMass[0], i, n1->length*BLOCK_SIZE*2);

		/*printf("\nInter res [%d]: ", i);
		for (int i = 0; i < n1->length * BLOCK_SIZE * 2; i++)
		{
			printf("%c", res_mass[i]);
		}*/
	}
	
	/*printf("\nResult mass: ");
	for (int i = 0; i < n1->length * BLOCK_SIZE*2; i++)
	{
		printf("%c", res_mass[i]);
	}*/

	x = n1->length * BLOCK_SIZE * 2 - 1; X = 0;
	for (int i = result.length-1; i>=0; i--)
	{
		for (int j = BLOCK_SIZE -1; j>=0; j--)
		{
			result.val[i][j] = res_mass[x];
			x--;
		}
	}
	for (int i = 0; i < result.length; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (result.val[i][j] == '0' && X == 0)
				result.val[i][j] = 'N';
			else
			{
				X = 1;
				break;
			}
		}
	}

	//free(res_mass);
	if (sign)
		result.sign = true;
}

void DIVIDE(bool sign, bigInt* n1, bigInt* n2)
{
	printf("\nOops, sorry, this option has not been implemented yet!");
	system("pause");
	exit(10);
}

int get_zero_count(bigInt *num, int i, int j)
{
	int n = -1, flag = 0, _j = j-1;
	for (i; i >= 0; i--)
	{
		if (flag != 0)
			_j = BLOCK_SIZE -1;
		for (_j; _j >= 0; _j--)
		{
			if (num->val[i][_j] == '0')
				n++;
			else
				return n;
		}
		flag = 1;
	}
}

void operation_definition(char op)
{
	int size1 = 0, size2 = 0;
	if (num1->length > num2->length)
		size1 = 1;
	else if (num1->length < num2->length)
		size2 = 1;
	else {
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			size1 = num1->val[0][j];
			size2 = num2->val[0][j];
			if (size1 == 'N')
				size1 = 0;
			if (size2 == 'N')
				size2 = 0;
			if (size1 > size2 || j == BLOCK_SIZE - 1)
			{
				size1 = 1;
				size2 = 0;
				break;
			}
			else if (size1 == size2)
				continue;
			else
			{
				size2 = 1;
				size1 = 0;
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
			ADD(true, num1, num2);
		else if (size1 > size2 && num1->sign == false)
			SUBTRACT(false, num1, num2);
		else if (num1->sign == false && size1 < size2)
		{
			swapBigNum(num1, num2);
			SUBTRACT(true, num1, num2);
		}
	}
	else if (op == '+')
	{
		if (num1->sign == false && num2->sign == false)
		{
			if (size1 < size2)
				swapBigNum(num1, num2);
			ADD(false, num1, num2);
		}
		else if (num1->sign == true && size1 > size2)
			SUBTRACT(true, num1, num2);
		else if (num1->sign == true && size1 < size2)
		{
			swapBigNum(num1, num2);
			SUBTRACT(false, num1, num2);
		}
	}
	else if (op == '*')
	{
		if (size1 < size2)
			swapBigNum(num1, num2);
		if (num1->sign == true && num2->sign == true)
			MULTIPLY(false, num1, num2);
		else if (num1->sign == true || num2->sign == true)
			MULTIPLY(true, num1, num2);
		else if (num1->sign == false && num2->sign == false)
			MULTIPLY(false, num1, num2);
	}
	else if (op == '/')
	{
		if (size1 < size2)
			swapBigNum(num1, num2);
		if (num1->sign == true && num2->sign == true)
			DIVIDE(false, num1, num2);
		else if (num1->sign == true || num2->sign == true)
			DIVIDE(true, num1, num2);
		else if (num1->sign == false && num2->sign == false)
			DIVIDE(false, num1, num2);
	}
	else
	{
		printf("\nERROR Invalid operation!\n");
		system("pause");
		exit(1);
	}
}
 
void swapBigNum(bigInt* n1, bigInt *n2)
{
	bigInt tmp;
	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

void alignment_mult_val(unsigned** mass, bigInt* n1, bigInt* n2)
{
	int minus = 1, it, n = n1->length, len =0;
	unsigned tmp = 0;


	int ch_len = 0;
	for (int i = 0; i < n1->length*BLOCK_SIZE; i++)
	{
		for (int j = (n1->length * BLOCK_SIZE) * 2; j>=0; j--)
		{
			if (clean_cell(mass[i][j]))
			{
				mass[i][j] = '0';
			}
			else
				ch_len = j;
		}
	}

	

	/*printf("\nBEFORE SWAP:");
	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		printf("\n [%d] mass = ", i);
		for (int j = 0; j < n1->length * BLOCK_SIZE * 2; j++)
			printf("%c", mass[i][j]);
	}*/
	//================свапаем числа в массиве для дальнейшего корректного сложения================= 
	for (int i = 0; i < n1->length*BLOCK_SIZE*2; i++)
	{
		it = n1->length*BLOCK_SIZE -1;
		for (int j = 0; j < n1->length*BLOCK_SIZE/2; j++)
		{
			tmp = mass[j][i];
			mass[j][i] = mass[it][i];
			mass[it][i] = tmp;
			it--;
		}
	}
	/*printf("\nAFTER SWAP:");
	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		printf("\n [%d] mass = ", i);
		for (int j = 0; j < n1->length * BLOCK_SIZE * 2; j++)
			printf("%c", mass[i][j]);
	}*/

	minus = n1->length * BLOCK_SIZE * 2 - 1;
	//сдвигаем числа в строке для корректного сложения по столбикам
	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		minus = n1->length * BLOCK_SIZE * 2 - 1;
		for (int j = n1->length * BLOCK_SIZE - 1; j >= 0; j--)
		{
			mass[i][minus - i] = mass[i][j];
			mass[i][j] = '0';
			minus--;
		}
	}

	/*printf("\nALIGMENT MASS:");
	for (int i = 0; i < n1->length * BLOCK_SIZE; i++)
	{
		printf("\n [%d] mass = ", i);
		for (int j = 0; j < n1->length * BLOCK_SIZE * 2; j++)
			printf("%c", mass[i][j]);
	}*/

}

void get_numbers_from_console(char** numbers, int argc, char** argv)
{
	int len1 = 150, len2 = 150, it = 0;
	numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));
	numbers[2] = (char*)realloc(numbers[2], len1 * sizeof(char));

	char ch;
	if (argc > 1 )
	{
		if (argc != 4 )
		{
			printf("\nError! Invalid argument!\n");
			system("pause");
			exit(12);
		}
		while (1)
		{
			ch = argv[1][it];
			if (ch == '\0')
			{
				numbers[0][it] = ch;
				len1 = it+1;
				numbers[0] = (char*)realloc(numbers[0], len1 * sizeof(char));
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
				len2 = it + 1;
				numbers[2] = (char*)realloc(numbers[2], len2 * sizeof(char));
				break;
			}
			if (it == len1 - 1)
			{
				len2 += 50;
				numbers[2] = (char*)realloc(numbers[2], len2 * sizeof(char));
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

unsigned getLengthDenomination(bigInt* n)
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

bool compare(bigInt* n1, unsigned len, bigInt* n2)
{

}

int plus_div(char num[2], int div, int *tmp)
{
	char TABLE[16][16][2] = {
		{ {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"} },
		{ {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"} },
		{ {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"} },
		{ {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"} },
		{ {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"} },
		{ {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"} },
		{ {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"} },
		{ {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"} },
		{ {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"} },
		{ {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"} },
		{ {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"} },
		{ {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"} },
		{ {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"} },
		{ {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"} },
		{ {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"} },
		{ {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"}, {"1E"} }
	};
	int x, y;

	if (num[1] > '9')
		x = num[1] - '0' - 7;
	else
		x = num[1] - '0';

	y = div;
	//if (TABLE[x][y][1] > '9')
	//	res[1] = TABLE[x][y][1] - '0' - 7;
	//else
	//	res[1] = TABLE[x][y][1] - '0';

	tmp[1] = TABLE[x][y][1]; 


	if (TABLE[x][y][0] != '0')
		tmp[0] = 1;
	else
		tmp[0] = 0; 

	if (num[0] > '9')            
		tmp[0] += (num[0] - '0' - 7);
	else
		tmp[0] += (num[0] - '0');
}

bool clean_cell(int cell)
{
	char ALPH[] = { "0123456789ABCDEF" };
	for(int i=0; i<17; i++)
		if (cell == ALPH[i])
			return false;
	return true;
}

void plus_interm_val(int *res, int** tmp, int it,  int len)
{
	char TABLE[16][16][2] = {
		{ {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"} },
		{ {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"} },
		{ {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"} },
		{ {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"} },
		{ {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"} },
		{ {"05"}, {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"} },
		{ {"06"}, {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"} },
		{ {"07"}, {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"} },
		{ {"08"}, {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"} },
		{ {"09"}, {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"} },
		{ {"0A"}, {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"} },
		{ {"0B"}, {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"} },
		{ {"0C"}, {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"} },
		{ {"0D"}, {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"} },
		{ {"0E"}, {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"} },
		{ {"0F"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"1A"}, {"1B"}, {"1C"}, {"1D"}, {"1E"} }
	};

	int i,x, y, div =0;

	for (i = len-1; i>=0; i--)
	{
		x = char_to_int(res[i]);
		y = char_to_int(tmp[it][i]);
		if (x != 15)
			x = x + div;
		else
			y = y + div;
		res[i] = TABLE[x][y][1];
		if (TABLE[x][y][0] != '0')
			div = char_to_int(TABLE[x][y][0]);
		else
			div = 0;
	}
	if (div != 0)
	{
		res[i] = int_to_char(div);
	}
}

int char_to_int(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch - '0' - 7;
	else if (ch <= '9' && ch >= '0')
		return ch - '0';
	else
		return '#';
}

char int_to_char(int n)
{
	if (n >= 10 && n <= 15)
		return n + '0' + 7;
	else if (n <= 9 && n >= 0)
		return n + '0';
	else
		return -1;
}
