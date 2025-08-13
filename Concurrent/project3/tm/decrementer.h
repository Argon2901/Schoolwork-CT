#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
class decrementer : public Thread 
{
public:
  decrementer(int i);
  
private:
  int iterations;
  void ThreadFunc();
};
