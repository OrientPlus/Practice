#pragma once

int sqr(int number, int power);
int translate_string_to_number(int* mass, int size, int notation);
int check_max_notation(int* mass, int size);
int translate_number_to_string(int mass_size, int* int_array, int notation, char* char_array);

int check_enter(int N);
int my_atoi(char* array_symbols, int not, int size_array_symbols);
int my_itoa(int N, int notation);