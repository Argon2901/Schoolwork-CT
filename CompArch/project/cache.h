// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 04/18/2024
// Term Project
// FILE NAME : cache.h
// PROGRAM PURPOSE :
// Creates a cache and relevant data structures for the 
// cache simulator.
// --------------------------------------------------------

#pragma once

enum CacheType{
    L1 = 1, 
    L2 = 16, 
    L3 = 64,
    MAIN = 100
};

struct Diagnostics{
    long long clockTicks;
    long long hits;
    long long misses;
    long long writeMissWrites;
    long long readMissWrites;
};

void dumpDiagnostics(struct Diagnostics*);

class Cache{
    struct Diagnostics* info;

    int roundTripTime;

    unsigned int* tagMemory;
    const unsigned int VALID_OFFSET = 0x00000002;
    const unsigned int DIRTY_OFFSET = 0x00000001;
    unsigned int TAG_OFFSET;
    unsigned int INDEX_OFFSET; 
    unsigned int INDEX_SHIFT;

    enum CacheType type;

    Cache* nextCache; 

    int indexFirstNonZeroBit(int);
    
    public: 
    int getRawHit();

    Cache(int, int, struct Diagnostics*, Cache*, enum CacheType, int);
    ~Cache();
    void readWrite(int, char);
};

