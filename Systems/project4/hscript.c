#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>


void ehandle();





int main(int argc, char* argv[]){
    int inPipe[2];
    int outPipe[2];
    int errPipe[2];

    signal(SIGCHLD, SIG_IGN);

    int childPID; 
    
    char* buffer = (char*)malloc(1024);

    int bLength;

    

    if(argc < 3){
        char* buffer = "not enough arguments\n";
        write(2, buffer, 22);
        exit(1);
    }

    if(mkdir(argv[argc - 1], 0700)){
        ehandle();
        exit(1);
    }


    pipe(inPipe);
    pipe(outPipe);
    pipe(errPipe);


    char* path = (char*) malloc(512);
    sprintf(path, "%s/0", argv[argc - 1]);
    int in = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    sprintf(path, "%s/1", argv[argc - 1]);
    int out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    sprintf(path, "%s/2", argv[argc - 1]);
    int err = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);


    if(!(childPID = fork())){
        close(0);
        close(1);
        close(2);
        
        dup2(inPipe[0], 0);
        dup2(outPipe[1], 1);
        dup2(errPipe[1], 2);

        char** newargv = (char**)malloc(sizeof(char*) * argc - 1);
        for(int i = 1; i < argc - 1; i++){
            newargv[i - 1] = argv[i];
        }

        newargv[argc - 2] = NULL;

        execvp(newargv[0], newargv);
        printf("failed\n");
        ehandle();
        exit(1);
    }

    while(!kill(childPID, 0)){
        int a = 0;
        ioctl(inPipe[1], FIONREAD, &a);
        if(a){
            while(1){

                bLength = read(0, buffer, 1024);
                write(in, buffer, bLength);
                write(inPipe[1], buffer, bLength);

                if(bLength < 1024){
                    write(inPipe[1], buffer, 0);
                    break;
                }
            }
        }

        ioctl(outPipe[0], FIONREAD, &a);
        if(a){
            while(1){
                bLength = read(outPipe[0], buffer, 1024);
                write(out, buffer, bLength);
                write(1, buffer, bLength);

                if(bLength < 1024){
                    break;
                }
            }
        }

        ioctl(errPipe[0], FIONREAD, &a);
        if(a){
            while(1){
                bLength = read(errPipe[0], buffer, 1024);
                write(err, buffer, bLength);
                write(2, buffer, bLength);

                if(bLength < 1024){
                    break;
                }
            }
        }

    }



    close(out);
    close(in);
    close(err);
}

void ehandle(){
    char* buffer = (char*) malloc(512);
    int length;
    switch(errno){
        case ENOEXEC:
            length = sprintf(buffer, "invalid program call\n");
            break;
        case EEXIST:
            length = sprintf(buffer, "directory specified already exists\n");
            break; 
        default:
            length = sprintf(buffer, "errror: %d has occured\n", errno);
    }
    write(2, buffer, length);
}
