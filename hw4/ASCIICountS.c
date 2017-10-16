/*
* Nehemya McCarter-Ribakoff
* Yue
* CSC 415 M/W 4:10 PM
* 16 October 2017
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>


#define NUM_THREADS 4
#define BUFFER_LENGTH 65536

int asciiTable[128];
char buffer[BUFFER_LENGTH];
pthread_mutex_t lock;


typedef struct{
    int partitionBounds;
    int threadNumber;
    int max_length;
} threadData;

void *ascii_checker(void *t_info) {
    int i, threadLocation;
    
    threadData *threadinfo = (threadData*) t_info;
    
    threadLocation = threadinfo->threadNumber * threadinfo->partitionBounds;
    
    for(i = 0; threadLocation + i < threadinfo->max_length && i < threadinfo->partitionBounds; i++) {
        pthread_mutex_lock(&lock);
        asciiTable[buffer[threadLocation + i]]++;
        pthread_mutex_unlock(&lock);
    }
    
    pthread_exit(NULL);
} 

double calcSeconds(void){
    return (double)clock()/CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
    
    pthread_t threadIds[NUM_THREADS];
    
    threadData t_info[NUM_THREADS];
    
    int i, j, sourceFile, partitions, charTotal, aThread;
    
    sourceFile = open(argv[1], O_RDONLY);
    
    if (sourceFile < 0){
        fprintf(stderr, "Error opening file!\n");
        return -1;
    } 

    sourceFile = read(sourceFile, buffer, BUFFER_LENGTH);
    
    partitions = (double) sourceFile / (double) NUM_THREADS;
    
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }
    
    for(i = 0; i < NUM_THREADS; i++) {
        t_info[i].threadNumber = i;
        t_info[i].partitionBounds = partitions;
        t_info[i].max_length = sourceFile;

        aThread = pthread_create(&threadIds[i], NULL, &ascii_checker, &t_info[i]);
        
        if(aThread != 0)
            printf("Error creating thread! %i\n", i);
    }
    
    
    i = 0;
    do{
        pthread_join(threadIds[i], NULL);
        i++;
    } while (i < NUM_THREADS);
    
    for(i = 0; i < 128; i++) {
        printf("%i occurrences of ", asciiTable[i]);
        if(i < 33 || i == 127){
            printf("%#0x\n", i);
        }
        else{
            printf("%c\n", i);
        }
    }
    close(sourceFile);
    
    return 0;
} 
