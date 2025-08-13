// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 10/16/2023
// PROGRAM ASSIGNMENT 3
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Declares a child class of Thread and declares overloads
// of function ThreadFunc.
// --------------------------------------------------------


#ifndef hThread
#define hThread

#include "ThreadClass.h"

class PrefixThread : public Thread{
public:
    PrefixThread(int, int);
private:
    int index;
    int offset;
    void ThreadFunc();
};
#endif