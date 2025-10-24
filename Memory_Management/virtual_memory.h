#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <stdio.h>
#include <stdlib.h>

#define PAGE_TABLE_SIZE 8
#define FRAME_COUNT 4

typedef struct Page {
    int page_number;
    int frame_number;
    int valid; // 1 if in memory
} Page;

Page page_table[PAGE_TABLE_SIZE];
int memory_frames[FRAME_COUNT]; // -1 = empty

void init_virtual_memory() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].page_number = i;
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }
    for (int i = 0; i < FRAME_COUNT; i++) memory_frames[i] = -1;
    printf("\033[1;35m[Virtual Memory] Initialized %d pages and %d frames.\n\033[0m", PAGE_TABLE_SIZE, FRAME_COUNT);
}

void load_page(int page_num) {
    // Check if already loaded
    if (page_table[page_num].valid) {
        printf("[VM] Page %d already in frame %d.\n", page_num, page_table[page_num].frame_number);
        return;
    }

    // Find free frame
    for (int i = 0; i < FRAME_COUNT; i++) {
        if (memory_frames[i] == -1) {
            memory_frames[i] = page_num;
            page_table[page_num].frame_number = i;
            page_table[page_num].valid = 1;
            printf("[VM] Loaded page %d into frame %d.\n", page_num, i);
            return;
        }
    }

    // Simple FIFO replacement
    int replaced_page = memory_frames[0];
    memory_frames[0] = page_num;
    page_table[replaced_page].valid = 0;
    page_table[replaced_page].frame_number = -1;
    page_table[page_num].frame_number = 0;
    page_table[page_num].valid = 1;
    printf("[VM] Replaced page %d with page %d in frame 0.\n", replaced_page, page_num);
}

void display_page_table() {
    printf("[VM] Page Table:\n");
    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
        printf("Page %d -> Frame %d [%s]\n",
               page_table[i].page_number,
               page_table[i].frame_number,
               page_table[i].valid ? "Valid" : "Invalid");
}

#endif
