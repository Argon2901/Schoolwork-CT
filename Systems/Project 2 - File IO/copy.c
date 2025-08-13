#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void checksum(int*, int);
void recieveInputs(int, char**, char**, char**, int*);

int main(int argc, char* argv[]){
    char* infile;
    char* outfile;
    int blocksize; 
    recieveInputs(argc, argv, &infile, &outfile, &blocksize);

    int* block = (int*)malloc(blocksize);
    int fd_in;
    int fd_out;
    int eof = 1; 

    fd_in = open(infile, O_RDONLY);
    fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);


    while(1){
        eof = read(fd_in, block, blocksize);

        
        if(eof < blocksize){
            for(int i = eof; i < blocksize; i++){
                ((char*)block)[i] = 0;
            }

            checksum(block, blocksize);
            write(fd_out, block, eof);
            break;
        }

        checksum(block, blocksize);
        write(fd_out, block, blocksize);
    }

    close(fd_in);
    close(fd_out);
    free(block);
}

void checksum(int* block, int blocksize){
    int sum = 0;
    for(int i = 0; i < blocksize / 4; i++){
        sum = sum ^ block[i];
    }
    char* buff = (char*)malloc(9);
    sprintf(buff, "%08x ", sum);
    write(1, buff, 9);
    free(buff);    
}

void recieveInputs(int argc, char* argv[], char** infile, char** outfile, int* blocksize){
    char* buff = (char*)malloc(1000);

    if(argc < 3){
        sprintf(buff, "Not Enough Arguments\n");
        write(2, buff, 1000);
        exit(1); 
    }

    *infile = argv[1];
    *outfile = argv[2];
    if(argc < 4){
        *blocksize = 1024;
    } else{
        *blocksize = atoi(argv[3]);
        if(*blocksize % 4){
            sprintf(buff, "Blocksize must be a multiple of 4\n");
            write(2, buff, 1000);
            *blocksize = *blocksize + (4 - (*blocksize % 4));

        }
    }
    free(buff);
}