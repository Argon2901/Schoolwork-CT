#include "ThreadClass.h"
#include <cstring>
Semaphore *Chairs;
Mutex *Chops[5];

class phil:public Thread
{
  public:
    phil(int n, int it);
  private:
    int  Number;
    int  iter;
    void ThreadFunc();
};

phil::phil(int n, int it)
{
  Number=n;
  iter=it;
}

void phil::ThreadFunc()
{
 char buf[200];
 int i, Left=Number,
        Right=(Number+1)%5;
 Thread::ThreadFunc();
 for (i=0; i<iter; i++) {
   snprintf(buf,200,"PHILOSOPHER %d WAITS ON Chairs\n",Number);
   write(1,buf,strlen(buf));
   
   Chairs->Wait();
   snprintf(buf,200,"Philosopher %d has a chair, waits on %d and %d\n",Number,Left,Right);
     write(1,buf,strlen(buf));   
     Chops[Left]->Lock();
   snprintf(buf,200,"Philosopher %d has chop %d\n",Number,Left);
     write(1,buf,strlen(buf));   
     
     Chops[Right]->Lock();
     snprintf(buf,200,"Philosopher %d has chop %d\n",Number,Right);
     write(1,buf,strlen(buf));   

     // Eat
     snprintf(buf,200,"Philosopher %d has chops %d and %d\n",Number,Left,Right);
     write(1,buf,strlen(buf));   
     
     Chops[Left]->Unlock();
     Chops[Right]->Unlock();
   Chairs->Signal();
   snprintf(buf,200,"PHILOSOPHER %d DONE\n",Number);
   write(1,buf,strlen(buf));   
   
 }
}

 int main(int argc, char *argv[])
 {
   phil *philosopher[5];
   int iterations;
   
   char buf[200];
   int i;
   
   iterations=atoi(argv[1]);
   Chairs = new Semaphore("Chair Sem",4);

   for (i=0;i<5;i++)
     {
       snprintf(buf,200,"Chopstick %d",i);
       Chops[i]=new Mutex(buf);
     }
   
  
   for (int i=0;i<5;i++){
       philosopher[i]=new phil(i,iterations);
       
       snprintf(buf,200,"Calling Begin for philosopher %d\n",i);
       write(1,buf,strlen(buf));
       philosopher[i]->Begin();
   }

  for (int i=0;i<5;i++){
       snprintf(buf,200,"Calling Join for philosopher %d\n",i);
       write(1,buf,strlen(buf));
       philosopher[i]->Join();
   }
   write(1,"Done\n",5);
 }
 
