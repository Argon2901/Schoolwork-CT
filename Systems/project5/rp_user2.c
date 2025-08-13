#include "rp_client.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 3){
        write(2, "./rp_user2 hostname port remote_file local_file\n", 48);
        exit(1);
    }
    rp_connect(argv[1], atoi(argv[2]));
    int serverfd = rp_open(argv[3], O_RDONLY);
    //printf("connected, errno = %s\n", strerror(errno));
    int myfd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
    //printf("opened file, errno = %s\n", strerror(errno));
    char* buffer = (char*)malloc(sizeof(char) * 4096);
    ssize_t size;
    rp_lseek(serverfd, 10, SEEK_SET);
    
    //printf("about to read, errno = %s\n", strerror(errno));
    while((size = rp_read(serverfd, buffer, 4096))){
        write(myfd, buffer, size);
    }
    
    rp_close(serverfd);
    close(myfd);
    free(buffer);
    return 0;
}