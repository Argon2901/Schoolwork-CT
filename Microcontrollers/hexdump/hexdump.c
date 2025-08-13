#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define RAW_OUTPUT  0x1
#define COMMAS      0x2

const char* instructionMessage = "./hexdump <filepath> [-r: raw, -c: commas, -x: 0x prefix]\n";

char* prefix = "";

int main(int argc, char** argv){
    if(argc < 2 || argc > 3){
        fprintf(stderr, instructionMessage);
        exit(1);
    }

    char flags = 0;
    int file;
    if((file = open(argv[1], O_RDONLY)) == -1){
        fprintf(stderr, "error: %s\n", strerror(errno));
        exit(1);
    }

    if(argc == 3){
        if((strchr(argv[2], 'r'))){
            //printf("raw\n");
            flags |= RAW_OUTPUT;
        }
        
        if((strchr(argv[2], 'c'))){
            //printf("commas\n");
            flags |= COMMAS;
        }

        if((strchr(argv[2], 'x'))){
            prefix = "0x";
        }

        if(flags == 0){
            printf("failure to parse options\n");
            fprintf(stderr, instructionMessage);
            exit(1);
        }
    }

    unsigned char* row = (unsigned char*) malloc(16);
    unsigned long int currentAddress = 0;
    char i, b, remainingLength;

    //TODO: change to read a page into a buffer 4096B
    while((remainingLength = read(file, row, 16)) != 0){ 

        if(remainingLength == -1){
            fprintf(stderr, "error: %s\n", strerror(errno));
            exit(1);
        }

        if(remainingLength < 16){
            for(; remainingLength < 16; remainingLength++){
                row[remainingLength] = 0;
            }
        }

        if(flags & RAW_OUTPUT){

        } else{
            printf("0x%016lX ", currentAddress);
        }

        for(i = 0; i < 16; i++){
            printf(prefix);
            printf("%02X", row[i]);
            if(flags & COMMAS){
                printf(", ");
            } else{
                printf(" ");
            }
        }

        if(flags & RAW_OUTPUT){

        }else{
            printf(" | ");
            for(i = 0; i < 16; i++){
                if((b=row[i]) >= 0x20 && b <= 0x7e ){
                    printf("%c", b);
                } else{
                    printf(".");
                }
            }
        }
        printf("\n");
        currentAddress += 16;
    }
}