#ifndef CPUh
#define CPUh

#include "cache.h"
#include "workable.h"
#include "instruction_memory.h"
#include <functional>


class CPU : public Workable{
public:

    void doCycleWork();
    void endCycleWork();

    void parse(FILE*);

    CPU(Cache*, Instruction_Memory*);
    ~CPU();
private:
    void reset();
    void set_register(unsigned char, unsigned char);
    void dump();
    
    void load(unsigned char, unsigned char, unsigned char*);
    void store(unsigned char, unsigned char, unsigned char*);
    void add(unsigned char, unsigned char, unsigned char, unsigned char*);
    void addi(unsigned char, unsigned char, unsigned char, unsigned char*);
    void mul(unsigned char, unsigned char, unsigned char*);
    void inv(unsigned char, unsigned char, unsigned char*);
    void beq(unsigned char, unsigned char, unsigned char, unsigned char*);
    void bneq(unsigned char, unsigned char, unsigned char, unsigned char*);
    void blt(unsigned char, unsigned char, unsigned char, unsigned char*);
    void halt(unsigned char*);
    void parseInstruction(unsigned int);


    struct CPU_Registers{
        unsigned char PC;
        unsigned char* rReg;
    } registers;

    enum State{
        idle,
        fetchI,
        decode,
        memReq,
        memWait
    } state; 

    Cache* memory; 
    Instruction_Memory* iMemory;
    unsigned int instruction;
    std::function<void (unsigned char*)> nextInstruction; //function pointer to the currently worked on instruction
    unsigned char waitTime = 0;
    unsigned char hasHalted = 0;

    int tickCount = 0;
};




#endif