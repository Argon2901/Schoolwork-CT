// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/29/2023 (1 day late)
// PROGRAM ASSIGNMENT 5
// FILE NAME : thread.h
// PROGRAM PURPOSE :
//  Declares child classes of Thread for the Cannibal, 
//  missionary, and boat threads. 
// --------------------------------------------------------

#ifndef hThread
#define hThread

#include "ThreadClass.h"
#include "boat-monitor.h"

class MissionaryThread : public Thread{
public:
    MissionaryThread(BoatMonitor*, int);
private:
    int id;
    BoatMonitor* monitor;

    void ThreadFunc();

    void MissionaryArrives();
};

class CannibalThread : public Thread{
public:
    CannibalThread(BoatMonitor*, int);
private:
    int id;
    BoatMonitor* monitor;


    void ThreadFunc();
    
    void CannibalArrives();
};

class BoatThread : public Thread{
public:
    BoatThread(BoatMonitor*);
private:
    BoatMonitor* monitor;

    void ThreadFunc();
    
    void BoatReady();
    void BoatDone();
};

#endif