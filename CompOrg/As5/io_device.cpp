
#include "io_device.h"
#include "clock.h"
#include "memory.h"
#include <string.h>

IO::IO(Clock* clock, Memory* memory){
    this->clock = clock;
    this->memory = memory;
}

void IO::parse(FILE* file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "reset")){
        this->reset();
    } else if(!strcmp(tempString, "load")){
        char* filepath = (char*) malloc(50);
        fscanf(file, "%s", filepath);
        load(filepath);
    } else if(!strcmp(tempString, "dump")){
        dump();
    }
    free(tempString);
}

void IO::load(char* filepath){
    this->filepath = filepath;
    this->file = fopen(filepath, "r");
}

void IO::dump(){
    printf("IO Device: 0x%02X\n\n", eventInfo.data);
}

void IO::reset(){
    this->file = fopen(filepath, "r");
}

void IO::doCycleWork(){
    //printf("io doing cycle work\n");
    char* tempString = (char*)malloc(20);
    switch(state){
        case idle:
            if(feof(file)){
                return;
            }
            fscanf(file, "%d", &eventInfo.tick);
            fscanf(file, "%s", tempString);
            eventInfo.operation = (strcmp(tempString, "read") ? 0 : 1);
            fscanf(file, "%X", &eventInfo.reg);

            if(!eventInfo.operation){ //if store
                fscanf(file, "%X", &eventInfo.data);
            }

            state = waiting;
            break;

        case waiting:
            //printf("io waiting\n");
            if(clock->getTicks() == eventInfo.tick){
                state = working;
            } else{
                endCycleWork();
            }
            break;
        case working:
            printf("Working at tick %d\n", clock->getTicks());
            unsigned char memDonePtr = 0;
            if(eventInfo.operation){ //load
                //printf("io_device fetch\n");
                memory->memFetch(eventInfo.reg, 1, (unsigned char*)&(eventInfo.data), &memDonePtr, Memory::IO);
            } else{ //store
                memory->memStore(eventInfo.reg, 1, (unsigned char*)&(eventInfo.data), &memDonePtr, Memory::IO);
            }

            if(memDonePtr){
                //printf("io_device op:%d reg:%d data:%d\n", eventInfo.operation, eventInfo.reg, eventInfo.data);
                state = idle;
            } else{
                endCycleWork();
            }

            break;
    }
    free(tempString);
}