// kernel/kalloc.h
#ifndef _KALLOC_H_
#define _KALLOC_H_

void* kalloc(void);
void  kfree(void*);
void  kinit(void);

#endif // _KALLOC_H_
