#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"
#include "types.h"

int main() {
    int *intPtr = alloc(sizeof(int));

    if (intPtr == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr - %p\n", intPtr);

    int *intPtr2 = alloc(sizeof(int));

    if (intPtr2 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr2 - %p\n", intPtr2);

    int *intPtr3 = alloc(50 * sizeof(int));

    if (intPtr3 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr3 - %p\n", intPtr3);

    int *intPtr4 = alloc(21 * sizeof(int));

    if (intPtr4 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr4 - %p\n", intPtr4);

    dealloc(intPtr);
    dealloc(intPtr2);
    dealloc(intPtr3);
    dealloc(intPtr4);

    printf("\n\n\n\n");

    intPtr4 = alloc(21 * sizeof(int));

    if (intPtr4 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr4 - %p\n", intPtr4);
    
    intPtr3 = alloc(50 * sizeof(int));
    
    if (intPtr3 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr3 - %p\n", intPtr3);
    
    intPtr2 = alloc(sizeof(int));
    
    if (intPtr2 == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }
    
    printf("intPtr2 - %p\n", intPtr2);

    intPtr = alloc(sizeof(int));

    if (intPtr == NULL) {
        perror("memory allocation failed!\n");
        exit(1);
    }

    printf("intPtr - %p\n", intPtr);
    
    return 0;
}