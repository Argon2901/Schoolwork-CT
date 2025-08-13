#ifndef CacheM
#define CacheM

#include "memory.h"


class Cache : public Parseable{
public:
    Cache(Memory*);
    ~Cache();

    void parse(FILE*);
    void dump();
    void reset();

    void memFetch(unsigned int, unsigned int, unsigned char*, unsigned char*);
    void memStore(unsigned int, unsigned int, unsigned char*, unsigned char*);

private:
    void FFWrite(unsigned char*);

    Memory* memory;
    
    unsigned char CLO = 0; //5 bits max 
    unsigned char* dataArray; 
    unsigned char* validArray; //0 = invalid, 1 = valid, 2 = written
    
    char isActive = 0;
    char flushed = 0;

    const char* flags = "IVW";
};










#endif 