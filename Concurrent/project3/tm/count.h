#include "ThreadClass.h"
class Count : public Monitor
{
  public:
    int  Inc();
    int  Dec();
    Count();
  private:
    int  Counter;
};

