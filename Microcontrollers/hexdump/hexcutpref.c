#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
    if(argc < 3 || argc > 4){
        printf("./hexcutpref <filepath> <cut to addr> [<hex end>]\n");
    }

    char* buf = malloc(4096);
    unsigned long int hex_start = strtol(argv[2], NULL, 16);
    unsigned long int hex_end = 0;
    unsigned long int totalBytes = 0xFFFFFFFFFFFFFFFF;
    if(argc == 4){
        hex_end = strtol(argv[3], NULL, 16);
        totalBytes = hex_end - hex_start;
    }
    short int readB; 


    int filerd, filewr;
    if((filerd = open(argv[1], O_RDONLY)) == -1){
        fprintf(stderr, "error: %s\n", strerror(errno));
        exit(1);
    }

    char* outputFile = malloc(200);
    strcpy(outputFile, argv[1]);
    strcat(outputFile, ".modified");

    printf("Output file name is %s\n", outputFile);

    if((filewr = open(outputFile, O_WRONLY | O_CREAT, 0644)) == -1){
        fprintf(stderr, "error: %s\n", strerror(errno));
        exit(1);
    }

    lseek(filerd, hex_start, SEEK_SET);

    while((readB = read(filerd, buf, 4096)) != 0){
        if(readB > totalBytes){
            readB = totalBytes;
        }
        if(write(filewr, buf, readB) == -1){
            fprintf(stderr, "error: %s\n", strerror(errno));
            exit(1);
        }
        totalBytes -= 4096;
    }

}