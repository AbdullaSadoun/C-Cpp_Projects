#pragma once
#ifndef MAZEGEENRATOR_h
#define MAZEGENERATOR_h

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MXN 150
#define maxchar 132
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define alphabet(c) (((c) >= 'A' && (c) <= 'Z')||((c) >= 'a' && (c) <= 'z'))
#define digits(c) ((c) > '0' && (c) <= '9') // any character thats a number 0 to 9
#define newstart(c) c== '\n' && c == '\n'
#define newline '!'
#define exception '*'

void processnumber(char c[], int i, int* reps);
void validcharprocess(char c[], int i, int reps);
void invalidcharprocess();
void newmazedetected();


FILE* fin;

#endif //MAZEGENERATOR