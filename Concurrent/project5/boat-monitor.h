/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 11/29/2023 (1 day late)                   */
/*  PROGRAM ASSIGNMENT 5                                 */
/*  FILE NAME : boat-monitor.h                           */
/*  PROGRAM PURPOSE :                                    */
/*      Creates a monitor that impliments the            */
/*      functionality of boat crossings.                 */
/*-------------------------------------------------------*/

#ifndef hMonitor
#define hMonitor
#include "ThreadClass.h"



class BoatMonitor : public Monitor{
public:
    BoatMonitor(char*, int);
    void boatWait();
    void missWait(int);
    void cannWait(int);
    void boatEnd();

private:
    Condition *wCann;
    Condition *wMiss;
    Condition *wBoat; 
    Condition *beingFerried;

    int nBoarded = 0; 
    int boardedIDs[3];
    bool fl_weird_miss;
    enum loadType {threeC, threeM, weird} type;


    int nLoads;
    int currentLoads = 0;

    int nCann = 0; 
    int nMiss = 0; 
    bool boatReady = false; 

    void ferryPassengers();
};


#endif