/*
program that utilizes
multithreading to accomplish the task of integer sorting.
ASN3 CSCI 3120
By: Abdulla Sadoun
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct { // struct to hold the parameters for each thread/list of ints
    int starting_index;
    int ending_index;
} parameters;

int compare(const void *a, const void *b); /* function to compare two integers */
void *sorter(void *params); /* thread that performs basic sorting algorithm */
void *merger(void *params); /* thread that performs merging of results */ 

int numbers[1000];
int sizeofarray;

int main(int argc, char *argv[]){

    FILE *fout = fopen("SortedIntegerList.txt", "w");

    /* check for command line arguments */
    if (argc < 2) {
            printf("Please provide a filename as an argument.\n");
            return 1;
        }

        FILE *fin = fopen(argv[1], "r");
        if (fin == NULL) {
            printf("Cannot open file\n");
            return 1;
        }

    /*reading the list*/
    int i = 0;
    while (fscanf(fin, "%d,", &numbers[i]) != EOF) { // was && i <=500)
        i++;
    }

    sizeofarray = i; // setting the size of the array

    /*initializing parameters for each thread*/
    parameters* first_thread_params = (parameters*) malloc(sizeof(parameters));
    parameters* second_thread_params = (parameters*) malloc(sizeof(parameters));

    /* determining parameters for each thread */
    first_thread_params->starting_index = 0;
    if(sizeofarray%2 == 0) { // sizeofarray is even
            first_thread_params->ending_index = sizeofarray/2 - 1;
            second_thread_params->starting_index = sizeofarray/2;
            second_thread_params->ending_index = sizeofarray - 1;
        } else { // sizeofarray is odd
            first_thread_params->ending_index = sizeofarray/2 ;
            second_thread_params->starting_index = sizeofarray/2 + 1;
            second_thread_params->ending_index = sizeofarray - 1;
        }

    pthread_t thread1, thread2, thread3; // initializing threads

    /* create the first and second threads (sorting) */
    pthread_create(&thread1, NULL, sorter, first_thread_params); // quick sort
    pthread_create(&thread2, NULL, sorter, second_thread_params); // quick sort

    /* wait for sorting threads*/
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    parameters *merge_params = malloc(sizeof(parameters));
    merge_params->starting_index = first_thread_params->starting_index;
    merge_params->ending_index = second_thread_params->ending_index;

    /* create the third thread (merging) */
    pthread_create(&thread3, NULL, merger, merge_params);

    /* now wait for the merging thread to finish */
    pthread_join(thread3, NULL);

    /* output the sorted array */
    for (int j = 0; j < sizeofarray; j++) {
        fprintf(fout, "%d ", numbers[j]);
    }

    // close the files
    fclose(fin);
    fclose(fout);
    return 0;

}

void *sorter(void *params) { // quick sort
/* 
sorting algorithm implementation
Using quick sort 
*/
    parameters *p = (parameters*) malloc(sizeof(parameters));
    p = params;
    int start = p->starting_index;
    int end = p->ending_index;
    int size = end - start + 1;

    qsort((numbers+start), size, sizeof(int), compare); // quick sort

    return NULL;
}

int compare(const void *a, const void *b) {
/*
function to compare two integers
*/
    return (*(int*)a - *(int*)b);
}

void *merger(void *params){
/* merging algorithm implementation
compares the first index of each sub list, smallest gets added next
*/

    parameters *p = (parameters*)params; 
    int start1 = 0; // same as before in sorter
    int end1 = (p->ending_index) / 2; // odd/even doesnt matter in merge
    int start2 = end1 + 1; // starts where the first sub list ends
    int end2 = p->ending_index;

    int *temp = malloc((end2 - start1 + 1) * sizeof(int));
    int i = start1, j = start2, k = 0;

    while (i <= end1 && j <= end2) { //comparing the first index of each sub list
        if (numbers[i] <= numbers[j]) {
            temp[k++] = numbers[i++];
        } else {
            temp[k++] = numbers[j++];
        }
    }
    while (i <= end1) { // if the first sub list is not empty
        temp[k++] = numbers[i++];
    }
    while (j <= end2) { // if the second sub list is not empty
        temp[k++] = numbers[j++];
    }

    k = 0;
    for (int i = start1; i <= end2; i++) {
        numbers[i] = temp[k];
        k++;
    }

    free(temp);
}

