#ifndef ALLOC_TYPES_LIB
#define ALLOC_TYPES_LIB

#include <stdbool.h>
#include <stdint.h>

#define Packed __attribute__((packed))
#define Unused __attribute__((unused))

struct Packed _header {
    uint32_t size: 30;
    bool allocated: 1;
    bool Unused reserved: 1;
};

typedef struct Packed _header header;

#endif