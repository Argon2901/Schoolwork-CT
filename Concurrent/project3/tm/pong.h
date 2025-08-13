#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
class pong : public Thread 
{
public:
  pong(int n);
  
private:
  int executions;
  void ThreadFunc();
};
