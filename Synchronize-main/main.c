/*
C program that utilizes synchronization to solve the bounded buffer problem
By: Abdulla Sadoun
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5
typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];

// 2. Initialize semaphores and mutex lock
sem_t empty, full; // declaring semaphores
pthread_mutex_t mutex; // declaring mutex

void initializeBuffer();
int insert_item(buffer_item item, int pindex);
int remove_item(buffer_item *item, int cindex);
void* producer(void *param);
void* consumer(void *param);

int main(int argc, char *argv[]) {
    int sleeptime, producerthreads, consumerthreads;
    
    // 1. Get command-line arguments argv[1],argv[2],argv[3] and test validity
    sleeptime = atoi(argv[1]); // convert string to integer
    producerthreads = atoi(argv[2]); // ''
    consumerthreads = atoi(argv[3]); // ''

    if(argc!=4 || sleeptime>100 || sleeptime<1 || producerthreads >5 || producerthreads<1 || consumerthreads>5 || consumerthreads<1) { // check for valid input cli arguments
        printf("Invalid CLI arguments\n");
        return -1;
    }

    // 3. Initialize buffer
    initializeBuffer(); 

    // 4. Create producer thread(s)
    pthread_t producers[producerthreads];
    for (int i = 0; i < producerthreads; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&producers[i], NULL, producer, (void*)id);
    }
    
    // 5. Create consumer thread(s)
    pthread_t consumers[consumerthreads];
    for (int i = 0; i < consumerthreads; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&consumers[i], NULL, consumer, (void*)id);
    }

    // 6. Sleep
    sleep(sleeptime);

    return 0;
}

void initializeBuffer() { // make all buffer elements -1
    int i=0;
    while(i<BUFFER_SIZE){
        buffer[i] = -1;
        i++;
    }
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
}

int insert_item(buffer_item item, int pindex) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    
    int position = -1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == -1) {
            buffer[i] = item;
            position = i;
            printf("Producer %d inserted item %d into buffer[%d]\n", pindex, item, position);
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    if (position != -1) {
        return 0;
    } else {
        return -1;
    }
}

int remove_item(buffer_item *item, int cindex) { // removes item from buffer
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    
    int position = -1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] != -1) {
            *item = buffer[i];
            buffer[i] = -1;
            position = i;
            printf("Consumer %d consumed item %d from buffer [%d]\n", cindex, *item, position);
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    if (position != -1) {
        return 0;
    } else {
        return -1;
    }
}

void* producer(void *param) { 
    int pindex = *(int*)param;
    buffer_item item;
    while(1) {
        sleep(rand() % 5); // sleep for a random time: 0-4 seconds
        item = rand(); // generate a random number
        insert_item(item, pindex); // insert an item
    }
    free(param);
}

void* consumer(void *param) {
    int cindex = *(int*)param;
    buffer_item item;
    while(1) {
        sleep(rand() % 5); // sleep for a random time: 0-4 seconds
       remove_item(&item, cindex); // remove an item
    }
    free(param);
}