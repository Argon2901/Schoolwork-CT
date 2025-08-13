
// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/08/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME : thread-support.cpp
// PROGRAM PURPOSE :
// Facilitates the activities of the mother and baby birds
// --------------------------------------------------------

#include "thread.h"
#include "ThreadClass.h"
#include "shared.h"

Semaphore *motherAwake;
Semaphore *pots;
int numPots;    

int potsUsed;
int potsFinished;
bool motherCalled = false;
bool motherRetired = false;

Semaphore birdMutex("mutex", 1);

/*-------------------------------------------------------*/
/* FUNCTION  BabyThread :                                     */
/*      BabyThread object constructor                    */
/* PARAMETER USAGE :                                     */
/*      number: int number of the bird created           */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
BabyThread::BabyThread(int number){
    this->number = number;
}

/*-------------------------------------------------------*/
/* FUNCTION  MotherThread :                              */
/*      MotherThread object constructor. Also initializes*/
/*      global variables.                                */
/* PARAMETER USAGE :                                     */
/*      feedings: int number of total feedings to happen */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
MotherThread::MotherThread(int feedings){
    potsUsed = numPots;
    potsFinished = numPots;
    totalFeedings = feedings;
}


/*-------------------------------------------------------*/
/* FUNCTION  ready_to_eat :                              */
/*      Impliments functionality for babies signaling    */
/*      the mother that they are without food and need to*/
/*      have pots filled. Also allows babies to eat.     */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void BabyThread::ready_to_eat(){
    print("Baby eagle %d is ready to eat.\n", number + 1);
    birdMutex.Wait();
    //print("Baby eagle %d got into the ready to eat mutex\n", number + 1);
    if(potsUsed == numPots){
        if(motherRetired){
            //print("baby %d exiting\n", number + 1);
            birdMutex.Signal();
            Exit();
        }

        if(!motherCalled && potsFinished == numPots){
            print("Baby eagle %d sees all the feeding pots are empty and wakes up the mother.\n", number + 1);
            motherCalled = true;
            motherAwake->Signal();
        }
    }
    birdMutex.Signal();

    pots->Wait();

    birdMutex.Wait();
    if(potsUsed == numPots && motherRetired){
        //print("baby %d exiting\n", number + 1);
        birdMutex.Signal();
        Exit();
    }

    print("Baby eagle %d is eating using feeding pot %d\n", number + 1, potsUsed + 1);
    potsUsed++;
    birdMutex.Signal();
}


/*-------------------------------------------------------*/
/* FUNCTION  finished_eating :                           */
/*      Signals that babies have eaten and that their pot*/
/*      is now fully empty.                              */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void BabyThread::finished_eating(){
    birdMutex.Wait();
    print("Baby eagle %d is finished eating\n", number + 1);
    potsFinished++;
    birdMutex.Signal();
}


/*-------------------------------------------------------*/
/* FUNCTION  goto_sleep :                                */
/*      Allows mother bird to sleep and wait for babies  */
/*      wake her. Also checks to see if her business is  */
/*      done and raises the retire flag while freeing all*/
/*      waiting children to exit.                        */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void MotherThread::goto_sleep(){
    birdMutex.Wait();
    if(feedingsDone == totalFeedings){
        motherRetired = true;
        birdMutex.Signal();
        for(int i = 0; i < 40; i++){
            pots->Signal();
        }
        Exit();
    }
    motherCalled = false;
    birdMutex.Signal();
    print("Mother eagle is taking a nap\n");
    motherAwake->Wait();
}


/*-------------------------------------------------------*/
/* FUNCTION  food_ready :                                */
/*      Fills all of the empty pots.                     */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
void MotherThread::food_ready(){
    print("Mother eagle says \"Feeding (%d)\"\n", feedingsDone + 1);
    birdMutex.Wait();
    for(int i = 0; i < numPots && feedingsDone != totalFeedings; i++){
        print("Mother filling pot %d\n", i + 1);
        potsUsed--;
        potsFinished--;
        pots->Signal();
    }
    birdMutex.Signal();
    feedingsDone++;
}