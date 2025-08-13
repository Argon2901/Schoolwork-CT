#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){ 
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return how much memory process is using
int
sys_get_mem_size(void)
{
  return myproc()->sz;
}

// get nice value of process in scheduler
int
sys_getnice(void)
{
  return myproc()->nice;
}


// sets nice value of process in scheduler
int
sys_setnice(void)
{
  int pid, nice;
  argint(0, &pid);
  argint(1, &nice);
  return setprocnice(pid, nice);
}


extern enum schdl_modes schdl_mode;
// sets scheduler policy
int
sys_setSchd(void)
{

  enum schdl_modes p;
  argint(0, (int*)&p);

  switch(p){
    case FIFO:
    case PRIO:
      schdl_mode = p;
      return 0;
    default:
      //oob
      return -1;
  }
}

// gets estimation for process's turnaround time
int
sys_gettt()
{
  return ticks - myproc()->ctime;
}

// gets the number of context switches the process experiences
int
sys_getSwtchCnt()
{
  return myproc()->scount;
}