#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
class ping : public Thread 
{
public:
  ping(int i);
  
private:
  int executions;
  void ThreadFunc();
};
