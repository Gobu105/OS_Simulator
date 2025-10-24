#ifndef MEM_MANAGEMENT_H
#define MEM_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 64 // total memory units

int memory[MEMORY_SIZE]; // 0 = free, 1 = occupied

void init_memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) memory[i] = 0;
    printf("\033[1;35m[Memory] Initialized %d units.\n\033[0m", MEMORY_SIZE);
}

void allocate_memory(int size) {
    int start = -1, count = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            if (start == -1) start = i;
            count++;
            if (count == size) break;
        } else {
            start = -1;
            count = 0;
        }
    }
    if (count == size) {
        for (int i = start; i < start + size; i++) memory[i] = 1;
        printf("[Memory] Allocated %d units at address %d.\n", size, start);
    } else {
        red("[Memory] Allocation failed. Not enough memory.\n");
    }
}

void free_memory(int start, int size) {
    for (int i = start; i < start + size && i < MEMORY_SIZE; i++) memory[i] = 0;
    printf("[Memory] Freed %d units starting at address %d.\n", size, start);
}

void display_memory() {
    cyan("[Memory] Status: ");
    for (int i = 0; i < MEMORY_SIZE; i++) printf("%d", memory[i]);
    printf("\n");
}

#endif
