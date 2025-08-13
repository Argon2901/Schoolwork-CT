#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "clock.h"
#include "workable.h"

void Clock::parse(FILE* file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "reset")){
        this->reset();
    } else if(!strcmp(tempString, "tick")){
        unsigned int ticks;
        fscanf(file, "%d", &ticks);
        this->tick(ticks);
    } else if(!strcmp(tempString, "dump")){
        this->dump();
    }
}

void Clock::reset(){
    count = 0;
}

Clock::~Clock(){
}

void Clock::tick(unsigned int ticks){
    char hasWorkToDo = true;


    for(unsigned int i = 0; i < ticks; i++){
        //printf("cycle %d start--------------------------------------------------\n", count + 1);
        for(int j = 0; j < numDevices; j++){
            devices[j]->startCycleWork();
        }

        hasWorkToDo = true;

        while(hasWorkToDo){
            hasWorkToDo = false;
            for(int k = 0; k < numDevices; k++){
                devices[k]->doCycleWork();
                hasWorkToDo = hasWorkToDo || devices[k]->hasCycleWork();
                //printf("doing cycle work %d\n", k);
            }
        }

        count++;
    }
}

void Clock::dump(){
    printf("Clock: %d\n", count);
    printf("\n");
}

Clock::Clock(Workable** devices, int numDevices){
    this->devices = devices;
    this->numDevices = numDevices;
}
