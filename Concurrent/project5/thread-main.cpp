/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 11/29/2023 (1 day late)                   */
/*  PROGRAM ASSIGNMENT 5                                 */
/*  FILE NAME : thread-main.cpp                          */
/*  PROGRAM PURPOSE :                                    */
/*      Create monitor and threads and oversee their     */
/*      execution.                                       */
/*-------------------------------------------------------*/


#include "boat-monitor.h"
#include "thread.h"
#include "shared.h"


/*-------------------------------------------------------*/
/* FUNCTION  main :                                      */
/*      Main function. Initializes and starts threads.   */
/* PARAMETER USAGE :                                     */
/*      argc: int number of arguments                    */
/*      argv: runtime variables, arguments 1, 2, and 3   */
/*            represent nCannibals, nMissionaries,       */
/*            and nTrips                                 */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
int main(int argc, char* argv[]){
    int cannibalCount = atoi(argv[1]);
    int missionaryCount = atoi(argv[2]);
    int numberOfTrips = atoi(argv[3]);

    if(cannibalCount == 0){
        cannibalCount = 8;
    }

    if(missionaryCount == 0){
        missionaryCount = 8;
    }

    if(numberOfTrips == 0){
        numberOfTrips = 5;
    }

    BoatMonitor* monitor = new BoatMonitor("name", numberOfTrips);

    CannibalThread** cannibals = (CannibalThread**)malloc(sizeof(CannibalThread*) * cannibalCount);
    MissionaryThread** missionaries = (MissionaryThread**)malloc(sizeof(MissionaryThread*) * missionaryCount);
    BoatThread* boat = new BoatThread(monitor);

    for(int i = 0; i < cannibalCount; i++){
        cannibals[i] = new CannibalThread(monitor, i + 1);
    }
    for(int i = 0; i < missionaryCount; i++){
        missionaries[i] = new MissionaryThread(monitor, i + 1);
    }

    for(int i = 0; i < cannibalCount; i++){
        cannibals[i]->Begin();
        print("Cannibal %d starts\n", i + 1);
    }

    for(int i = 0; i < missionaryCount; i++){
        missionaries[i]->Begin();
        print("Cannibal %d starts\n", i + 1);
    }
    
    boat->Begin();

    boat->Join();
    

}