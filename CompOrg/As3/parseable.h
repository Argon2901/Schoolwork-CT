#ifndef PARSEABLE_H
#define PARSEABLE_H

#include <stdio.h>


class Parseable{
    public:
        virtual ~Parseable() = default;
        virtual void parse(FILE*) = 0;
    private:
        virtual void reset() = 0;
};

#endif