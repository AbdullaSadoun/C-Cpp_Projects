#pragma once
#ifndef ISBN_H
#define ISBN_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MXN 81

FILE* fin;

void isbncheck(const char* fin);

#endif // ISBN_H