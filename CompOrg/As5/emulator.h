#ifndef EMULATOR
#define EMULATOR

#include "clock.h"
#include "cpu.h"
#include "memory.h"
#include "workable.h"
#include "parseable.h"

#include <stdio.h>

class Emulator{
public:
    Emulator(char*);
    ~Emulator();
    void start();
    void end();
private:
    char* filepath;
    FILE* file;
    Parseable** devices; //memory, cpu, clock, imemory
    Workable** workables; //memory, cpu
    int deviceCount = 6;
    int workableCount = 3;
};




#endif