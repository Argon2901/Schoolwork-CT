#include "ThreadClass.h"
#include <iostream>
#include "count.h"
Count::Count(void)
{ Counter = 0; }

int Count::Inc()
{
  int newValue;
  
   MonitorBegin();
      Counter++;
      newValue=Counter;
      cout << "Monitor: Counter incremented to " << Counter << " newValue is " << newValue << "\n";
      fflush(stdout);
      
   MonitorEnd();
   return newValue;
}
int Count::Dec()
{
  int newValue;
  
   MonitorBegin();
      Counter--;
      newValue=Counter;
      cout << "Monitor: Counter decremented to " << Counter << " newValue is " << newValue << "\n";
      fflush(stdout);      
   MonitorEnd();
   return newValue;
}
