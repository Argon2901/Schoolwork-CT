#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functional>

#include "cache.h"
#include "cpu.h"


void CPU::endCycleWork(){
    hasWork = 0;
    tickCount++;
}

void CPU::reset(){
    registers.PC = 0;
    tickCount = 0;
    *((unsigned long long int*)(registers.rReg)) = 0; //resets rReg array
    state = idle;
    hasHalted = 0;
}

void CPU::set_register(unsigned char reg, unsigned char value){
    if(reg == 9){
            registers.PC = value;
            return;
    }
    registers.rReg[reg] = value;
}

void CPU::dump(){


    const char* format = "%c%c: 0x%02X\n";
    printf(format, 'P', 'C', registers.PC);
    for(int i = 0; i < 8; i++){
        printf(format, 'R', ('A' + i), registers.rReg[i]);
    }
    printf("TC: %d\n", tickCount);
    printf("\n");
}

void CPU::doCycleWork(){
    if(!hasCycleWork()){
        //  printf("cpu no cycle work\n");
        return;
    }

    if(hasHalted){
        //printf("Halted cycle work, tick %d\n", tickCount);
        //printf("hasWork == %d\n", hasWork);
        endCycleWork();
        return;
    }



    switch(state){
        case idle:
            //printf("cpu do cycle work idle \n");
            state = fetchI;

            endCycleWork();
            return;

        case fetchI:
            //printf("cpu do cycle work fetchI \n");
            state = decode;

            instruction = iMemory->fetchI(registers.PC);
            //printf("working on instruction %5X tick %d\n", instruction, tickCount);


            return;

        case decode:
            //printf("cpu do cycle work decode \n");
            state = memReq;

            //instructionCompleted = 0;
            parseInstruction(instruction);

            return;

        case memReq:
            //printf("cpu do cycle work memReq \n");
            state = memWait;

            return;

        case memWait:
            //printf("cpu do cycle work memWait \n");
            
            unsigned char instructionCompleted = 0;
            nextInstruction(&instructionCompleted);

            if(instructionCompleted){
                state = idle;
                //printf("Instruction Completed\n");
                registers.PC++;
            } else{        
                endCycleWork();     
            }

            return;
    }
}

CPU::CPU(Cache* memory, Instruction_Memory* iMemory){
    this->memory = memory;
    this->iMemory = iMemory;

    registers.PC = 0;
    registers.rReg = (unsigned char*)calloc(8, 8);
}

CPU::~CPU(){
    free(registers.rReg);
}

void CPU::parse(FILE *file){
    char* tempString = (char*)malloc(40);
    fscanf(file, "%s", tempString);//pulling initial command

    if(!strcmp(tempString, "reset")){
        this->reset();
    } else if(!strcmp(tempString, "set")){
        fscanf(file, "%s", tempString);

        if(!strcmp(tempString, "reg")){
            char* reg = (char*) malloc(2);
            unsigned char regIndex;
            int temp;

            unsigned char byte;
            fscanf(file, "%s", reg);
            fscanf(file, "%X", &temp);
            byte = (unsigned char)(temp);

            if(reg[0] == 'R'){
                regIndex = (reg[1] - 'A') & 7;
            } else{
                regIndex = 9;
            }
            this->set_register(regIndex, byte);
        }
    } else if(!strcmp(tempString, "dump")){
        this->dump();
    }
}

