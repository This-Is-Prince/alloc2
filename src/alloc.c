#include "alloc.h"
#include <sys/_types/_null.h>
#include <unistd.h>
#include "types.h"

void* heap;

void* find_header(void* mem_start, size_t size) {
    header *h = (header*)mem_start;

    if (h->size == 0) {
        if (sbrk(size + sizeof(header)) == NoMem) {
            return NoMem;
        }

        h->size = size;
        h->allocated = true;

        return h;
    } else if (h->size == size && h->allocated == false) {
        h->allocated = true;

        return h;
    } else {
        void* next_mem_start = mem_start + sizeof(header) + h->size;
        return find_header(next_mem_start, size);
    }
}

void* alloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    if (heap == NULL) {
        heap = sbrk(0);
    }

    header *h = find_header(heap, size);
    if (h == NoMem) {
        return NoMem;
    }

    return (void*)h + sizeof(header);
}

void dealloc(void* mem) {
    if (mem == NULL) {
        return;
    }

    header *h = mem - sizeof(header);

    if (h->size > 0 && h->allocated) {
        h->allocated = false;
    }
}