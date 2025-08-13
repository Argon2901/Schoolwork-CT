// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 10/16/2023
// PROGRAM ASSIGNMENT 3
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
// Implements overloaded functions for the PrefixThread, a
// child class of Thread.
// --------------------------------------------------------

#include "ThreadClass.h"
#include "thread.h"

extern int** B;
extern int B_length;
extern int B_index;

// --------------------------------------------------------
//  FUNCTION  PrefixThread :                                      
//       Constructor for thread child class PrefixThread.
//  PARAMETER USAGE :   
//       int  index: index in array B[a] which it writes to
//       int offset: prefix offset to determine which index
//                   B[a - 1][index] is added to, such that 
//                   B[a][index] = B[a-1][index] 
//                                 + B[a-1][index - offset]
//  FUNCTION CALLED :                                     
// --------------------------------------------------------
PrefixThread::PrefixThread(int index, int offset ){
    this->index = index;
    this->offset = offset;
}

// --------------------------------------------------------
//  FUNCTION  ThreadFunc :                                      
//       Overloaded inhereted function from Thread.
//       Calculates prefix from index and offset in B and 
//       writes it back to its own independent index in B.
//  PARAMETER USAGE :                                     
//  FUNCTION CALLED :                                     
// --------------------------------------------------------
void PrefixThread::ThreadFunc(){
    char* buffer = (char*)malloc(200);
    int length;
    length = sprintf(buffer, "\tThread %d created\n", index);
    write(1, buffer, length);  

    if(index - offset < 0){
        length = sprintf(buffer, "\tThread %d copies x[%d]\n", index, index);
        write(1, buffer, length);  

        B[B_index][index] = B[B_index - 1][index];
    } else{
        length = sprintf(buffer, "\tThread %d computes x[%d] + x[%d]\n", index, index - offset);
        write(1, buffer, length);  

        B[B_index][index] = B[B_index - 1][index] + B[B_index - 1][index - offset];
    }

    length = sprintf(buffer, "\tThread %d Exits\n", index);
    write(1, buffer, length);  
    free(buffer);   
    Exit();
}