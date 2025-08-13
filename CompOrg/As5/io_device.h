#ifndef IODEVICE
#define IODEVICE

#include "stdio.h"
#include "clock.h"
#include "memory.h"

class IO : public Workable{
public:    
    void parse(FILE*);
    void doCycleWork();
    IO(Clock*, Memory*);

private:
    void reset();
    void load(char*);
    void dump();

    int currentTick;
    FILE* file;
    char* filepath;
    Clock* clock;
    Memory* memory;

    enum State{
        idle, 
        waiting,
        working
    } state = idle;

    struct EventInfo{
        int tick;
        unsigned char operation; // 1 load, 0 store 
        int reg; 
        int data;
    } eventInfo;

};


#endif