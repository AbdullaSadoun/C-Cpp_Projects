#pragma once
/*
A5.h
This program is used to uncompress and process a compressed file
This is the Header file for the program highlighting the methods, libraries and functions used.
By: Abdulla Sadoun
*/

#pragma once

#ifndef Compression_h
#define Compression_h

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define wlength 50 // length of the word
#define blength 50 // length of the buffer var. being processed
#define NUL '\0'
#define NL '\n' // New line character

FILE* fin;

struct node { // linked list structure
    char data[wlength];
    struct node* next;
};
typedef struct node node_t; // so i do not have to type struct node every time

node_t* start;

void free_mem(node_t** ptr);
void initialize_list(node_t** ptr);
int add_to_list(node_t** list, char* item);
void Reading(char* input);

char Word[wlength];
char Builder[blength];

#endif //COMPRESSION
