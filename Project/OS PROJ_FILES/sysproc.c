#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sha.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

extern int counter; 
uint64
sys_resetc(void)
{
  counter=0; //reset the counter
  return 0;
}


uint64
sys_count(void)
{
  return counter; //from syscall
}


uint64
sys_hash(void)
{
    char *str;
    uint64 addr;

    // Get the address of the string argument
    argaddr(0, &addr);

    // Allocate memory for the string
    str = kalloc();
    if (str == 0)
        return -1;
        
    // Fetch the string from user space using the address
    if (fetchstr(addr, str, PGSIZE) < 0) {
        kfree(str);
        return -1;
    }
    
    // Compute SHA-256 hash of the string
    char* hashStr = "";
    hashStr = SHA256(str);
    
    // Print the SHA-256 hash
    printf("SHA-256 hash of '%s': %s\n\n", str, hashStr);
    
    // Free allocated memory for hash string
    kfree(hashStr);

    return 0;
}


uint64
sys_gettime(void)
{
	return r_time();

}







