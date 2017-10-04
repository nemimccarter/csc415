#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUM_THREADS 8
#define BUFFER_LENGTH 65536
#define ASCII_CHAR_COUNT 128

int asciiTable[NUM_THREADS][ASCII_CHAR_COUNT];
char buffer[BUFFER_LENGTH];

typedef struct {
    int partitionBounds;
    int threadNumber;
} threadData;

void *runner(void *t_info);
double Seconds(void);

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    threadData t_info[NUM_THREADS];
    int sourceFile;
    int partitions;
    int charTotal;
    int aThread;
    double t;

    sourceFile = open(argv[1], O_RDONLY);

    if (sourceFile < 0){
        fprintf(stderr, "Error opening file.\n");
        return 1;
    } 

    sourceFile = read(sourceFile, buffer, BUFFER_LENGTH);

    t = Seconds();
    
    partitions = (double) sourceFile / (double) NUM_THREADS;
    close(sourceFile);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        t_info[i].threadNumber = i;
        t_info[i].partitionBounds = partitions;
        aThread = pthread_create(&threads[i], NULL, &runner, &t_info[i]);
        
        if (aThread < 0)
            printf("Error creating thread! %i\n", i);
    } 
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        i++;
    }
    
    for (int i = 0; i < ASCII_CHAR_COUNT; i++) {
        charTotal = 0;
        for (int j = 0; j < NUM_THREADS; j++) {
            charTotal += asciiTable[j][i];
        } 

        printf("%i occurrences of ", charTotal);

        if (i < 33 || i == 127) {
            printf("%#0x\n", i);
        }
        else {
            printf("'%c'\n", i);
        } 
    }
    
    t = Seconds() - t;
       
    return 0;
}

void *runner(void *t_info) {
    threadData threadinfo = *(threadData*) t_info;
    int threadLocation = threadinfo.threadNumber * threadinfo.partitionBounds;
    char currentChar = buffer[threadLocation];

    for (int i = 0; threadLocation < BUFFER_LENGTH && i < threadinfo.partitionBounds; i++) {
        currentChar = buffer[threadLocation++];
        asciiTable[threadinfo.threadNumber][currentChar]++;
    }
    
    pthread_exit(NULL);
}

double Seconds(void) {
    return (double)clock()/CLOCKS_PER_SEC;
}
