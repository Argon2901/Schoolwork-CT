#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"

void Memory::doCycleWork(){
    if(!hasCycleWork()){
        return;
    }

    switch(state){
        case idle:
            endCycleWork();
            return;
        case waiting:
            waitTime--;
            //printf("memory waiting\n");
            if(waitTime == 0){
                //printf("memory wait over\n");
                state = completed;
            }
            
            
            endCycleWork();
            

            return;
        case completed:
            //endCycleWork();
            return;
    }
}

void Memory::create(unsigned int bytes){
    if(memory != 0){
        free(memory);
    }

    memorySize = bytes;
    memory = (unsigned char*)malloc(bytes);
}

void resetA(unsigned char* array, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        array[i] = 0;
    }
}

void resetNeg(int* array, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        array[i] = -1;
    }
}

void Memory::reset(){
    resetA(memory, memorySize);
}

void Memory::dump(unsigned int address, int bytes){
    const char* titleFormat = "Addr 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
    int* tempStorage = (int*)malloc(16 * sizeof(int));
    char hasReachedEnd = 0;
    resetNeg(tempStorage, 16);

    printf(titleFormat);

    while(bytes > 0){
        printf("0x%02X ", address - (address & 0b1111));
        hasReachedEnd = 0;
        while(!hasReachedEnd && bytes > 0){
            tempStorage[address & 0b1111] = (int)memory[address];
            bytes--;
            address++;
            hasReachedEnd = !(address & 0b1111);
        }

        for(int i = 0; i < 16; i++){
            if(tempStorage[i] < 0){
                printf("   ");
            } else{
                printf("%02X ", tempStorage[i]);
            }
        }
        printf("\n");
        resetNeg(tempStorage, 16);
    }
    
    printf("\n");

    free(tempStorage);
}


void Memory::memFetch(unsigned int address, unsigned int count, 
          uint8_t *dataPtr, unsigned char *memDonePtr, Memory::Signature signature) 
{ 
    if(device != FREE && signature != device){
        return;
    }
    device = signature;

    switch(state){
        case idle:
            state = waiting;
            waitTime = 4;
            //printf("memory memreq\n");
            return;
        case waiting:
            return;
        case completed:
            state = idle;
    }
        
    if (1 == count)  // special case if only 1 byte 
    *dataPtr = memory[address]; 
    else 
    memcpy(dataPtr, memory+address, count); 
    
    // could always use memcpy, but useful to show what 
    // is going on with a single byte example 
    
    *memDonePtr = 1;  // tell CPU copy is done 
    device = FREE;
}


void Memory::memStore(unsigned int address, unsigned int count, 
          uint8_t *dataPtr, unsigned char *memDonePtr, Memory::Signature signature)
{
    if(device != FREE && signature != device){
        return;
    }
    device = signature;

    switch(state){
        case idle:
            state = waiting;
            waitTime = 4;
            return;
        case waiting:
            return;
        case completed:
            //printf("memStore ready and completed\n");
            state = idle;
    }

    if (1 == count)  // special case if only 1 byte 
        memory[address] = *dataPtr; 
    else 
        memcpy(memory+address, dataPtr, count);
    device = FREE;
    *memDonePtr = 1;  // tell CPU copy is done 
}

void Memory::immediateStore(unsigned int address, unsigned char* data){
    memory[address] = *data;
}

void Memory::immediateFetch(unsigned int address, unsigned int count, unsigned char* data){
    memcpy(data, memory+address, count); 
}

void Memory::set(unsigned int address, unsigned int n, unsigned char* bytes){
    for(unsigned int i = 0; i < n; i++){
        memory[address + i] = bytes[i];
    }
}

void Memory::parse(FILE* file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "reset")){
        this->reset();
    } else if(!strcmp(tempString, "create")){
        unsigned int size;
        fscanf(file, "%X", &size);

        this->create(size);
    } else if(!strcmp(tempString, "dump")){
        unsigned int address; 
        unsigned int count;

        fscanf(file, "%X", &address);
        fscanf(file, "%X", &count);

        this->dump(address, count);
    } else if(!strcmp(tempString, "set")){
        unsigned int address;
        unsigned int count;
        unsigned int temp;
        fscanf(file, "%X", &address);
        fscanf(file, "%X", &count);
        unsigned char* bytes = (unsigned char*)malloc(count);

        for(unsigned int i = 0; i < count; i++){
            fscanf(file, "%X", &temp);
            bytes[i] = (unsigned char)temp;
        }
        set(address, count, bytes);
        free(bytes);
    }
    free(tempString);
}

Memory::~Memory(){
    free(memory);
}