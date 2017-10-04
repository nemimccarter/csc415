// Nehemya McCarter-Ribakoff
// Yue
// CSC 415 MW 4:10 PM
// HW1: Hello World
// 4 October 2017

/* NOTES: each thread gets its own array
*         to count ASCII instances. Sum
*         the instances of each into a new
*         array after every thread is done
*/

#include <stdio.h>
#define NUM_THREADS 8

// global 64KB array buffer
char buffer[65536];

int main(int argc, char *argv[]) {
FILE *filePointer;
char 
filePointer = fopen(argv, "r");
if (!filePointer) {
    printf("Error: Cannot open file. Exiting.\n";
    exit(1);
}

while (!feof(filePointer)) {
    buffer = fread( , ,filePointer);
}

    return 0;
}
