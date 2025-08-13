#include "instruction_memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Instruction_Memory::~Instruction_Memory(){
    free(memory);
}

void Instruction_Memory::parse(FILE* file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "create")){
        unsigned int size;
        fscanf(file, "%X", &size);
        create(size);
    } else if(!strcmp(tempString, "reset")){
        reset();
    } else if(!strcmp(tempString, "dump")){
        unsigned int address;
        int count;

        fscanf(file, "%X", &address);
        fscanf(file, "%X", &count);

        dump(address, count);
    } else if(!strcmp(tempString, "set")){
        char* discard = (char*)malloc(10);
        char* filename = (char*)malloc(500);
        unsigned int address;

        fscanf(file, "%X", &address);
        fscanf(file, "%s", discard); //the 'file'
        fscanf(file, "%s", filename);

        FILE* iMemoryFile = fopen(filename, "r");
        set(address, iMemoryFile);
        fclose(iMemoryFile);
    }
}

void Instruction_Memory::create(unsigned int size){
    if(0 != memory){
        free(memory);
    }

    this->size = size;
    memory = (unsigned int*)malloc(size * (unsigned int)sizeof(int));
}

void resetI(unsigned int* arr, int n){
    for(int i = 0; i < n; i++){
        arr[i] = 0;
    }
}

void resetNeg(int* arr, int n){
    for(int i = 0; i < n; i++){
        arr[i] = -1;
    }
}

void Instruction_Memory::reset(){
    resetI(memory, size);
}    

void Instruction_Memory::dump(unsigned int address, int bytes){
    printf("addr %5d %5d %5d %5d %5d %5d %5d %5d\n", 0, 1, 2, 3, 4, 5, 6, 7);
    int tempStorage[] = {-1, -1, -1, -1, -1, -1, -1, -1};
    char hasReachedEnd = 0;


    while(bytes > 0){
        printf("0x%02X ", address - (address & 0b111));
        hasReachedEnd = 0;
        while(!hasReachedEnd && bytes > 0){
            tempStorage[address & 0b111] = (int)memory[address];
            bytes--;
            address++;
            hasReachedEnd = !(address & 0b111);
        }

        for(int i = 0; i < 8; i++){
            if(tempStorage[i] < 1){
                printf("      ");
            } else{
                printf("%5X ", tempStorage[i]);
            }
        }
        printf("\n");
        resetNeg(tempStorage, 8);
    }
    printf("\n");
}

void Instruction_Memory::set(unsigned int address, FILE* file){
    unsigned int instruction;
    while(fscanf(file, "%X", &instruction) == 1){
        memory[address] = instruction;
        address++;
    }
}

unsigned int Instruction_Memory::fetchI(unsigned int address) { 
    return memory[address];
}