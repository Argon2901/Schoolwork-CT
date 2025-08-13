#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include "workable.h"

class Memory : public Workable{
public:
    enum Signature{
        FREE,
        CPU, 
        IO,
        CACHE
    };
    void doCycleWork();

    void memFetch(unsigned int, unsigned int, unsigned char*, unsigned char*, Memory::Signature);
    void memStore(unsigned int, unsigned int, unsigned char*, unsigned char*, Memory::Signature);

    void immediateStore(unsigned int, unsigned char*);
    void immediateFetch(unsigned int, unsigned int, unsigned char*);

    void parse(FILE*);
    ~Memory();

private:
    void create(unsigned int);
    void reset();
    void dump(unsigned int, int);
    void set(unsigned int, unsigned int, unsigned char*);
    unsigned char* memory = 0;
    unsigned int memorySize = 0;
    char waitTime = 0;

    enum State{
        idle, 
        waiting,
        completed
    } state = idle;

    Signature device = FREE;
};




#endif
