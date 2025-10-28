#ifndef ALLOC_LIB
#define ALLOC_LIB

#include <sys/_types/_size_t.h>

#define NoMem ((void*)-1)

void* alloc(size_t);
void dealloc(void*);

#endif