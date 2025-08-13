#include "ThreadClass.h"
#include <iostream>
#include "decrementer.h"
#include "count.h"
#include <stdio.h>
extern Count countMonitor;

decrementer::decrementer(int i)
{
  iterations=i;
}
       
void decrementer::ThreadFunc()
{
   int newValue;
   char buf[200];
   Thread::ThreadFunc();
   for (int i=0;i<iterations;i++) {
      newValue=countMonitor.Dec();
      sprintf(buf,"Decrementer sets value to %d in iteration %d\n",newValue,i);
      cout << buf;
      fflush(stdout);      
   }
   
   Exit();
}
