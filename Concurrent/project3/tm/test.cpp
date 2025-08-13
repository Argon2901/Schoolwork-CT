#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define DELAY
class test : public Thread 
{
public:
  test(int i);
private:
  int n;
  void ThreadFunc();
};
test::test(int i)
{
  n=i;
}
       
void test::ThreadFunc()
{  
   Thread::ThreadFunc();
   char buf[100];
   
   for (int i=0;i<5;i++)
   {
#ifdef DELAY     
     Delay();
     Delay();
#endif     
     sprintf(buf,"Thread %d in iteration %d\n",n,i);
     write(1,buf,strlen(buf));     
   }
   Exit();
}
int main(void)
{
  test* Run[3];
  int   i;
  for (i=0;i<3;i++) {
    Run[i] = new test(i) ;
    Run[i]->Begin();
  }
  for (i=0;i<3;i++) {
    Run[i]->Join();
  }
  Exit();  
}
