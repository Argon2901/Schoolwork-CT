/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 10/04/2023 1 day late                     */
/*  PROGRAM ASSIGNMENT 2                                 */
/*  FILE NAME : main.c                                   */
/*  PROGRAM PURPOSE :                                    */
/*      Creates a shared memory to be used by children.  */
/*      Calls child processes "merge" and "qsort" using  */
/*      fork and execvp.                                 */
/*-------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "shared.h"

void readInput(struct Data*);
void inputIntoShmem(int*, struct Data*);


/*-------------------------------------------------------*/
/* FUNCTION  main :                                      */
/*      Creates shared memory segment. Calls programs    */
/*      merge and qsort with shared memory id.           */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      readInput()                                      */
/*      inputIntoShmem()                                 */
/*      dumpShmem()                                      */
/*      print()                                          */
/*-------------------------------------------------------*/
int main(){
    struct Data data;
    readInput(&data);


    key_t key = ftok("./", 'h');

    printf("*** MAIN: shared memory key: %d\n", key);

    int size = sizeof(int) * 4 + data.a_size + data.x_size + data.y_size + data.f_size;
    int flags = IPC_CREAT | 0666;
    int shmid;

    shmid = shmget(key, size, flags);
    printf("*** MAIN: shared memory created\n");

    int* shmem = (int*)shmat(shmid, NULL, 0);

    if(shmem < 0){
        fprintf(stderr, "shmem creation failure\n");
        exit(1);
    }

    printf("*** MAIN: Shared memory attached\n");



    inputIntoShmem(shmem, &data);
    printf("\n");
    dumpShmem(shmem, 0);
   // print("\n");

    printf("MAIN: About to spawn process for merge\n");
    //merge call
    if(!fork()){
        //print("fork successful\n");
        char** argv = (char**)malloc(sizeof(char*) * 3);


        //print("key main: %d\n", key);
        //print("shmid main: %d\n", shmid);

        argv[0] = "./merge\0";
        argv[1] = (char*)malloc(20);
        sprintf(argv[1], "%d\0", shmid);
        argv[2] = NULL;

        execvp(argv[0], argv);
        fprintf(stderr, "merge execvp unsuccessful\n");
        exit(1);
    }

    print("MAIN: About to spawn process for qsort\n");
    //qsort call
    if(!fork()){
        char** argv = (char**)malloc(sizeof(char*) * 3);

        argv[0] = "./qsort\0";
        argv[1] = (char*)malloc(20);
        sprintf(argv[1], "%d\0", shmid);
        argv[2] = NULL;

        execvp(argv[0], argv);
        fprintf(stderr, "qsort execvp unsuccessful\n");
        exit(1);      
    }
    
    wait(NULL);
    wait(NULL);

    int* a = shmem + 4;
    int* f = shmem + 4 + shmem[0] + shmem[1] + shmem[2];
    int a_size = shmem[0];
    int f_size = shmem[3];

    printf("*** MAIN: sorted array by qsort:\n");
    for(int i = 0; i < a_size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("*** MAIN: merged array:\n");
    for(int i = 0; i < f_size; i++){
        printf("%d ", f[i]);
    }
    printf("\n");


    free(data.a);
    free(data.x);
    free(data.y);
    free(data.finalMerge);

    shmdt(shmem);
    printf("MAIN: shared memory successfully detatched\n");

    shmctl(shmid, IPC_RMID, NULL);
    printf("MAIN: shared memory successfully removed\n");

    return 0;
}   

/*-------------------------------------------------------*/
/* FUNCTION  readInput :                                 */
/*      Reads input from stdin into a buffer struct.     */
/* PARAMETER USAGE :                                     */
/*      data: buffer struct to hold data                 */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void readInput(struct Data* data){
    scanf("%d", &data->a_size);
    data->a = (int*)malloc(sizeof(int) * data->a_size);
    for(int i = 0; i < data->a_size; i++){
        scanf("%d", data->a + i);
    }

    scanf("%d", &data->x_size);
    data->x = (int*)malloc(sizeof(int) * data->x_size);
    for(int i = 0; i < data->x_size; i++){
        scanf("%d", data->x + i);
    }

    scanf("%d", &data->y_size);
    data->y = (int*)malloc(sizeof(int) * data->y_size);
    for(int i = 0; i < data->y_size; i++){
        scanf("%d", data->y + i);
    }

    data->f_size = data->x_size + data->y_size;

    data->finalMerge = (int*)calloc(sizeof(int) * (data->x_size + data->y_size), sizeof(int) * (data->x_size + data->y_size));
}


/*-------------------------------------------------------*/
/* FUNCTION  inputIntoShmem :                            */
/*      Inserts buffer data struct into shared memory.   */
/*      Data structure follows as such:                  */
/*      [a_size]-[x_size]-[y_size]-[f_size]-[a_arr]-     */
/*          -[x_arr]-[y_arr]-[f_arr]                     */
/* PARAMETER USAGE :                                     */
/*      shmem: pointer to shared memory                  */
/*      data: pointer to data buffer struct              */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void inputIntoShmem(int* shmem, struct Data* data){
    int shmemIndex = 0;

    //printf("data f_size = ")
    
    shmem[0] = data->a_size;
    shmem[1] = data->x_size;
    shmem[2] = data->y_size;
    shmem[3] = data->f_size;
    shmemIndex = 4;

    for(int i = 0; i < data->a_size; i++){
        shmem[shmemIndex] = data->a[i];
        shmemIndex++;
    }
    for(int i = 0; i < data->x_size; i++){
        shmem[shmemIndex] = data->x[i];
        shmemIndex++;
    }
    for(int i = 0; i < data->y_size; i++){
        shmem[shmemIndex] = data->y[i];
        shmemIndex++;
    }
}