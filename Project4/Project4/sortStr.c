#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "sortStr.h"

#define STRINGS_COUNT   10
#define MAX_STRING_SIZE 100


void SORT()
{
    srand(time(NULL));
    int choise = 0;
    char strings[STRINGS_COUNT][MAX_STRING_SIZE];
    int (*fptr)(const char*, const char*) = NULL;

    GenerateRandomStrings(strings);
    printf("\nGenerated array of strings:");
    PrintStrings(strings);
    printf("\n\
(1) - Sort alphabetically(considering reg)\n\
(2) - Sort alphabetically in descending order\n\
(3) - Sort alphabetically, case-insensitive\n\
(4) - Sorting by line length\
\n:");
    scanf_s("%d", &choise);
    if (choise == 1)
        fptr = SortByAlphabet;
    else if (choise == 2)
        fptr = sortByAlphabetDescending;
    else if (choise == 3)
        fptr = SortByAlphabetNoReg;
    else if (choise == 4)
        fptr = SortByLength;

    SortStrings(strings, STRINGS_COUNT, fptr);
    
    printf("\nSorted array:\n");
    PrintStrings(strings);
}

void GenerateRandomString(char *str)
{
    char alphabet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
    unsigned int size = 1 + rand() % MAX_STRING_SIZE,
        pos = 0;
    for (int i = 0; i < size; i++)
    {
        pos = rand() % 52;
        str[i] = alphabet[pos];
    }
    if (size < MAX_STRING_SIZE-1)
        str[size] = '\0';

}

void GenerateRandomStrings(char str[][MAX_STRING_SIZE]) {

    for (int i = 0; i < STRINGS_COUNT; i++) 
    {
        GenerateRandomString(str[i], i);
    }

}

void PrintStrings(char strings[][MAX_STRING_SIZE])
{
    printf("\n=====================================================================================\n");
    for (int i = 0; i < STRINGS_COUNT; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < MAX_STRING_SIZE; j++)
        {
            if (strings[i][j] == '\0')
                break;
            printf("%c", strings[i][j]);
        }
        printf("\n");
    }

}


void SortStrings(char strings[][MAX_STRING_SIZE], unsigned int stringsCount, int (*compareStringsFunction)(const char*, const char*))
{
    unsigned int i, pvt = 0;

    if (stringsCount <= 1)
        return;

    swap(strings + ((unsigned int)rand() % stringsCount), strings + stringsCount - 1);

    for (i = 0; i < stringsCount - 1; ++i)
    {
        if (compareStringsFunction(strings[i], strings[stringsCount - 1]) < 0)
            swap(strings + i, strings + pvt++);
    }

    swap(strings + pvt, strings + stringsCount - 1);

    SortStrings(strings, pvt++, compareStringsFunction);
    SortStrings(strings + pvt,  stringsCount - pvt, compareStringsFunction);

}

void swap(char* arg1, char* arg2)
{
    char temp;

    if (arg1 == NULL || arg2 == NULL)
        return;
    for (int _i = 0; _i < MAX_STRING_SIZE; _i++)
    {
        temp = arg1[_i];
        arg1[_i] = arg2[_i];
        arg2[_i] = temp;
    }
}



int SortByAlphabetNoReg(const char* first, const char* second)
{
    int countFirst = 0;
    int countSecond = 0;

    while (((toupper(*first) != '\0' && toupper(*second) != '\0') && (countFirst != MAX_STRING_SIZE && countSecond != MAX_STRING_SIZE)) && toupper(*first) == toupper(*second))
    {
        first++;
        second++;
        countFirst++;
        countSecond++;
    }

    if (toupper(*first) == toupper(*second)) return 0;
    else if (toupper(*first) > toupper(*second)) return -1;
    else return 1;
}

int SortByAlphabet(const char* first, const char* second)
{
    return sortByAlphabetDescending(first, second) * (-1);
}

int sortByAlphabetDescending(const char* first, const char* second)
{
    int countFirst = 0;
    int countSecond = 0;

    while (((*first != '\0' && *second != '\0') && (countFirst != MAX_STRING_SIZE && countSecond != MAX_STRING_SIZE)) && *first == *second)
    {
        first++;
        second++;
        countFirst++;
        countSecond++;
    }

    if (*first == *second) return 0;
    else if (*first > *second) return 1;
    else return -1;
}

int SortByLength(const char* first, const char* second)
{
    int countFirst = 0;
    int countSecond = 0;
    
    while (*first != '\0' && countFirst!= MAX_STRING_SIZE )
    {
        first++;
        countFirst++;
    }
    while (*second != '\0' && countSecond != MAX_STRING_SIZE)
    {
        second++;
        countSecond++;
    }
    if (countFirst > countSecond)
        return 1;
    else if (countFirst < countSecond)
        return -1;
    else
        return 0;
}