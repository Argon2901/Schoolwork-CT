#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pong.h"
pong::pong(int i)
{
 executions=i;
}
       
void pong::ThreadFunc()
{  
   Thread::ThreadFunc();
   for (int i=0;i<executions;i++) {
     write(1,"pong\n",5);
   }
   
   Exit();
}
