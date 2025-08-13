#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

#include <errno.h>
#include <error.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "rp_calls.h"


static int sock_fd = 0;

/*************************************************************************/
//                                                                       //
//     read_from_server(): reads next packet of data                     //
//                         and returns pointer to the                    //
//                         data read                                     //
//                                                                       //
//     Calling Convention:                                               //
//                                                                       //
//              1. Reading an integer:                                   //
//                                                                       //
//                      int var = *(int*) read_from_server();            //
//                                                                       //
//              2. Reading a string:                                     //
//                                                                       //
//                      char *string = read_from_server();               //
//                                                                       //
//     How it works:                                                     //
//                                                                       //
//              The communication for this assignment is                 //
//              abstracted to the following:                             //
//                                                                       //
//                      Any data sent across the network                 //
//                      is preceeded by a fixed size packet              //
//                      indicating the size of the data                  //
//                      contained in the subsequent packet               //
//                                                                       //
//              Ex 1:                                                    //
//                      Sending an integer is done like so:              //
//                                                                       //
//                      client --> [size of int] --> server              //
//                      client --> [integer value] --> server            //
//                                                                       //
//              Ex 2:                                                    //
//                                                                       //
//                      Sending a string is done like so:                //
//                                                                       //
//                      client --> [length of string] --> server         //
//                      client --> [string data] --> server              //
//                                                                       //
/*************************************************************************/

void* read_from_server(){
    size_t size;
    char *buf;
    int rtrn; 

    if((rtrn = read(sock_fd, &size, sizeof(size))) < 1) {
        if(rtrn == -1) {
            perror("read_from_server read 1");
            exit(-1);
        }
        return NULL;
    }

    size = ntohl(size);
    
    buf = malloc(size);
    if((rtrn = read(sock_fd, buf, size)) < 1) {
        if(rtrn == -1) {
            perror("read_from_server read 2");
            exit(-1);
        }
        return NULL;
    }
    return buf;
}

/*************************************************************************/
//                                                                       //
//     send_to_server(): sends data to the server by sending             //
//                       a packet containing the size of the             //
//                       data being sent prior to the data itself        //
//                                                                       //
//     Calling Convention:                                               //
//                                                                       //
//              1. Sending an integer:                                   //
//                                                                       //
//                      int my_int = 5;                                  //
//                      send_to_server(&my_int, sizeof(my_int);          //
//                                                                       //
//              2. Sending a string:                                     //
//                                                                       //
//                      char string[] = "some string";                   //
//                      send_to_server(string, strlen(string));          //
//                                                                       //
/*************************************************************************/

int send_to_server(void *data, size_t size){
   
    size_t nb_size = htonl(size);
    
    if(write(sock_fd, &nb_size, sizeof(size)) == -1)
        return -1;

    return write(sock_fd, data, size);

}



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
//                                                                       //
//             YOU MUST IMPLEMENT THE FOLLOWING FUNCTIONS                //
//                                                                       //
//                  |               |               |                    //
//                  |               |               |                    //
//                  |               |               |                    //
//                \ | /           \ | /           \ | /                  //
//                 \|/             \|/             \|/                   //
//                  V               V               V                    //
//                                                                       //
//                                                                       //
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/


/*************************/
//      RP_CONNECT       //
/*************************/

