#ifndef CPU_CLOCK
#define CPU_CLOCK

#include <stdio.h>
#include "cpu.h"
#include "parseable.h"
#include "workable.h"

class Clock : public Parseable{
    public:
        void parse(FILE*);
        Clock(Workable**, int);
        ~Clock();
    private:
        void reset();
        void tick(unsigned int);
        void dump();
        unsigned short int count;
        Workable** devices;
        int numDevices;
};




#endif