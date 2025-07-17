#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "sha.h"

volatile static int started = 0;

// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n");
    printf("\n");
    kinit();         // physical page allocator
    kvminit();       // create kernel page table
    kvminithart();   // turn on paging
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    binit();         // buffer cache
    iinit();         // inode table
    fileinit();      // file table
    virtio_disk_init(); // emulated hard disk
    userinit();      // first user process
    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }
  
    if (cpuid() == 0) { // KERNEL IMPLEMENTATION
     
    char *startup = "";

    uint64 start;
    uint64 end;

    // Measure start time for kernel-space computation
    asm volatile("csrr %0, time" : "=r" (start));

    // Perform SHA-256 hashing 1000 times in kernel-space
    for (int i = 0; i < 1000; i++) {
        startup = SHA256("hello"); // SHA-256 computation
    }

    // Measure end time for kernel-space computation
    asm volatile("csrr %0, time" : "=r" (end));

    // Print the time taken in kernel-space for 1000 iterations
    printf("Time in kernel space(startup): %ld\n", (end - start) / 1000);

    // Print the SHA-256 hash of the string
    printf("XV6 started: %s\n", startup);

    // Free the allocated memory for hash string
    kfree(startup);
}

  
  

  scheduler();        
}
