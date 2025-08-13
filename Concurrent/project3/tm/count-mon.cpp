#include "ThreadClass.h"
#include "count.h"
#include "incrementer.h"
#include "decrementer.h"
#include <stdlib.h>

#define MAXOPS 1000
Count countMonitor;
int main(int argc, char *argv[])
{
  int ops;
  if (argc!=2) exit(1);
  ops=atoi(argv[1]);
  if ((ops < 0)||(ops > MAXOPS))exit(2);
  
 
  incrementer increments(ops);
  decrementer decrements(ops);
    
  increments.Begin();
  decrements.Begin();

  increments.Join();
  decrements.Join();

  Exit();
}
