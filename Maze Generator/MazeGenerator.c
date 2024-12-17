#include "MazeGenerator.h"

void processnumber(char c[], int i, int* reps) {
    if (digits(c[i - 1])) {
        *reps = (c[i] - '0') + (c[i - 1] - '0');
        if (*reps > maxchar) {
            printf("Too many characters\n");
        }
    }
    else {
        *reps = (c[i] - '0');
    }
}

void validcharprocess(char c[], int i, int reps) {
    //int lreps = reps;
    if (c[i] == 'b') { // print black reps amount if b found
        for (int n = 0; n < reps; n++) {
            printf("%c", ' ');
        }
    }
    else if (c[i] == '!') {// starting a new row
        if (digits(c[i - 1])) { // checking if the character prior is a number.
            for (int n = 0; n < reps; n++) {
                printf("\n");
            }
        }
        else { // if there is no skipped rows
            printf("\n");
        }
    }
    else {
        for (int n = 0; n < reps; n++) { // print character reps amt
            printf("%c", c[i]);
        }
    }
}

void invalidcharprocess() {
    printf("Invalid Character");
    return;
}

void newmazedetected() {
    printf("\n");
}