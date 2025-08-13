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
    int serverfd = rp_open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);

    int myfd = open(argv[3], O_RDONLY);
    char* buffer = (char*)malloc(sizeof(char) * 4096);
    ssize_t size;
    rp_lseek(serverfd, 10, SEEK_SET);
    
    while((size = read(myfd, buffer, 4096))){
        rp_write(serverfd, buffer, size);
    }

    rp_close(serverfd);

    serverfd = rp_open(argv[3], O_RDONLY);
    int checksum = rp_checksum(serverfd);
    printf("checksum = %d\n", checksum);
    rp_close(serverfd);

    close(myfd);
    free(buffer);
    return 0;
}