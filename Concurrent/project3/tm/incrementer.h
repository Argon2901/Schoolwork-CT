#include "ThreadClass.h"
#include <iostream>
class incrementer : public Thread 
{
public:
  incrementer(int i);
  
private:
  int iterations;
  void ThreadFunc();
};
