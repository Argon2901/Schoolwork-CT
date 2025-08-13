// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 04/18/2024
// Term Project
// FILE NAME : cache.cpp
// PROGRAM PURPOSE :
// Implements the functions declared in cache.h
// --------------------------------------------------------

#include "cache.h"
#include <stdlib.h>
#include <tgmath.h>


int Cache::indexFirstNonZeroBit(int mask){
    for(int i = 0; i < 32; i++){
        if(!(mask & (0x1 << i))){
            return i;
        }
    }
    return -1;
}

int Cache::getRawHit(){
    return (int)type;
}


Cache::Cache(int cacheSize, int blockSize, struct Diagnostics* info, Cache* nextCache, enum CacheType type, int busClockCycles){
    this->info = info; 
    this->nextCache = nextCache;
    this->type = type;
    this->roundTripTime = busClockCycles;

    //block size - 1 looks like 00000111, cache size-1 looks like 00011111, index bits are 00011000
    INDEX_OFFSET = (0xFFFFFFFF & (cacheSize - 1)) & ~(0xFFFFFFFF & (blockSize - 1)); 
    //addr == 10010110, cacheSize = 00011111, tag = 100
    TAG_OFFSET = 0xFFFFFFFF & ~(cacheSize - 1);

    //blocksize - 1 looks like 00000111, finds 3
    INDEX_SHIFT = indexFirstNonZeroBit(blockSize - 1);

    
    int indices = cacheSize / blockSize;

    tagMemory = (unsigned int*)calloc(indices, 4);


    // printf("block bits   = %08x\n", blockSize - 1);
    // printf("cache bits   = %08x\n", cacheSize - 1);
    // printf("index offset = %08x\n", INDEX_OFFSET);
    // printf("tag offset   = %08x\n", TAG_OFFSET);
    // printf("index shift  = %d\n", INDEX_SHIFT);
    // printf("num indexes  = %d\n", indices);
}

Cache::~Cache(){
    free(tagMemory);
}

void Cache::readWrite(int addr, char op){ //0 load, 1 store
    unsigned int tag = (addr & TAG_OFFSET);
    unsigned int index = (addr & INDEX_OFFSET) >> INDEX_SHIFT;
    //printf("cache: %u tag: %x index: %x\n", (unsigned int)type, tag, index);
    unsigned int retrievedTag = tagMemory[index];

    
    
    if((retrievedTag & TAG_OFFSET) == tag && (retrievedTag & VALID_OFFSET)){ //hit
        info->clockTicks += type + roundTripTime; //cache access + bus cycles between caches 
        info->hits++;
    } else{ //misses
        info->misses++;

        if((retrievedTag & DIRTY_OFFSET) && (retrievedTag & VALID_OFFSET)){ //valid and dirty
            if(op){ //marking because of read miss or write miss
                info->readMissWrites++;
            } else{
                info->writeMissWrites++;
            }

            if(nextCache == NULL){ //next is main memory
                info->clockTicks += MAIN + 2 + MAIN + roundTripTime; //main access round trip plus writing back time
            } else{ //next is another cache
                info->clockTicks += 2;
                //printf("writeback\n");
                nextCache->readWrite(retrievedTag | index, 1); //chase down and mark dirty
                nextCache->readWrite(addr, 0);
            }

        } else{ //invalid or valid and clean 

            if(nextCache == NULL){ //next is main memory 
                info->clockTicks += MAIN + roundTripTime + 2; //main access + bus cycles between caches
            } else{
                nextCache->readWrite(addr, op);
            }
            tagMemory[index] = tag | VALID_OFFSET; //sets and validates    
        }
    }


    if(op){ //mark dirty 
        tagMemory[index] = tagMemory[index] | DIRTY_OFFSET;
    }
}


void dumpDiagnostics(struct Diagnostics* info){
    printf("Clock ticks:            %-lld \n", info->clockTicks);
    printf("Cache hits:             %-lld \n", info->hits);
    printf("Cache misses:           %-lld \n", info->misses);
    printf("Cache read writeback:   %-lld \n", info->writeMissWrites);
    printf("Cache write writeback:  %-lld \n", info->readMissWrites);

}