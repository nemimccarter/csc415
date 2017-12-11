/* Nehemya McCarter-Ribakoff *
 * Yue                       *
 * CSC415 M/W 4:10PM         *
 * 11 December 2017          *
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

// 1. accept two filenames as command-line arguments: the first an existing filename, the second the name of the copy
int main(int argc, char *argv[]) {
    const char *sourceFileName = argv[1];
    const char *destFileName = argv[2];

    const size_t BUFFER_SIZE = 1024;
    char BUFFER[BUFFER_SIZE];

    int sourceFile;
    int destFile;

    ssize_t bytesRead = 0,
            bytesWritten = 0;
    int openStatus = 0,
        closeStatus = 0;

    // 2. Open first file
    sourceFile = open(sourceFileName, O_RDONLY);
    if (sourceFile < 0) {
        printf("Error opening source file: %s\n", strerror(errno));
    return -1;
    }

    // 4. Create second file (exit if filename already exists)
    destFile = open(destFileName, O_CREAT|O_EXCL|O_WRONLY);
    if (destFile < 0) {
        printf("Error opening destination file: %s\n", strerror(errno));
    return -1;
    }
    // 5. Loop through contents of first file, writing to second file, keep track of bytes copied
    bytesRead = read(sourceFile, BUFFER, BUFFER_SIZE);
    if (bytesRead < 0) {
        printf("Error reading from file to buffer: %s\n", strerror(errno));
    return -1;
    }

    bytesWritten = write(destFile, BUFFER, BUFFER_SIZE);
    if (bytesWritten < 0) {
        printf("Error writing to destination file: %s\n", strerror(errno));
    return -1;
        
    } else {
        printf("%d bytes written\n", bytesWritten);
    }

    closeStatus = close(sourceFile);
    if (closeStatus != 0) {
        printf("\nError closing source file: %s\n", strerror(errno));
    return -1;
    }
    closeStatus = close(destFile);
    if (closeStatus != 0) {
        printf("Error closing destination file: %s\n", strerror(errno));
    return -1;
    }

    return 0;
}
