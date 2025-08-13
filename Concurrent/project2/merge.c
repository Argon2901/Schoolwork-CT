/*--------------------------------------------------------*/
/*  NAME : Collin Thompson               USER ID : collint*/
/*  DUE DATE : 10/04/2023 1 day late                      */
/*  PROGRAM ASSIGNMENT 2                                  */
/*  FILE NAME : merge.c                                   */
/*  PROGRAM PURPOSE :                                     */
/*      Merges two arrays given to it through shared      */
/*      memory created by some parent process.            */
/*      Algorithm achieved through binary search and fork.*/
/*      Routes output to empty space in shared memory.    */
/*--------------------------------------------------------*/


#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shared.h"

int binarySearch(int*, int, int);


/*--------------------------------------------------------*/
/* FUNCTION  main :                                       */
/*      Attaches to shared memory. Merges arrays x[] and  */
/*      y[] into array f[] in shared memory.              */
/* PARAMETER USAGE :                                      */
/*      argc: the count of the number of line args.       */
/*      argv: line arguments                              */
/*          argv[1] = shmid                               */
/* FUNCTION CALLED :                                      */
/*      print()                                           */
/*      binarySearch()                                    */
/*--------------------------------------------------------*/
int main(int argc, char* argv[]){
    int shmid = atoi(argv[1]);
    int* shmem = NULL;
    shmem = (int*)shmat(shmid, NULL, 0);
    
    //extracting arrays out of shared memory data
    int* x = shmem + 4 + shmem[0];
    int* y = shmem + 4 + shmem[0] + shmem[1];
    int* f = shmem + 4 + shmem[0] + shmem[1] + shmem[2];
    int x_size = shmem[1];
    int y_size = shmem[2];
    int f_size = shmem[3];


    pid_t ypid;
    pid_t xpid;
    //x fork
    if(!(xpid = fork())){
        
        for(int i = 0; i < x_size; i++){
            if(!fork()){
                print("$$$ M-PROC(%d): handling x[%d] = %d", getpid(), i, x[i]);
                int k = binarySearch(y, y_size, x[i]);

                if(k == 0){
                    print("$$$ M-PROC(%d): x[%d] = %d is found to be smaller than y[%d] = %d", getpid(), i, x[i], 0, y[0]);
                } else if(k == y_size){
                    print("$$$ M-PROC(%d): x[%d] = %d is found to be larger than y[%d] = %d", getpid(), i, x[i], y_size - 1, y[y_size - 1]);
                } else{
                    print("$$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d", getpid(), i, x[i], k, y[k], k - 1, y[k]);
                }

                print("$$$ M-PROC(%d): about to write x[%d] = %d into position %d of the output array", i, x[i], i + k);
                f[k + i] = x[i];
                exit(0);
            }
        }

        for(int i = 0; i < x_size; i++){
            wait(NULL);
        }
        exit(0);
    }

    //y fork
    if(!(ypid = fork())){
        for(int i = 0; i < y_size; i++){
            if(!fork()){
                print("$$$ M-PROC(%d): handling y[%d] = %d", getpid(), i, y[i]);
                int k = binarySearch(x, x_size, y[i]);

                if(k == 0){
                    print("$$$ M-PROC(%d): y[%d] = %d is found to be smaller than x[%d] = %d", getpid(), i, y[i], 0, x[0]);
                } else if(k == y_size){
                    print("$$$ M-PROC(%d): y[%d] = %d is found to be larger than x[%d] = %d", getpid(), i, y[i], x_size - 1, x[x_size - 1]);
                } else{
                    print("$$$ M-PROC(%d): y[%d] = %d is found between x[%d] = %d and x[%d] = %d", getpid(), i, y[i], k, x[k], k - 1, x[k]);
                }

                print("$$$ M-PROC(%d): about to write y[%d] = %d into position %d of the output array", i, y[i], i + k);

                f[k + i] = y[i];
                exit(0);
            }        
        }

        for(int i = 0; i < y_size; i++){
            wait(NULL);
        }
        exit(0);
    }

    waitpid(xpid, NULL, 0);
    waitpid(ypid, NULL, 0);
    //print("merge ended\n");

    shmdt(shmem);
}

/*--------------------------------------------------------*/
/* FUNCTION  binarySarch :                                */
/*      Finds the location the value should be in sorted  */
/*      array arr.                                        */
/* PARAMETER USAGE :                                      */
/*      arr:    array to be checked against               */
/*      s:      size of arr                               */
/*      value:  integer to be checked against arr         */
/* FUNCTION CALLED :                                      */
/*--------------------------------------------------------*/
int binarySearch(int *arr, int s, int value){
    int lb = 0, ub = s;
    int c;
    while(ub > lb){
        c = (ub - lb) / 2 + lb; 
        if(arr[c] < value){
            lb = c + 1;
        } else{
            ub = c;
        }
    }
    return lb; 
}