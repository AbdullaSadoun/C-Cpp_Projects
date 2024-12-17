/*
testingA5.c
This program is used to uncompress and process a compressed file
This is the main of the program

By: Abdulla Sadoun
*/
#include "Compression.h"

int main(int argc, char* argv[]) {

    if (argc == 1) { // file name name
        printf("Missing file name\n");
    }
    else {
        if (fopen_s(&fin, argv[1], "r") != 0) { // file content check
            printf("Error opening file %s - possibly missing\n", argv[1]);
            getchar();
            return -1;
        }
    }

    initialize_list(&start); // starting the empty linked list

    while (fgets(Builder, blength, fin) > 0) {
        Reading(Builder);
    }

    free_mem(&start); // freeing the memory from the list
    fclose(fin); // closing the compressed folder
    getchar();
    return 0;
}