void CPU::parseInstruction(unsigned int instruction){
    unsigned char nnn = (unsigned char)((instruction & 0xE0000) >> 17);
    unsigned char ddd = (unsigned char)((instruction & 0x1C000) >> 14);
    unsigned char sss = (unsigned char)((instruction & 0x03800) >> 11);
    unsigned char ttt = (unsigned char)((instruction & 0x00700) >> 8);
    unsigned char iiiiiiii = (unsigned char)((instruction & 0x000FF));

    switch(nnn){
        case 0b000:
                nextInstruction = std::bind(&CPU::add, this, ddd, sss, ttt, std::placeholders::_1);
            return;

        case 0b001:
            nextInstruction = std::bind(&CPU::addi, this, ddd, sss, iiiiiiii, std::placeholders::_1);
            return;
        
        case 0b010:
            nextInstruction = std::bind(&CPU::mul, this, ddd, sss, std::placeholders::_1);
            return;
        
        case 0b011:
            nextInstruction = std::bind(&CPU::inv, this, ddd, sss, std::placeholders::_1);
            return;
        
        case 0b100:
            if(!ddd){
                nextInstruction = std::bind(&CPU::beq, this, sss, ttt, iiiiiiii, std::placeholders::_1);

            } else{
                if(ddd & 0b1){
                        nextInstruction = std::bind(&CPU::bneq, this, sss, ttt, iiiiiiii, std::placeholders::_1);
                } else{
                        nextInstruction = std::bind(&CPU::blt, this, sss, ttt, iiiiiiii, std::placeholders::_1);
                }
            }

            return;

        case 0b101: //lw 
            nextInstruction = std::bind(&CPU::load, this, ddd, ttt, std::placeholders::_1);
            return;
        
        case 0b110: //sw
            nextInstruction = std::bind(&CPU::store, this, sss, ttt, std::placeholders::_1);
            return;

        case 0b111:
            nextInstruction = std::bind(&CPU::halt, this, std::placeholders::_1);
            return;
    }
}

void CPU::add(unsigned char dReg, unsigned char sReg, unsigned char tReg, unsigned char* completed){
    registers.rReg[dReg] = registers.rReg[sReg] + registers.rReg[tReg];
    *completed = true;
}

void CPU::addi(unsigned char dReg, unsigned char sReg, unsigned char immediate, unsigned char* completed){
    registers.rReg[dReg] = registers.rReg[sReg] + immediate;
    *completed = true;
}

void CPU::mul(unsigned char dReg, unsigned char sReg, unsigned char* completed){    
    if(waitTime == 0){
        waitTime = 1;
        return;
    }

    waitTime = 0;
    registers.rReg[dReg] = (registers.rReg[sReg] & 0b1111) * (registers.rReg[sReg] >> 4);
    *completed = true;

}

void CPU::inv(unsigned char dReg, unsigned char sReg, unsigned char* completed){
    registers.rReg[dReg] = ~registers.rReg[sReg];
    *completed = true;
}

void CPU::beq(unsigned char sReg, unsigned char tReg, unsigned char immediate, unsigned char* completed){
    
    if(registers.rReg[sReg] != registers.rReg[tReg]){
        *completed = true;
        return;
    }
    if(waitTime == 0){
        waitTime = 1;
        return;
    }

    waitTime = 0;
    registers.PC = immediate;
    *completed = true;
}

void CPU::bneq(unsigned char sReg, unsigned char tReg, unsigned char immediate, unsigned char* completed){
    if(registers.rReg[sReg] == registers.rReg[tReg]){
        *completed = true;
        return;
    }
    if(waitTime == 0){
        waitTime = 1;
        return;
    }

    waitTime = 0;
    registers.PC = immediate;
    *completed = true;
}

void CPU::blt(unsigned char sReg, unsigned char tReg, unsigned char immediate, unsigned char* completed){
    if(registers.rReg[sReg] >= registers.rReg[tReg]){
        *completed = true;
        return;
    }
    if(waitTime == 0){
        waitTime = 1;
        return;
    }

    waitTime = 0;
    registers.PC = immediate;
    *completed = true;
}


void CPU::load(unsigned char dReg, unsigned char tReg, unsigned char* completed){
    unsigned char* destination = registers.rReg + dReg;
    unsigned char target = registers.rReg[tReg];
    memory->memFetch((unsigned int)target, (unsigned int)1, destination, completed);

}

void CPU::store(unsigned char sReg, unsigned char tReg, unsigned char* completed){
    unsigned char* source = registers.rReg + sReg;
    unsigned char target = registers.rReg[tReg];

    memory->memStore((unsigned int)target, (unsigned int)1, source, completed);
}

void CPU::halt(unsigned char* completed){
    hasHalted = true;
    *completed = true;
}