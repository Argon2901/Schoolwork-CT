/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 10/04/2023 1 day late                     */
/*  PROGRAM ASSIGNMENT 2                                 */
/*  FILE NAME : shared.h                                 */
/*  PROGRAM PURPOSE :                                    */
/*      Provides extra utility to each .c file allowing  */
/*      better code reuse. Includes data buffer struct.  */
/*-------------------------------------------------------*/


#include<stdarg.h>

/*-------------------------------------------------------*/
/* Data buffer struct.                                   */
/* Deprecated.                                           */
/*-------------------------------------------------------*/
struct Data{

    int a_size, x_size, y_size, f_size;

    int* a;
    int *x;
    int *y;

    int* finalMerge;
};


/*-------------------------------------------------------*/
/* FUNCTION  dumpData :                                  */
/*      Dumps struct Data to stdout.                     */
/* PARAMETER USAGE :                                     */
/*      data: pointer to struct to be printed            */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void dumpData(struct Data* data){
    printf("starting dump\n");

    printf("size : %d a: ", data->a_size);
    for(int i = 0; i < data->a_size; i++){
        printf("%d ", data->a[i]);
    }
    printf("\n");

    printf("size : %d x: ", data->x_size);
    for(int i = 0; i < data->x_size; i++){
        printf("%d ", data->x[i]);
    }
    printf("\n");

    printf("size : %d y: ", data->y_size);
    for(int i = 0; i < data->y_size; i++){
        printf("%d ", data->y[i]);
    }
    printf("\n");

    printf("size : %d final: ", data->f_size);
    for(int i = 0; i < data->f_size; i++){
        printf("%d ", data->finalMerge[i]);
    }
    printf("\n");
}


/*-------------------------------------------------------*/
/* FUNCTION  dupmShmem :                                 */
/*      Dumps shared memory segment data structure to    */
/*      stdout.                                          */
/* PARAMETER USAGE :                                     */
/*      shmem: shared memory segment to be dumped        */
/*      f:     deprecated flag                           */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void dumpShmem(int* shmem, char f){
    int a = shmem[0];
    int x = shmem[1];
    int y = shmem[2];
    //int f = shmem[3];
    int shmemIndex = 4;
    if(f){
        f = 0; 
    }

    if(!f){

        printf("Input array for qsort has %d elements:\n", a);
        for(int i = 0; i < a; i++){
            printf("%d ", shmem[shmemIndex]);
            shmemIndex++;
        } 
        printf("\n");

        printf("Input array x[] for merge has %d elements: \n", x);
        for(int i = 0; i < x; i++){
            printf("%d ", shmem[shmemIndex]);
            shmemIndex++;
        } 
        printf("\n");

        printf("Input array y[] for merge has %d elements: \n", y);
        for(int i = 0; i < y; i++){
            printf("%d ", shmem[shmemIndex]);
            shmemIndex++;
        }   
        printf("\n");
    }/*else{
        printf("printing f size: %d\n", f);
        for(int i = 0; i < f; i++){
            printf("%d ", shmem[shmemIndex]);
            shmemIndex++;
        } 
        printf("\n");
    }*/
    return;
}


/*-------------------------------------------------------*/
/* FUNCTION  print :                                     */
/*      Atomic printf equivalent.                        */
/* PARAMETER USAGE :                                     */
/*      format: string format used in vsprintf           */
/*      ...: variadric input to fill in format           */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void print(char* format, ...){
    va_list list;
    va_start(list, format);
    char* buffer = (char*)malloc(200);
    vsprintf(buffer, format, list);
    write(1, buffer, 200);
}