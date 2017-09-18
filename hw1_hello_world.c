// Nehemya McCarter-Ribakoff
// Yue
// CSC 415 MW 4:10 PM
// HW1: Hello World
// 13 September 2017

#include <unistd.h>
#include <stdio.h>

int main() {
    char str[100];
    int td = 1; 
    char* buf = str;
    size_t count = sprintf(str, "hello world!\n");
    
    write(1, str, count);

    return 0;

}
