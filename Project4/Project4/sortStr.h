#pragma once

#define STRINGS_COUNT   10
#define MAX_STRING_SIZE 100


void SORT();

void GenerateRandomStrings(char str[][MAX_STRING_SIZE]);
void GenerateRandomString(char* str);
void PrintStrings(char str[][MAX_STRING_SIZE]);

void SortStrings(char str[][MAX_STRING_SIZE], unsigned int stringsCount, int (*compareStringsFunction)(const char*, const char*));
void swap(char* arg1, char* arg2);

int SortByAlphabet(const char* first, const char* second);
int sortByAlphabetDescending(const char* first, const char* second);
int SortByAlphabetNoReg(const char* first, const char* second);
int SortByLength(const char* first, const char* second);