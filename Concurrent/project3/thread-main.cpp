// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 10/16/2023
// PROGRAM ASSIGNMENT 3
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
// Main program that recieves data from stdin, inserts it 
// into global arrays, creates threads to compute data, and
// prints output. 
// --------------------------------------------------------


#include "ThreadClass.h"
#include "thread.h"
#include <stdio.h>
#include <math.h>

int** B;
int B_length;
int B_index = 1;

void printArr(int, int*);

// --------------------------------------------------------
//  FUNCTION  main :                                      
//       Gets file input and creates threads to process it.
//       Outputs results to stdout. 
//  PARAMETER USAGE :                                     
//  FUNCTION CALLED :                                     
//       Begin()
//       printArr()                   
// --------------------------------------------------------
int main(){

    int* x;
    int x_length;
    int cap;


    scanf("%d", &x_length);
    B_length = x_length;

    x = (int*) malloc(sizeof(int) * x_length);

    //inserting data into tempArray
    for(int i = 0; i < x_length; i++){
        scanf("%d", x + i);
    }

    printf("Number of input data = %d\n", x_length);
    printf("Input array: \n");
    printf("\t");
    printArr(x_length, x);
    printf("\n");

    //creating and assigning memory space into global memory
    B = (int**)malloc(sizeof(int*) * x_length); //too much data assigned, define cap earlier and set to that
    for(int i = 0; i < x_length; i++){
        B[i] = (int*)malloc(sizeof(int) * x_length);
    }
    //printf("initialized space for B\n");

    for(int i = 0; i < x_length; i++){
        B[0][i] = x[i];
    }


    //calculating how many runs will happen
    cap = log(x_length) / log(2) + 1;
    PrefixThread** threads = (PrefixThread**)malloc(sizeof(PrefixThread**) * B_length);


    //Creation and deletion of threads which process data 
    int j;
    for(j = 1, B_index = 1; B_index < cap; j = j * 2){
        printf("Run %d:\n", B_index);
        
        for(int i = 0; i < B_length; i++){
            threads[i] = new PrefixThread(i, j);
            threads[i]->Begin();
        }

        for(int i = 0; i < B_length; i++){
            threads[i]->Join();
            delete threads[i];
        }

        printf("Results after run %d:\n", B_index);
        printf("\t");
        printArr(B_length, B[B_index]);
        printf("\n");

        B_index++;
    }
    B_index--;

    printf("Final result after run %d:\n", B_index);
    printf("\t");
    printArr(B_length, B[B_index]);
    printf("\n");   
}


// --------------------------------------------------------
//  FUNCTION  printArr :                                      
//       Prints an integer array of length n 
//  PARAMETER USAGE :                       
//       int  n: length of array a 
//       int* a: array to be printed 
//  FUNCTION CALLED :                
// --------------------------------------------------------
void printArr(int n, int* a){
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
}