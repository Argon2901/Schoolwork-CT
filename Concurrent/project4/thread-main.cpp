// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 11/08/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Creates and runs the child threads. 
// --------------------------------------------------------


#include "ThreadClass.h"
#include "thread.h"
#include <iostream>
#include <stdio.h>
#include "shared.h"

/*-------------------------------------------------------*/
/* FUNCTION  main :                                      */
/*      Verifies the input as correct.                   */
/*      Creates and initializes the global runtime       */
/*      variables in thread.h.                           */
/*      Creates and starts the mother and baby threads   */
/* PARAMETER USAGE :                                     */
/*      argc: int number of arguments                    */
/*      argv: runtime variables, arguments 1, 2, and 3   */
/*            represent nPots, nBabies, and nFeedings    */
/* FUNCTION CALLED :                                     */
/*-------------------------------------------------------*/
int main(int argc, char* argv[]){
    if(argc < 4){
        perror("Not enough arguments\n");
        exit(1);
    }

    int inPots, babies, feedings;
    inPots = atoi(argv[1]);
    babies = atoi(argv[2]);
    feedings = atoi(argv[3]);

    if(inPots < 0 || babies < 0 || feedings < 0){
        perror("Inputs must be greater than or equal to 0\n");
        exit(1);
    }

    if(inPots == 0){
        inPots = 10;
    }
    if(babies == 0){
        babies = 10;
    }
    if(feedings == 0){
        feedings = 10;
    }

    if(inPots > babies){
        perror("Pots must be less than or equal to babies\n");
        exit(1);
    }

    motherAwake = new Semaphore("mother", 0);
    pots = new Semaphore("pots", 0);
    numPots = inPots;
    BabyThread **babyThreads = (BabyThread**)malloc(sizeof(BabyThread*) * babies);
    for(int i = 0; i< babies; i++){
        babyThreads[i] = new BabyThread(i);
    }
    MotherThread *mother = new MotherThread(feedings);

    print("MAIN: There are %d baby eagles, %d feeding pots, and %d feedings.\n", babies, inPots, feedings);

    print("MAIN: Game starts!!!\n");
    mother->Begin();
    print("Mother eagle has started.\n");

    for(int i = 0; i < babies; i++){
        babyThreads[i]->Begin();
    }


    for(int i = 0; i < babies; i++){
        babyThreads[i]->Join();
    }


    print("Mother eagle retires after serving %d feedings. Game is over!!!\n", feedings);
}