#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H

void contiguous_allocation(char *name,int length) {
    int start;
    printf("Enter start block: ");
    scanf("%d", &start);

    // Check free blocks
    for (int i = start; i < start + length; i++) {
        if (bit_vector[i] == 1) {
            printf("❌ Block %d is already allocated. File creation failed.\n", i);
            return;
        }
    }

    // Allocate
    for (int i = start; i < start + length; i++) {
        bit_vector[i] = 1;
    }

    strcpy(contiguous_filenames[contiguous_count], name);
    contiguous_start_block[contiguous_count] = start;
    contiguous_file_length[contiguous_count] = length;
    contiguous_count++;

    printf("✅ File '%s' created successfully (Contiguous).\n", name);
}

void show_contiguous_files() {
    printf("\n📂 Contiguous Allocation Files:\n");
    printf("%-20s%-15s%-10s\n", "File Name", "Start Block", "Length");
    for (int i = 0; i < contiguous_count; i++) {
        printf("%-20s%-15d%-10d\n",
               contiguous_filenames[i],
               contiguous_start_block[i],
               contiguous_file_length[i]);
    }
    if (contiguous_count == 0) printf("(No files)\n");
}

int delete_contiguous(char *file_name) {
    for (int i = 0; i < contiguous_count; i++) {
        if (strcmp(contiguous_filenames[i], file_name) == 0) {
            for (int j = contiguous_start_block[i];
                 j < contiguous_start_block[i] + contiguous_file_length[i];
                 j++) {
                bit_vector[j] = 0;
            }

            // Shift remaining entries
            for (int k = i; k < contiguous_count - 1; k++) {
                strcpy(contiguous_filenames[k], contiguous_filenames[k + 1]);
                contiguous_start_block[k] = contiguous_start_block[k + 1];
                contiguous_file_length[k] = contiguous_file_length[k + 1];
            }

            contiguous_count--;
            return 1;  // ✅ return success
        }
    }
    return 0;  // ✅ return failure
}

#endif
