/*-------------------------------------------------------*/
/*  NAME : Collin Thompson              USER ID : collint*/
/*  DUE DATE : 11/29/2023 (1 day late)                   */
/*  PROGRAM ASSIGNMENT 5                                 */
/*  FILE NAME : boat-monitor.cpp                         */
/*  PROGRAM PURPOSE :                                    */
/*      Impliments the boat monitor routines.            */
/*-------------------------------------------------------*/

#include "boat-monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include <unistd.h>

/*-------------------------------------------------------*/
/* FUNCTION  BoatMonitor :                               */
/*      Iniitializes the boat monitor.                   */
/* PARAMETER USAGE :                                     */
/*      name  : string used for the visualization        */
/*      nLoads: the total number of loads the boat will  */
/*          service before exiting.                      */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
BoatMonitor::BoatMonitor(char* name, int nLoads)
            :Monitor(name, HOARE){
    this->nLoads = nLoads;

    wCann = new  Condition("cannibal");
    wMiss = new  Condition("missionary");
    wBoat = new  Condition("boat");
    beingFerried = new  Condition("being ferried");   
}

/*-------------------------------------------------------*/
/* FUNCTION  boatWait :                                  */
/*     Boat will wait until it has passengers available  */
/*      or will immediately set off if there is a valid  */
/*      configuration of passengers with which to cross. */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      ferryPassengers()                                */
/*-------------------------------------------------------*/
void BoatMonitor::boatWait(){
    MonitorBegin(); 
    if(currentLoads == nLoads){
        print("Monitor: %d crosses have been made.\n", currentLoads);
        print("Monitor: The river cross is closed indefinitely for renovation\n");
        exit(0);
    }

        if(nMiss >= 3 || nMiss == 2 && nCann >= 1 || nCann >= 3){
            ferryPassengers();
        } else{       
            boatReady = true;
            wBoat->Wait();
        } 

        switch(type){
            case threeC:
                print("***** Boat load (%d): Passenger list (c%d, c%d, c%d)\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                break;
            case threeM:
                print("***** Boat Load (%d): Passenger list (m%d, m%d, m%d)\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                break;
            case weird:
                print("***** Boat Load (%d): Passenger list (c%d, m%d, m%d)\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                break;
        }

        //print("nCann = %d, nMiss = %d\n", nCann, nMiss);
    MonitorEnd();
}


/*-------------------------------------------------------*/
/* FUNCTION  boatEnd :                                   */
/*      Ends the boat passage and frees passengers.      */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                      */
/*-------------------------------------------------------*/
void BoatMonitor::boatEnd(){

    MonitorBegin();
        print("***** Boat Load (%d): Completed\n", currentLoads + 1);
        currentLoads++;
        beingFerried->Signal();
        beingFerried->Signal();
        beingFerried->Signal();
        nBoarded = 0;
    MonitorEnd();       
}


/*-------------------------------------------------------*/
/* FUNCTION  ferryPassengers :                           */
/*      Frees groups of passengers in the case that the  */
/*      boat arrives and there already is a valid amount.*/
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void BoatMonitor::ferryPassengers(){
    if(nMiss >= 3){
        wMiss->Signal();
        wMiss->Signal();
        wMiss->Signal();
        print("Monitor(%d): three missionaries (%d, %d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
        type = threeM;
    } else if(nMiss == 2 && nCann >= 1){

        wCann->Signal(); 
        wMiss->Signal();
        wMiss->Signal();
        print("Monitor(%d): one cannibal (%d) and two missionaries (%d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]); 
        type = weird;
    } else if(nCann >= 3){
        wCann->Signal();
        wCann->Signal();
        wCann->Signal();
        print("Monitor(%d): three cannibals (%d, %d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
        type = threeC;
    }
}


/*-------------------------------------------------------*/
/* FUNCTION  cannWait :                                  */
/*      Locks the cannibal thread in a control variable  */
/*      if a valid configuration of passengers does not  */
/*      exist or if the boat is not there.               */
/*                                                       */
/*      Frees waiting passengers if a valid configuration*/
/*      is found when the function is called and frees   */
/*      the boat.                                        */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void BoatMonitor::cannWait(int id){
    MonitorBegin();
        nCann++;
        if(boatReady){
            if(nMiss >= 3 || nMiss == 2 && nCann >= 1){
                boatReady = false;

                if(nCann >= 3){
                    type = threeC;
                    boardedIDs[0] = id;
                    nBoarded++;
                    wCann->Signal();
                    wCann->Signal();
                    print("Monitor(%d): three cannibals (%d, %d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                } else{
                    type = weird;

                    boardedIDs[nBoarded] = id;
                    nBoarded++;
                    wMiss->Signal();
                    wMiss->Signal();
                    print("Monitor(%d): one cannibal (%d) and two missionaries (%d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                }

                wBoat->Signal();
            } else{
                wCann->Wait();
                boardedIDs[nBoarded] = id;
                nBoarded++;
            }
        } else{
            wCann->Wait();
            boardedIDs[nBoarded] = id;
            nBoarded++;
        }
        
        nCann--;

        beingFerried->Wait();
    MonitorEnd();
}

/*-------------------------------------------------------*/
/* FUNCTION  missWait :                                  */
/*      Locks the missionary thread in a control variable*/
/*      if a valid configuration of passengers does not  */
/*      exist or if the boat is not there.               */
/*                                                       */
/*      Frees waiting passengers if a valid configuration*/
/*      is found when the function is called and frees   */
/*      the boat.                                        */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void BoatMonitor::missWait(int id){
    MonitorBegin();
        nMiss++;
        if(boatReady){
            if(nMiss >= 3 || nMiss == 2 && nCann >= 1){
                boatReady = false;

                if(nMiss >= 3){
                    type = threeM;
                    boardedIDs[0] = id;
                    nBoarded++;
                    wMiss->Signal();
                    wMiss->Signal();
                    print("Monitor(%d): three missionaries (%d, %d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                } else{
                    type = weird;
                    wCann->Signal();
                    boardedIDs[nBoarded] = id;
                    nBoarded++;
                    wMiss->Signal();
                    print("Monitor(%d): one cannibal (%d) and two missionaries (%d, %d) are selected\n", currentLoads + 1, boardedIDs[0], boardedIDs[1], boardedIDs[2]);
                }

                wBoat->Signal();
            } else{
                wMiss->Wait();
                boardedIDs[nBoarded] = id;
                nBoarded++;
            }
        } else{
            wMiss->Wait();
            boardedIDs[nBoarded] = id;
            nBoarded++;
        }
        
        nMiss--;

        beingFerried->Wait();
    MonitorEnd();
}