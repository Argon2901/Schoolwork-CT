#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int countWords(int, int, int);

int childNumber;

int main(int argc, char** argv){
    if(argc < 3){
        printf("[name] pathname children\n");
        exit(1);
    }
    int fd;
    if(!(fd = open(argv[1], O_RDONLY))){
        printf("File not found\n");
        exit(1);
    }
    int filelength = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    //printf("file length: %d\n", filelength);

    int childCount = atoi(argv[2]);

    int pipes[2];
    if(pipe(pipes)){
        printf("Pipe failed to create\n");
        exit(1);
    }

    int high, low;

    int sum = 0;


    for(int i = 0; i < childCount - 1; i++){
        low = (filelength / childCount * i);
        high = (filelength / childCount * (i + 1));
        childNumber = i;
        if(fork() == 0){//child process
            close(pipes[0]);
            int temp = countWords(fd, low, high);
            write(pipes[1], &temp, 4);
            //printf("child %d exiting with %d counted\n", childNumber, temp);
            exit(0);
        }//parent does nothing
    }
    if(fork() == 0){
        childNumber++;
        close(pipes[0]);
        int temp = countWords(fd, high, filelength); //to ensure no integer division loss
        write(pipes[1], &temp, 4);
        //printf("child %d exiting with %d counted\n", childNumber, temp);
        exit(0);
    }


    close(pipes[1]);
    int temp;
    
    while(read(pipes[0], &temp, 4)){
        //printf("temp = %d\n", temp);
        sum += temp;
    } //should only exit when all children have exited and their pipes close

    //sum = sum - (childCount - 1); //adjustment due to double counting of words

    /*if(childCount > sum){
        printf("Please don't put more children than there are words.\n");
        exit(1);
    }*/
    printf("File has %d words\n", sum);
}

int countWords(int file, int low, int high){
    char* text = malloc(high - low + 10);
    int count = 0;
    lseek(file, low, SEEK_SET);

    unsigned int length = read(file, text, high - low + 1); //extra read in case ends in space and next starts on a letter
    char isWord = 0;
    if(!(text[0] == ' ' || text[0] == '\n')){
        if(childNumber == 0){

        } else{
            isWord = 1;
        }
    } 


    //printf("child %d has text block \"%s\"", childNumber, text);

    for(int i = 0; i < length - 1; i++){
        if(isWord){
            if(text[i] == ' ' || text[i] == '\n'){
                isWord = 0;
            }
            continue;
        } else{
            if(text[i] == ' ' || text[i] == '\n'){

            } else{
                isWord = 1;
                count += 1;
            }
        }
    }
    if((text[length - 2] == ' ' || text[length - 2] == '\n') && !(text[length - 1] == ' ' || text[length - 1] == '\n')){ //in the case of ending on a space and next is a letter
        count += 1;
    }

    return count;
}