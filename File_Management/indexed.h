#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#ifndef INDEXED_H
#define INDEXED_H

void indexed_allocation(char *name,int length) {
    int index_block = -1;

    // Find an empty block for index
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (bit_vector[i] == 0) {
            index_block = i;
            bit_vector[i] = 1;
            break;
        }
    }

    if (index_block == -1) {
        printf("No free block for index!\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < MAX_BLOCKS && count < length; i++) {
        if (bit_vector[i] == 0) {
            indexed_file_blocks[indexed_count][count] = i;
            bit_vector[i] = 1;
            count++;
        }
    }

    if (count < length) {
        printf("Not enough free blocks! File creation failed.\n");
        bit_vector[index_block] = 0;
        return;
    }

    strcpy(indexed_filenames[indexed_count], name);
    indexed_index_blocks[indexed_count] = index_block;
    indexed_length[indexed_count] = length;
    indexed_count++;

    printf("✅ File '%s' created successfully (Indexed).\n", name);
}

void show_indexed_files() {
    printf("\n📂 Indexed Allocation Files:\n");
    printf("%-15s%-15s%-10s%-20s\n", "File Name", "Index Block", "Length", "Blocks");
    for (int i = 0; i < indexed_count; i++) {
        printf("%-15s%-15d%-10d", indexed_filenames[i],
               indexed_index_blocks[i], indexed_length[i]);
        for (int j = 0; j < indexed_length[i]; j++) {
            printf("%d ", indexed_file_blocks[i][j]);
        }
        printf("\n");
    }
    if (indexed_count == 0) printf("(No files)\n");
}

int delete_indexed(char *target) {

    for (int i = 0; i < indexed_count; i++) {
        if (strcmp(indexed_filenames[i], target) == 0) {
            // Free index and data blocks
            bit_vector[indexed_index_blocks[i]] = 0;
            for (int j = 0; j < indexed_length[i]; j++) {
                bit_vector[indexed_file_blocks[i][j]] = 0;
            }

            // Shift array entries
            for (int k = i; k < indexed_count - 1; k++) {
                strcpy(indexed_filenames[k], indexed_filenames[k + 1]);
                indexed_index_blocks[k] = indexed_index_blocks[k + 1];
                indexed_length[k] = indexed_length[k + 1];
                memcpy(indexed_file_blocks[k], indexed_file_blocks[k + 1], sizeof(indexed_file_blocks[k]));
            }

            indexed_count--;
            return 1;
        }
    }
    return 0;
}

#endif
