#pragma once
#ifndef A4_h
#define A4_h

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 31
#define MAX_DICTIONARY_SIZE 100
#define INITIAL_COUNTER_VALUE 0
#define FALSE 0
#define TRUE 1

//function prototypes
int myStrcasecmp(char* str1, char* str2);
int isWordInDictionary(char dictionary[][MAX_WORD_LENGTH], int dictionary_size, char* word);
int storeDictionary(char* dictionary_file_path, char dictionary[][MAX_WORD_LENGTH], int max_words);
void GoingThroughCheckFile(char* check_file_path, char dictionary[][MAX_WORD_LENGTH], int dictionary_size);

FILE* fin;

#endif //A4
