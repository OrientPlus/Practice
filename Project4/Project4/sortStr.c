#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "sortStr.h"

#define STRINGS_COUNT   10
#define MAX_STRING_SIZE 100

void SORT()
{
    srand(time(NULL));
    char strings[STRINGS_COUNT][MAX_STRING_SIZE] = {0};
    int choise = 0;
    void (*fptr)(char*) = NULL;

    GenerateRandomStrings(strings);
    PrintStrings(strings);
    printf("\n1- ALPABET SORT(no case)\n2- ALPABET SORT\n3- LENGTH SORT\n");
    scanf_s("%d", &choise);
    switch (choise)
    {
    case 1:
        fptr = SortStrings;
    default:
        break;
    }
    SortStrings(strings, fptr);
}

void GenerateRandomString(char str[STRINGS_COUNT][MAX_STRING_SIZE], int i)
{
    char alphabet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
    unsigned int size = 1 + rand() % MAX_STRING_SIZE,
        pos = 0;
    for (int j = 0; j < size; j++)
    {
        pos = rand() % 53;
        str[i][j] = alphabet[pos];
    }

}


void GenerateRandomStrings(char str[STRINGS_COUNT][MAX_STRING_SIZE]) {

    for (int i = 0; i < STRINGS_COUNT; i++) 
    {
        GenerateRandomString(str, i);
    }

}

void PrintStrings(char strings[STRINGS_COUNT][MAX_STRING_SIZE])
{
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


void SortStrings(char strings[STRINGS_COUNT][MAX_STRING_SIZE], void* compareStringsFunction)
{


}