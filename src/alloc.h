#ifndef ALLOC_LIB
#define ALLOC_LIB

#include <sys/_types/_size_t.h>

#define ALLOC_FAIL ((void*)-1)
#define MIN_BLOCK_SIZE (sizeof(header) * 2)
#define MAX_ALLOC_SIZE ((1UL << 30) - 1)

void* alloc(size_t);
void dealloc(void*);

#endif