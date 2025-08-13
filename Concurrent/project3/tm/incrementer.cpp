#include "ThreadClass.h"
#include <iostream>
#include "incrementer.h"
#include "count.h"
#include <stdio.h>
extern Count countMonitor;

incrementer::incrementer(int i)
{
 iterations=i;
}
       
void incrementer::ThreadFunc()
{
  int newValue;
  char buf[200];
  
   Thread::ThreadFunc();
   for (int i=0;i<iterations;i++) {
      newValue=countMonitor.Inc();
      sprintf(buf,"Incrementer sets value to %d in iteration %d\n",newValue,i);
      cout << buf;
      fflush(stdout);      
   }
      
   Exit();
}
