#include "A4.h"

int myStrcasecmp(char* str1, char* str2) { // this function converts uppercase chars to lowercase chars
    while (*str1 && *str2) {
        char c1 = *str1;
        char c2 = *str2;

        if (c1 >= 'A' && c1 <= 'Z') {
            c1 += 'a' - 'A';
        }

        if (c2 >= 'A' && c2 <= 'Z') {
            c2 += 'a' - 'A';
        }

        if (c1 != c2) {
            return c1 - c2;
        }

        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int isWordInDictionary(char dictionary[][MAX_WORD_LENGTH], int dictionary_size, char* word) {

    char filtered_word[MAX_WORD_LENGTH]; // string of word without ',' or '.' or '?' or '!'

    int length = strlen(word); // get the length of the word to make the loops
    int start = INITIAL_COUNTER_VALUE;
    int end = length - 1;

    /* removing ',' or '.' or '?' or '!' */
    while (end >= 0 && (word[end] == ',' || word[end] == '.' || word[end] == '?' || word[end] == '!')) { // has nl ('\n')
        end--;
    }
    while (start < length && (word[start] == ',' || word[start] == '.' || word[start] == '?' || word[start] == '!')) { // no nl ('\n')
        start++;
    }
    if (end >= 1 && word[end] == '\n' && (word[end - 1] == ',' || word[end - 1] == '.' || word[end - 1] == '?' || word[end - 1] == '!')) { // has nl ('\n')
        end--;
    }

    strncpy(filtered_word, word + start, end - start + 1); // putting it in the filtered word spot
    filtered_word[end - start + 1] = '\0';

    if (strlen(filtered_word) == 0) { // no spelling error if the filtered word is empty
        return 1;
    }

    for (int i = 0; i < dictionary_size; i++) { // checking if "filtered" word is in the dictionary
        if (myStrcasecmp(filtered_word, dictionary[i]) == 0) { // accounting for case sensitivity while searching
            return 1;
        }
    }
    return 0; // word not found in the dictionary array
}

int storeDictionary(char* dictionary_file_path, char dictionary[][MAX_WORD_LENGTH], int max_words) { // storing the content of the dictionary to the program
    FILE* dictionary_file = NULL;
    if (fopen_s(&dictionary_file, dictionary_file_path, "r") != 0 || dictionary_file == NULL) {
        printf("Error opening dictionary file");
        return 0;
    }

    int word_count = 0;
    char word[MAX_WORD_LENGTH];

    while (word_count < max_words && fscanf(dictionary_file, "%s", word) != EOF) {
        word[strcspn(word, "\n")] = '\0'; // filtering out the NL('/n') chars

        strncpy(dictionary[word_count], word, MAX_WORD_LENGTH - 1);// copying the word to dictionary array
        dictionary[word_count][MAX_WORD_LENGTH - 1] = '\0';

        word_count++;
    }

    fclose(dictionary_file);
    return word_count;
}

void GoingThroughCheckFile(char* check_file_path, char dictionary[][MAX_WORD_LENGTH], int dictionary_size) {
    FILE* check_file = NULL;
    if (fopen_s(&check_file, check_file_path, "r") != FALSE || check_file == NULL) {
        printf("Error opening check file");
        return;
    }

    char check_word[MAX_WORD_LENGTH];
    int has_spelling_errors = FALSE;

    printf("File \"%s\" ", check_file_path);

    char misspelled_words[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH]; // storing the misspelled words
    int misspelled_count = 0;

    // Read words from the check file and check their spelling against the dictionary
    while (fscanf(check_file, "%s", check_word) != EOF) {
        if (!isWordInDictionary(dictionary, dictionary_size, check_word)) {// to check if the word is in the dictionary
            has_spelling_errors = TRUE;
            strncpy(misspelled_words[misspelled_count], check_word, MAX_WORD_LENGTH - 1); // store the misspelled words in their array 
            misspelled_words[misspelled_count][MAX_WORD_LENGTH - 1] = '\0';
            misspelled_count++;
        }
    }

    if (has_spelling_errors) {
        printf("has spelling errors.\n");
        // Print all misspelled words
        for (int j = 0; j < misspelled_count; j++) {
            printf("%s\n", misspelled_words[j]);
        }
    }
    else {
        printf("has no spelling errors.\n");
    }

    fclose(check_file);
}
