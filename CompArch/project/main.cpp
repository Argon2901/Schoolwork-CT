// --------------------------------------------------------
// NAME : Collin Thompson                 User ID: collint
// DUE DATE : 04/18/2024
// Term Project
// FILE NAME : main.cpp
// PROGRAM PURPOSE :
// Main file for the cache simulator. Recieves input and 
// routes it to the cache objects. 
// --------------------------------------------------------

#include "cache.h"
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char* argv[]){
    if(argc < 3){
        printf("./exec (Block Size words)[4/8] (L1 size KiB)[4/16]\n");
        return 1;
    }

    int L1Size = atoi(argv[2]) * 1024; //num kibibytes * size of kibibyte
    int L2Size = atoi(argv[3]) * 1024; 
    int L3Size = atoi(argv[4]) * 1024; 
    
    int blockSize = atoi(argv[1]) * 4;

    struct Diagnostics* infoL1 = (struct Diagnostics*)calloc(1, sizeof(struct Diagnostics));
    struct Diagnostics* infoL2 = (struct Diagnostics*)calloc(1, sizeof(struct Diagnostics));
    struct Diagnostics* infoL3 = (struct Diagnostics*)calloc(1, sizeof(struct Diagnostics));

    Cache* L3Cache = new Cache(L3Size, blockSize, infoL3, NULL, L3, 2);
    Cache* L2Cache = new Cache(L2Size, blockSize, infoL2, L3Cache, L2, 2);
    Cache* L1Cache = new Cache(L1Size, blockSize, infoL1, L2Cache, L1, 2);
    // Cache* iCache = new Cache(L1Size, blockSize, infoIn, NULL, L1, 2);

    
    char nextchar;
    char operation;
    char referencetype; 
    unsigned int address;

    int totalMemoryAccesses = 0;

    while(scanf("%c", &nextchar) != EOF){
        if(nextchar != '@'){
            //printf("skipping due to not @\n");
            continue;
        }
        totalMemoryAccesses++;
        //separating input 
        scanf("%c", &referencetype);
        scanf("%c", &operation);
        scanf("%x", &address);

        //printf("Working on %c%c%x\n", referencetype, operation, address);

        switch(operation){
        case 'R': 
            operation = 0;
            break;
        case 'W': 
            operation = 1;
            break;
        }       

        switch(referencetype){
        case 'I':
            //iCache->readWrite(address, operation);
            break;
        case 'D':
            L1Cache->readWrite(address, operation);
            break;
        }

        
    }

    printf("Total Memory Calls:     %d\n", totalMemoryAccesses);
    printf("L1 information:\n");
    dumpDiagnostics(infoL1);
    printf("L2 information:\n");
    dumpDiagnostics(infoL2);
    printf("L3 information:\n");
    dumpDiagnostics(infoL3);

    delete L1Cache;
    delete L2Cache;
    delete L3Cache;
    //delete iCache;
    
    return 0;
}


