/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 11/29/2023 (1 day late)                   */
/*  PROGRAM ASSIGNMENT 5                                 */
/*  FILE NAME : thread.cpp                               */
/*  PROGRAM PURPOSE :                                    */
/*      Define the running functionalities of            */
/*      missionary, cannibal, and boat classes.          */
/*-------------------------------------------------------*/

#include "thread.h"
#include "boat-monitor.h"
#include "shared.h"

/*-------------------------------------------------------*/
/* FUNCTION  MissionaryThread :                          */
/*      Constructor for MissionaryThread.                */
/* PARAMETER USAGE :                                     */
/*      monitor: Reference to a monitor instance for the */
/*              class to use at runtime.                 */
/*      id     : Instance identifiaction number          */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
MissionaryThread::MissionaryThread(BoatMonitor* monitor, int id){
    this->monitor = monitor;
    this->id = id;
}


/*-------------------------------------------------------*/
/* FUNCTION  CannibalThread :                            */
/*      Constructor for CannibalThread                   */
/* PARAMETER USAGE :                                     */
/*      monitor: Reference to a monitor instance for the */
/*              class to use at runtime.                 */
/*      id     : Instance identifiaction number          */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
CannibalThread::CannibalThread(BoatMonitor* monitor, int id){
    this->monitor = monitor;
    this->id = id;
}

/*-------------------------------------------------------*/
/* FUNCTION  BoatThread :                                */
/*      Constructor for BoatThread                       */
/* PARAMETER USAGE :                                     */
/*      monitor: Reference to a monitor instance for the */
/*              class to use at runtime.                 */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
BoatThread::BoatThread(BoatMonitor* monitor){
    this->monitor = monitor;
}

/*-------------------------------------------------------*/
/* FUNCTION  ThreadFunc :                                */
/*      Inhereted function from Thread. implements       */
/*      missionary runtime action order.                 */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      goto_sleep()                                     */
/*      food_ready()                                     */
/*-------------------------------------------------------*/
void MissionaryThread::ThreadFunc(){
    while(1){
        Delay();
        MissionaryArrives();

        for(int i = 0; i < 3; i++){
            Delay();
        }
    }
}

/*-------------------------------------------------------*/
/* FUNCTION  ThreadFunc :                                */
/*      Inhereted function from Thread. implements       */
/*      cannibal runtime action order.                   */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      goto_sleep()                                     */
/*      food_ready()                                     */
/*-------------------------------------------------------*/
void CannibalThread::ThreadFunc(){
    while(1){
        Delay();
        CannibalArrives();

        for(int i = 0; i < 3; i++){
            Delay();
        }
    }
}

/*-------------------------------------------------------*/
/* FUNCTION  ThreadFunc :                                */
/*      Inhereted function from Thread. implements boat  */
/*      runtime action order.                            */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      goto_sleep()                                     */
/*      food_ready()                                     */
/*-------------------------------------------------------*/
void BoatThread::ThreadFunc(){
    while(1){
        Delay();
        BoatReady();
        Delay();
        BoatDone();
    }
}

/*-------------------------------------------------------*/
/* FUNCTION  MissionaryArrives :                         */
/*      Registers itself with the boat monitor that it   */
/*      is ready to cross.                               */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      missWait()                                       */
/*-------------------------------------------------------*/
void MissionaryThread::MissionaryArrives(){
    print("Missionary %d arrives\n", id);
    monitor->missWait(id);
}

/*-------------------------------------------------------*/
/* FUNCTION  CannibalArrives :                           */
/*      Registers itself with the boat monitor that it   */
/*      is ready to cross.                               */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      cannWait()                                       */
/*-------------------------------------------------------*/
void CannibalThread::CannibalArrives(){
    print("Cannibal %d arrives\n", id);
    monitor->cannWait(id);
}

/*-------------------------------------------------------*/
/* FUNCTION  BoatReady :                                 */
/*      signals to the monitor that the boat is ready to */
/*      take more passengers.                            */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      boatWait()                                       */
/*-------------------------------------------------------*/
void BoatThread::BoatReady(){
    print("The boat is ready\n");
    monitor->boatWait();
}

/*-------------------------------------------------------*/
/* FUNCTION  BoatDone :                                  */
/*      Signals to the monitor that the boat has ferried */
/*      its passengers and is done.                      */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      goto_sleep()                                     */
/*      food_ready()                                     */
/*-------------------------------------------------------*/
void BoatThread::BoatDone(){
    monitor->boatEnd();
}