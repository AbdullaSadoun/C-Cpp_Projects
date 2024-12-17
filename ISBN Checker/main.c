#include "ISBN.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Missing File Name\n");
        getchar();
        return -1;
    }

    const char* fin = argv[1];

    // Call the function to process the file
    isbncheck(fin);

    return 0;
}
