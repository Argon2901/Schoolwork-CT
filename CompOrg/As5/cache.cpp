#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "cache.h"


void Cache::parse(FILE* file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "reset")){
        this->reset();
    } else if(!strcmp(tempString, "on")){
        isActive = 1; 
    } else if(!strcmp(tempString, "off")){
        isActive = 0;
    } else if(!strcmp(tempString, "dump")){
        this->dump();
    }
    free(tempString);
}

void Cache::reset(){
    isActive = 0;
    CLO = 0;
    memset(validArray, 0, 8);
    memset(dataArray, 0, 8);
}

void Cache::dump(){
    printf("CLO        : 0x%02X\n", CLO);

    printf("cache data : ");
    for(int i = 0; i < 8; i++){
        printf("0x%02X ", dataArray[i]);
    }
    printf("\n");

    printf("Flags     : ");
    for(int i = 0; i < 8; i++){
        printf("  %c  ", flags[validArray[i]]);
    }
    printf("\n\n");
}

Cache::Cache(Memory* memory){
    this->memory = memory;
    dataArray = (unsigned char*)calloc(8, 8);
    validArray = (unsigned char*)calloc(8, 8);
}

Cache::~Cache(){
    free(dataArray);
    free(validArray);
}

void Cache::memFetch(unsigned int address, unsigned int count, 
          unsigned char* dataPtr, unsigned char* memDonePtr) 
{ 
    //printf("%s\n", isActive ? "active" : "not active");    
    if(!isActive){
        memory->memFetch(address, count, dataPtr, memDonePtr, Memory::CACHE);
        return;
    } 
    if(address == 0xFF){
        *dataPtr = 0;
        memset(validArray, 0, 8);
        *memDonePtr = 1;
        return;
    }

    unsigned int computedCacheLine = address >> 3;
    unsigned char offset = address & 0b111;

    if(computedCacheLine == CLO && validArray[offset]){ //cache hit 
        //printf("load cache hit\n");
        *dataPtr = dataArray[offset];
        *memDonePtr = 1;

    } else{ //cache miss
        //printf("load cache miss\n");
        unsigned char missDone = 0; 
        FFWrite(&missDone);

        if(missDone == 1){
            memory->immediateFetch(computedCacheLine << 3, 8, dataArray);
            memset(validArray, 1, 8);
            *dataPtr = dataArray[offset];
            *memDonePtr = 1;
        } else if(missDone == 2){
            memory->memFetch(computedCacheLine << 3, 8, dataArray, memDonePtr, Memory::CACHE);
            
            if(*memDonePtr){
                memset(validArray, 1, 8);
                *dataPtr = dataArray[offset];
            }
        }
    }

    return;
}

void Cache::memStore(unsigned int address, unsigned int count, 
          unsigned char* dataPtr, unsigned char *memDonePtr)
{
    if(!isActive){
        memory->memStore(address, count, dataPtr, memDonePtr, Memory::CACHE);
        return;
    }   

    if(address == 0xFF){
        //printf("starting ffwrite\n");
        FFWrite(memDonePtr);
        flushed = 1;
        //printf("memDonePtr = %d\n", *memDonePtr);
        if(*memDonePtr){
            //printf("mem reset to V\n")
            //memset(validArray, 1, 8);
            flushed = 1;
        }
        return;
    } 

    unsigned int computedCacheLine = address >> 3;
    unsigned char offset = address & 0b111;


    if(computedCacheLine == CLO || flushed){ //cache hit
        //printf("store cache hit, CLO = %02X, calc = %02X\n", CLO, computedCacheLine);
        dataArray[offset] = *dataPtr;
        validArray[offset] = 2; 
        *memDonePtr = 1;
        /*if(flushed){
            CLO = computedCacheLine;
        }
        flushed = 0;*/

    } else{ //cache miss
        //printf("store cache miss, CLO = %02X\n", computedCacheLine);
        FFWrite(memDonePtr);
        if(*memDonePtr){
            //printf("miss mem done ptr != 0 \n");
            memset(validArray, 0, 8);
            CLO = computedCacheLine;
            dataArray[offset] = *dataPtr;
            
            //memory->immediateStore(address, dataPtr);
            validArray[offset] = 2;
            //flushed = 1;
        }
    }

}

void Cache::FFWrite(unsigned char *memDonePtr){
    unsigned char hasWritable = 0;

    for(int i = 0; i < 8; i++){
        if(validArray[i] == 2){
            memory->memStore((CLO << 3) + i, 1, dataArray + i, memDonePtr, Memory::CACHE);
            hasWritable = 1;
            break;    
        }
    }

    if(!hasWritable){
        *memDonePtr = 2;
        return;
    }

    if(*memDonePtr){
        //printf("FF memDonePtr is true\n");

        for(int i = 0; i < 8; i++){
            if(validArray[i] == 2){
                memory->immediateStore((CLO << 3) + i, dataArray + i);
                validArray[i] = 1;
            }
        }
    }

}