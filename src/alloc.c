#include "alloc.h"
#include <unistd.h>
#include "types.h"
#include <errno.h>

static void* heap_start = NULL;
static void* heap_end = NULL;

static header* request_more_memory(size_t size) {
    size_t total_alloc_size = size + sizeof(header);

    void* current_break = sbrk(0);
    if (sbrk(total_alloc_size) == ALLOC_FAIL) {
        errno = ENOMEM;
        return NULL;
    }

    heap_end = (void*)current_break + total_alloc_size;
    header* h = (header*)current_break;
    h->size = size;
    h->allocated = true;
    return h;
}

static header* find_free_block(size_t size) {
    header* current = (header*)heap_start;

    while ((void*)current < heap_end) {
        if (!current->allocated && current->size >= size) {
            if (current->size > (size + MIN_BLOCK_SIZE)) {
                header* split_block = (header*)((void*)current + size + sizeof(header));
                split_block->size = current->size - size - sizeof(header);
                split_block->allocated = false;

                current->size = size;
            }

            current->allocated = true;
            return current;
        }

        current = (header*)((void*)current + sizeof(header) + current->size);
    }

    return request_more_memory(size);
}

void* alloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    if (size > MAX_ALLOC_SIZE) {
        errno = EINVAL;
        return NULL;
    }

    if (heap_start == NULL) {
        heap_start = sbrk(0);
        heap_end = heap_start;
        if (heap_start == ALLOC_FAIL) {
            errno = ENOMEM;
            return NULL;
        }
    }

    header* h = find_free_block(size);

    if (h == NULL) {
        return NULL;
    }

    return (void*)h + sizeof(header);
}

void dealloc(void* mem) {
    if (mem == NULL) {
        return;
    }

    header *h = (header*)(mem - sizeof(header));

    if ((void*)h < heap_start || (void*)h >= heap_end) {
        return;
    }

    h->allocated = false;
}