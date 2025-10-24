#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#ifndef LINKED_H
#define LINKED_H

void linked_allocation(char *name,int length) {
    int count = 0;

    if (linked_count >= MAX_FILES) {
        printf("File limit reached.\n");
        return;
    }

    Block *head = NULL, *prev = NULL;
    for (int i = 0; i < MAX_BLOCKS && count < length; i++) {
        if (bit_vector[i] == 0) {
            Block *new_block = (Block *)malloc(sizeof(Block));
            new_block->block_num = i;
            new_block->next = NULL;

            if (prev)
                prev->next = new_block;
            else
                head = new_block;

            prev = new_block;
            bit_vector[i] = 1;
            count++;
        }
    }

    if (count < length) {
        printf("Not enough free blocks! File creation failed.\n");
        return;
    }

    strcpy(linked_files[linked_count].name, name);
    linked_files[linked_count].start = head;
    linked_count++;

    printf("✅ File '%s' created successfully (Linked).\n", name);
}

void show_linked_files() {
    printf("\n📂 Linked Allocation Files:\n");
    printf("%-20s%-15s\n", "File Name", "Blocks");
    for (int i = 0; i < linked_count; i++) {
        printf("%-20s", linked_files[i].name);
        Block *temp = linked_files[i].start;
        while (temp) {
            printf("%d -> ", temp->block_num);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    if (linked_count == 0) printf("(No files)\n");
}

int delete_linked(char *target) {
    for (int i = 0; i < linked_count; i++) {
        if (strcmp(linked_files[i].name, target) == 0) {
            Block *temp = linked_files[i].start;
            while (temp) {
                bit_vector[temp->block_num] = 0;
                Block *to_free = temp;
                temp = temp->next;
                free(to_free);
            }

            // Shift array entries
            for (int k = i; k < linked_count - 1; k++) {
                linked_files[k] = linked_files[k + 1];
            }

            linked_count--;
            return 1;
        }
    }
    return 0;
}
#endif
