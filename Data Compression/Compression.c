/*
A5.c
This program is used to uncompress and process a compressed file
This is the Implementation file of the program containing all the defintions of the functions used.
By: Abdulla Sadoun
*/

#include "Compression.h"


void free_mem(node_t** ptr) { // freeing memory incase freed node become 0 (using the address of the pointer (**))
    node_t* current;
    node_t* next;

    current = *ptr; // getting the value of ptr

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *ptr = NULL; // freeing and clearing the pointer
}

void initialize_list(node_t** ptr) { // address of the pointer
    *ptr = NULL;
}

int add_to_list(node_t** list, char* item) {
    node_t* new_entry;
    int len;

    new_entry = malloc(sizeof(node_t));
    if (new_entry == NULL) // no heap space case
        return 0;

    strcpy_s(new_entry->data, wlength, item); // copy content new_entry

    new_entry->next = *list; // to connect entry to the list
    *list = new_entry; // ""

    return 1;
}

void Reading(char* input) { // reads the content of the file in the proper format and processes it
    int position = 0, i;
    node_t* ptr;

    while (*input && *input != '0' && *input != EOF) { // not end of file && no '0' encountered to end the message
        if (isalpha(*input)) { // checking if char is 'A'-'Z' || 'a'-'z'
            Word[position] = *input;  // adding char to the word
            position++;
        }
        else if (isdigit(*input)) { // if the current input is a digit from 0-9
            if (position != 0) { // if a word is being collected then add it to the list
                add_to_list(&start, Word);
                printf("%s", Word);
            }
            memset(Word, 0, position); // clear the current word in the list
            position = 0;
            int digit = 0;

            while (isdigit(*input)) { // digits = char to integer conversion
                digit = (digit * 10) + (*input - '0');
                input++;
            }
            input--;

            node_t* current;
            node_t* previous;
            current = start;
            previous = NULL;

            if (digit == 1) { // when a one is encountered, print the content at the top of the list
                printf("%s", current->data);
            }
            else { // else go through the list looking for the content asked for in the file
                for (i = 1; i < digit; i++) {
                    previous = current;
                    current = current->next;
                }
                printf("%s", current->data);
                previous->next = current->next;
                current->next = start;
                start = current;
            }
        }
        else { // case of punctuation or other characters (!= alpha && != digit)
            if (position != 0) {
                add_to_list(&start, Word); // add to list
                printf("%s", Word); // print it 
            }
            memset(Word, 0, position); // clear it 
            position = 0;
            printf("%c", *input); // print the char
        }
        input++;
    }
}

