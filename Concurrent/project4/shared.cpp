// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/08/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME : shared.cpp
// PROGRAM PURPOSE :
// Implements the functions declared in shared.h
// --------------------------------------------------------

#include "shared.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


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
    int length = vsprintf(buffer, format, list);
    write(1, buffer, length);
}