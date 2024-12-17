/*
Maze Generator: Makes a maze based on the users description in the input file

Created by: Abdulla Sadoun

*/

#include "MazeGenerator.h"

FILE* fin;

int main(int argc, char* argv[]) { //int argc, char* argv[]

    //FILE* fin = fopen("test.txt", "r");
    const char* fin = argv[1]; //test1


    //Check number of arguments
    if (argc == 1)
    {
        printf("Missing file name\n");
        (void)getchar();
        return -1;
    }

    /* argc >= 1, attempt to open file */
    if (fopen_s(&fin, argv[1], "r") != 0)
    {
        printf("Error opening file >%s< - possibly missing\n", argv[1]);
        (void)getchar();
        return -1;
    }

    char c[MXN];
    int i = 0;
    int reps = 0;

    while (fscanf_s(fin, "%c", &c[i]) != EOF) { //reading characters from the file.

        if (digits(c[i])) { // check for digits //if (c[i] >= '0' && c[i] <= '9')
            processnumber(c, i, &reps);
        }
        else if ((alphabet(c[i])) || c[i] == newline || c[i] == exception) { //if c is a letter (not b or !) then print it reps amt
            validcharprocess(c, i, reps);
        }
        else if (newstart(c[i])) {// to start a new maze
            newmazedetected();
        }
        else {
            invalidcharprocess(); //if the character is not a number, letter, *, or !
        }
        i++; // needed for all cases
    }

    fclose(fin);
    (void)getchar();
    return 0;
}