int rp_connect(const char *address, unsigned short port){

    /************************************/
    //         PART 2 OF PROJECT        //                                    
    /************************************/
    
    struct sockaddr_in server_addr;
    struct hostent *host;
    


    host = gethostbyname(address);
    if(!host){
        write(2,"Invalid host address\n", 21);
        exit(h_errno);
    }

    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = (short)AF_INET;
    server_addr.sin_port = htons(port);
    bcopy(host->h_addr, (char *)&server_addr.sin_addr,
		host->h_length);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    return connect(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
}


/*************************/
//        RP_OPEN        //
/*************************/

int rp_open(const char *pathname, int flags, ...) {

    va_list arg_list;

    va_start(arg_list, flags);

    mode_t mode;

    // Check if there will be a mode passed
    // This can be done by chekcing the flags to see if O_CREAT is speacified
    if(flags & O_CREAT){
        mode = va_arg(arg_list, mode_t);
    }

    va_end(arg_list);

    // Send type of call to server
    int call = OPEN_CALL;
    send_to_server(&call, sizeof(int));
    //printf("sent call to server\n");
    // Send each argument to the server (pathname, flags, mode)
    send_to_server(pathname, strlen(pathname));
    send_to_server(&flags, sizeof(int));
    send_to_server(&mode, sizeof(mode_t));
    //printf("sent args to server\n");
    // Read return of open coming back from server 
    int* r = (int*)read_from_server();
    int fd = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);
    // Return the return of open
    return fd;
}


/*************************/
//        RP_CLOSE       //
/*************************/

int rp_close(int fd){
    
    // Send type of call to server
    int call = CLOSE_CALL;
    send_to_server(&call, sizeof(int));
    // Send each argument to the server
    send_to_server(&fd, sizeof(int));
    // Read return of close coming back from server 
    int* r = (int*)read_from_server();
    int ret = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);
    // Return result
    return ret;
}


/*************************/
//        RP_READ        //
/*************************/

ssize_t rp_read(int fd, void *buf, size_t count) {
    
    /************************************/
    //         PART 2 OF PROJECT        //                                    
    /************************************/
    
    // Send type of call to server
    int call = READ_CALL;
    send_to_server(&call, sizeof(int));
    // Send each argument to the server
    send_to_server(&fd, sizeof(int));
    send_to_server(buf, count);
    send_to_server(&count, sizeof(size_t));
    // Read return of read coming back from server 
    ssize_t* r = (ssize_t*)read_from_server();
    ssize_t ret = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);

    char* newbuf = (char*)read_from_server(); 
    bcopy(newbuf, buf, ret);
    free(newbuf);
    // Return result
    return ret;
}


/*************************/
//       RP_WRITE        //
/*************************/

ssize_t rp_write(int fd, const void *buf, size_t count) {
    
    /************************************/
    //         PART 2 OF PROJECT        //                                    
    /************************************/
    
    // Send type of call to server
    int call = WRITE_CALL;
    send_to_server(&call, sizeof(int));
    // Send each argument to the server
    send_to_server(&fd, sizeof(int));
    send_to_server(buf, count);
    send_to_server(&count, sizeof(int));
    // Read return of write coming back from server 
    ssize_t* r = (ssize_t*)read_from_server();
    ssize_t ret = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);
    // Return result
    return ret;
}


/*************************/
//       RP_LSEEK        //
/*************************/

off_t rp_lseek(int fd, off_t offset, int whence) {
    
    /************************************/
    //         PART 2 OF PROJECT        //                                    
    /************************************/
    
    // Send type of call to server
    int call = LSEEK_CALL;
    send_to_server(&call, sizeof(int));
    // Send each argument to the server
    send_to_server(&fd, sizeof(int));
    send_to_server(&offset, sizeof(off_t));
    send_to_server(&whence, sizeof(int));
    // Read return of lseek coming back from server
    off_t* r = (off_t*)read_from_server();
    off_t ret = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);
    // Return result
    return ret;
}


/*************************/
//      RP_CHECKSUM      //
/*************************/

short rp_checksum(int fd) {
   
    /************************************/
    //         PART 2 OF PROJECT        //                                    
    /************************************/

   
    
    // Send type of call to server
    int call = CHECKSUM_CALL;
    send_to_server(&call, sizeof(int));
    // Send each argument to the server
    send_to_server(&fd, sizeof(int));
    // Read return of checksum coming back from server 
    short* r = (short*)read_from_server();
    short ret = *r;
    free(r);
    // Read errno sent from server
    int* errnov = (int*)read_from_server();
    errno = *errnov;
    free(errnov);  
    // Return result
    return ret;  
}
