#include "ISBN.h"

// Function definition to process the file
void isbncheck(const char* fin) {
    char c[MXN];
    char digit[MXN];
    int s1[MXN] = { 0 };
    char s2[MXN] = { 0 };
    int last2; // the last partial sum (s2)

    // Opening the file
    if (fopen_s(&fin, fin, "r") != 0) {
        printf("File content Error.");
        getchar();
        return;
    }

    while (fgets(c, sizeof(c), fin) != NULL) {
        int i = 0;
        int n = 0;

        while (c[i] != '\0') {
            if (c[i] != 58 && c[i] != 45 && c[i] != '\n') {
                if (c[i] >= 48 && c[i] <= 57) {
                    digit[n] = c[i];
                    s1[n + 1] = s1[n] + digit[n] - '0';
                    s2[n + 1] = s2[n] + s1[n + 1];
                    n++;
                }
                else if (c[i] == 88 && n == 9) {
                    digit[n] = '0';
                    s1[n + 1] = s1[n] + 10;
                    s2[n + 1] = s2[n] + s1[n + 1];
                    n++;
                }
            }
            i++;
        }

        last2 = s2[n]; // assign the last s2 as last2 to divide

        i = 0;

        while (c[i] != '\0') { // printing the said code for the final decision on the screen
            if (c[i] != ' ' && c[i] != '\n') {
                printf("%c", c[i]);
            }
            i++;
        }

        if (last2 % 11 == 0 || i > 15) { // so it invalids the more than 10 digits isbns 
            printf(" is invalid\n");
        }
        else {
            printf(" is valid\n");
        }
    }

    fclose(fin); // close the file

    getchar();
}

