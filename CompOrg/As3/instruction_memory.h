#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include "parseable.h"

class Instruction_Memory : public Parseable{
public:
    Instruction_Memory(){};
    ~Instruction_Memory();

    unsigned int fetchI(unsigned int);
    void parse(FILE*);
private:
    void create(unsigned int);
    void reset();
    void dump(unsigned int, int);
    void set(unsigned int, FILE*);
    unsigned int* memory;
    int size = 0;
};

#endif