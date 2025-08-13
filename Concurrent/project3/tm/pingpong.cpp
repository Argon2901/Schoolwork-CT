#include "ThreadClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ping.h"
#include "pong.h"
int main(void)
{
  ping  pinger(4);
  pong  ponger(2);
  pinger.Begin();
  ponger.Begin();

  pinger.Join();
  ponger.Join();

  Exit();  
}
