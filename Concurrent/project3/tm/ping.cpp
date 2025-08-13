#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ping.h"
ping::ping(int i)
{
 executions=i;
}
       
void ping::ThreadFunc()
{  
   Thread::ThreadFunc();
   for (int i=0;i<executions;i++) {
     write(1,"ping\n",5);
   }
   
   Exit();
}
