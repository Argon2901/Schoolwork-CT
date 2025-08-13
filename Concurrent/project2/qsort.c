/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 10/04/2023 1 day late                     */
/*  PROGRAM ASSIGNMENT 2                                 */
/*  FILE NAME : qsort.c                                  */
/*  PROGRAM PURPOSE :                                    */
/*      Sorts arrays in shared memory using the quicksort*/
/*      algorithm.                                       */
/*-------------------------------------------------------*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shared.h"

int mqsort(int*, int, int);
void qsortCall(int, int, int);
void printArr(int*, int);


/*-------------------------------------------------------*/
/* FUNCTION  main :                                      */
/*      Attaches program to shared memory specified in   */
/*      argv[1]. Calls mqsort and new calls of itself to */
/*      create a recursive quicksort.                    */
/* PARAMETER USAGE :                                     */
/*      argc: the count of the number of line args.      */
/*      argv: line arguments                             */
/*          argv[1] = shmid                              */
/*          argv[2] = lower bound                        */
/*          argv[3] = upper bound                        */
/* FUNCTION CALLED :                                     */
/*      qsortcall()                                      */
/*      print()                                          */
/*      mqsort()                                         */
/*-------------------------------------------------------*/
int main(int argc, char* argv[]){

    //print("entering qsort\n");
    int shmid = atoi(argv[1]);
    int* shmem = NULL;
    shmem = (int*)shmat(shmid, NULL, 0);

    int* a = shmem + 4;
    int a_size = shmem[0];

    //initial call
    if(argc == 2){
        //print("\nentering qsort first time\n\n");
        if(!fork()){
            qsortCall(shmid, a_size - 1, 0);
        }
        wait(NULL);
    
    } else{ //actual process recursive call for qsort

        int lb = atoi(argv[2]);
        int ub = atoi(argv[3]);
        
        print("### Q-PROC(%d): entering with a[%d..%d]\n", getpid(), lb, ub);
        for(int i = lb; i <= ub; i++){
            print("%d ", a[i]);
        }
        print("\n");
        

        if(ub <= lb){
            print("### Q-PROC(%d): section a[%d..%d] sorted", getpid(), lb, ub);
            shmdt(shmem);
            print("### Q-PROC(%d): exits", getpid());
            return 0;
        }
            


        int pivot = mqsort(a, ub, lb);

        if(pivot >= 0){
            if(!fork()){
                qsortCall(shmid, pivot - 1, lb);
            }

            if(!fork()){
                qsortCall(shmid, ub, pivot + 1);
            }
            wait(NULL);
            wait(NULL);

            print("### Q-PROC(%d): section a[%d..%d] sorted", getpid(), lb, ub);
            for(int i = lb; i <= ub; i++){
                print("%d ", a[i]);
            }
            print("\n");
        }

    }


    shmdt(shmem);
    print("### Q-PROC(%d): exits", getpid());
}



/*-------------------------------------------------------*/
/* FUNCTION  printArr :                                  */
/*      debugging array print                            */
/* PARAMETER USAGE :                                     */
/*      arr: array to be printed                         */
/*      s: size of arr                                   */
/* FUNCTION CALLED :                                     */
/*      print()                                          */
/*-------------------------------------------------------*/
void printArr(int* arr, int s){
    for(int i = 0; i < s; i++){
        print("%d ", arr[i]);
    }
    print("\n\n");
}


/*-------------------------------------------------------*/
/* FUNCTION  mqsort :                                    */
/*      Operates quicksort algorithm within bounds       */
/* PARAMETER USAGE :                                     */
/*      arr: Array to be sorted.                         */
/*      ub: Inclusive upper bound index of sorted area.  */
/*      lb: Inclusive lower bound index of sorted area   */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
int mqsort(int* arr, int ub, int lb){
    if(!(ub - lb)){
        return -1;
    }

    int pivotIndex = ub;

    print("Pivot element is a[%d] = %d\n", pivotIndex, arr[pivotIndex]);

    ub = ub - 1;

    while(lb != ub){
        //print("ub: %d lb: %d\n", ub, lb);
        if(arr[lb] <= arr[pivotIndex]){
            lb++;
        } else{
            while(lb != ub){
                //print("ub: %d lb: %d\n", ub, lb);
                if(arr[ub] > arr[pivotIndex]){
                    ub--;
                } else{
                    int temp = arr[ub];
                    arr[ub] = arr[lb];
                    arr[lb] = temp;
                    break;
                }
            }
        }
    }

    if(arr[pivotIndex] > arr[ub]){
        int temp = arr[ub + 1];
        arr[ub + 1] = arr[pivotIndex];
        arr[pivotIndex] = temp;
        pivotIndex = ub + 1;
    } else{
        int temp = arr[ub];
        arr[ub] = arr[pivotIndex];
        arr[pivotIndex] = temp;
        pivotIndex = ub;
    }


    return pivotIndex;
}

/*-------------------------------------------------------*/
/* FUNCTION  qsortCall :                                 */
/*      Prepares and executes a call to run a new        */
/*      instance of qsort.                               */
/* PARAMETER USAGE :                                     */
/*      shmid: the shared memory id                      */
/*      ub: Inclusive upper bound index of sorted area.  */
/*      lb: Inclusive lower bound index of sorted area   */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void qsortCall(int shmid, int ub, int lb){

    //print("entering qsortCall\n");
    char** argv = (char**)malloc(sizeof(char*) * 5);

    argv[0] = "./qsort\0";
    
    argv[1] = (char*)malloc(20);
    sprintf(argv[1], "%d\0", shmid);
    
    argv[2] = (char*)malloc(20);
    sprintf(argv[2], "%d\0", lb);
    
    argv[3] = (char*)malloc(20);
    sprintf(argv[3], "%d\0", ub);
    
    argv[4] = NULL;

    execvp(argv[0], argv);
    fprintf(stderr, "execvp unsuccessful\n");
    exit(1);
}