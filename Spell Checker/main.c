#include "SPELLCHECKER.h"


int main(int argc, char* argv[]) {

    if (argc < 3) { // if the three files werent opened correctly
        printf("Usage: %s <dictionary_file> <check_file1> [<check_file2> etc...]\n", argv[0]); // remind user of how to enter the files in cmd prompt
        return TRUE;
    }

    char* dictionary_file_path = argv[1]; // setting the dictionary file to argv[1]

    char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH]; // declaring dictionary array 

    int dictionary_size = storeDictionary(dictionary_file_path, dictionary, MAX_DICTIONARY_SIZE);// read and store the dictionary array from dictionary file
    if (dictionary_size == 0) {
        return TRUE;
    }


    for (int i = 2; i < argc; i++) { // going through the words in the check files to see if they match with the ones in the dictionary file
        char* check_file_path = argv[i]; // setting the opened check file to argv[i] for checking
        GoingThroughCheckFile(check_file_path, dictionary, dictionary_size); // this function will compare the words in check files against the ones in the dictionary
    }

    printf("End of Output\n"); // marking the end of the output

    getchar();
    return 0;
}
