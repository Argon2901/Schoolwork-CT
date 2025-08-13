// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/08/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Declares child classes of Thread for the Mother and 
// Baby threads. 
// --------------------------------------------------------

#ifndef hThread
#define hThread

#include "ThreadClass.h"

extern Semaphore *motherAwake;
extern Semaphore *pots;
extern int numPots;


class MotherThread : public Thread{
public:
    MotherThread(int);
private:
    bool retire = false;
    int totalFeedings;
    int feedingsDone = 0;

    void ThreadFunc();

    void goto_sleep();
    void food_ready();
};

class BabyThread : public Thread{
public:
    BabyThread(int);
private:
    int number;
    void ThreadFunc();

    void ready_to_eat();
    void finished_eating();

};

#endif