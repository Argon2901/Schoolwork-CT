#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "emulator.h"
#include "memory.h"
#include "cpu.h"
#include "clock.h"
#include "instruction_memory.h"
#include "cache.h"
#include "io_device.h"

Emulator::Emulator(char* filepath){
    devices = (Parseable**)malloc(deviceCount * sizeof(Parseable*));
    workables = (Workable**)malloc(workableCount * sizeof(Workable*));

    this->filepath = filepath;
    this->file = fopen(filepath, "r");


    this->devices[0] = new Memory();
    this->workables[0] = (Workable*)devices[0];
    this->devices[2] = new Clock(workables, workableCount);
    this->devices[3] = new Instruction_Memory();
    this->devices[4] = new Cache((Memory*)this->devices[0]);
    this->devices[1] = new CPU((Cache*)this->devices[4], (Instruction_Memory*)this->devices[3]);
    this->workables[1] = (Workable*)devices[1];
    this->devices[5] = new IO((Clock*)this->devices[2], (Memory*)this->devices[0]);
    this->workables[2] = (Workable*)devices[5];
    //printf("created all devices\n");
}

Emulator::~Emulator(){
    for(int i = 0; i < deviceCount; i++){
        delete devices[i];
    }
    fclose(file);
    free(workables);
    free(devices);
}

void Emulator::start(){
    
    char* temp = (char*)malloc(50);
    while(fscanf(file, "%s", temp) == 1){
        //printf("%s\n", temp);
        if(!strcmp(temp, "memory")){
            devices[0]->parse(file);
        } else if(!strcmp(temp, "cpu")){
            devices[1]->parse(file);
        } else if(!strcmp(temp, "clock")){
            devices[2]->parse(file);
        } else if(!strcmp(temp, "imemory")){
            devices[3]->parse(file);
        } else if(!strcmp(temp, "cache")){
            devices[4]->parse(file);
        } else if(!strcmp(temp, "iodev")){
            devices[5]->parse(file);
        }
    }
    free(temp);
}