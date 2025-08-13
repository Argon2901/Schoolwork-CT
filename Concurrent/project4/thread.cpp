// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/08/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Defines the runtime behaviors and calls of the mother
// and baby threads. 
// --------------------------------------------------------

#include "ThreadClass.h"
#include "thread.h"
#include <cstdlib>
#include <ctime>

/*-------------------------------------------------------*/
/* FUNCTION  ThreadFunc :                                */
/*      Inhereted function from Thread. implements mother*/
/*      runtime action order.                            */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      goto_sleep()                                     */
/*      food_ready()                                     */
/*-------------------------------------------------------*/
void MotherThread::ThreadFunc(){
    std::srand(std::time(nullptr));
    int randomNumber;
    while(1){
            goto_sleep();

        //hunting
        randomNumber = (std::rand() % 4) + 1;
        for(int i = 0; i < randomNumber; i++){
            Delay();
        }

        food_ready();

        //doing random stuff
        randomNumber = (std::rand() % 4) + 1;
        for(int i = 0; i < randomNumber; i++){
            Delay();
        }

    }
}

/*-------------------------------------------------------*/
/* FUNCTION  ThreadFunc :                                */
/*      Inhereted function from Thread. implements baby  */
/*      runtime action order.                            */
/* PARAMETER USAGE :                                     */
/* FUNCTION CALLED :                                     */
/*      ready_to_eat()                                   */
/*      finished_eating()                                */
/*-------------------------------------------------------*/
void BabyThread::ThreadFunc(){
    std::srand(std::time(nullptr));
    int randomNumber;

    while(1){
        Delay();

        ready_to_eat();

        randomNumber = (std::rand() % 4) + 1;
        for(int i = 0; i < randomNumber; i++){
            Delay();
        }

        finished_eating(); 
    }
}