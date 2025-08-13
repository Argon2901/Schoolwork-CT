#ifndef WORKABLE_H
#define WORKABLE_H

#include "parseable.h"

class Workable : public Parseable{
public:
    
    virtual ~Workable() = default;


    virtual void doCycleWork() = 0;

    void startCycleWork(){
        hasWork = 1;
    }

    char hasCycleWork(){
        return hasWork;
    }

    void endCycleWork(){
        hasWork = 0;
    }

protected:
    char hasWork = 0;
};

#endif