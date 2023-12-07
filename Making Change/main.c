/*Making Change
Created by: Abdulla Sadoun
Description: This application aids employees working at cash with handling change with the new Canadian cash system.*/


#include "CHANGE.h"


int main(int argc, char* argv[]) {

    const char* fin = argv[1];//test1

    if (argc == 1) { // file missing a name test
        printf("Missing File Name\n");
        (void)getchar();
        return -1;
    }

    if (fopen_s(&fin, argv[1], "r") != 0) { // opening the file
        printf("File content Error. - file does not exist\n", argv[1]);
        (void)getchar();
        return -1;
    }


    float cost[MXN], paid[MXN], rounded_cost;
    int cost_in_cents[MXN], remainder[MXN];
    int i = 0;

    while (fscanf(fin, "%f %f", &cost[i], &paid[i]) != EOF) {
        rounded_cost = 0;

        if (cost[i] == invalid && paid[i] == invalid) { // this skips the input line if its 0.00 and 0.00
            break;
        }

        rounded_cost = roundingcost(cost[i]); // rounds to the nearest 5 cents

        finaldecision(cost[i], paid[i], rounded_cost);

        i++;//incrementing i to store the next line info
    }

    fclose(fin);//closing the input file
    (void)getchar();//to keep the command window open
}
