#include "rp_client.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 3){
        write(2, "./rp_user1 hostname port remote_file local_file\n", 48);
        exit(1);
    }
    //printf("trying to connect\n");
    int r = rp_connect(argv[1], atoi(argv[2]));
    //printf("connected, r = %d errno = %s\n", r, strerror(errno));
    int serverfd = rp_open(argv[3], O_RDONLY);
    //printf("opened file, errno = %s\n", strerror(errno));
    int myfd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
    char* buffer = (char*)malloc(sizeof(char) * 4096);
    ssize_t size;

    //printf("about to read, errno = %s\n", strerror(errno));
    while((size = rp_read(serverfd, buffer, 4096))){
        //printf("read\n");
        write(myfd, buffer, size);
    }
    
    rp_close(serverfd);
    close(myfd);
    free(buffer);
    return 0;
}
