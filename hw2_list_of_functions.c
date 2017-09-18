// Nehemya McCarter-Ribakoff
// Yue
// CSC 415 MW 4:10 PM
// HW1: Hello World
// 20 September 2017

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*** TODO: rename "functionlist.c" before submitting ***/
int main () {

    char* inputString = calloc(1,1);
    const int maxCharInput = 3;
    pid_t pid;

    /* for case 1 */
    char str[20];
    const int td = 1; 
    char* buf = str;
    size_t count;
 
    do {
        printf("\n1. Hello World!\n2. List files");
        printf("\n3. Exit\nPlease select: ");
        
        fgets(inputString, maxCharInput, stdin);

        switch (atoi(inputString)) { 
            case 1:
                pid = fork();
                if (pid == 0) {
                    count = sprintf(str, "hello world!\n");
                    write(1, str, count);
                    exit(0);
                } else if (pid < 0) {  /* error */
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                } else { /* parent process */
                    wait(NULL);
                }
                break;

            case 2:
                pid = fork();
                if (pid == 0) {
                    execlp("/bin/ls", "ls", NULL);
                    exit(0);
                } else if (pid < 0) { /* error */
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                } else { /* parent process */
                    wait(NULL);
                }
                break;

            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (1);

    return 0;
}
