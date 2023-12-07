#pragma once
#ifndef CHANGE_H
#define CHANGE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define centsinadollar 100.0
#define roundingnumber 0.5 //used to insure the number converted to int is done so correctly
#define MXN 100
#define invalid 0.00
#define roundingconstant 5

FILE* fin;

void calculateChange(float cost, float paid);
float roundingcost(float cost);
void finaldecision(float cost, float paid, float rounded_cost);

#endif //CHANGE