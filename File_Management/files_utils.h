#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#define MAX_BLOCKS 100
#define MAX_FILES 50
#define MAX_BLOCKS_PER_FILE 20

typedef struct Block {
    int block_num;
    struct Block *next;
} Block;

typedef struct File {
    char name[30];
    Block *start;
} File;

// ---- GLOBAL BIT VECTOR ----
int bit_vector[MAX_BLOCKS] = {0};

// ---- CONTIGUOUS ALLOCATION DATA ----
char contiguous_filenames[MAX_FILES][30];
int contiguous_start_block[MAX_FILES];
int contiguous_file_length[MAX_FILES];
int contiguous_count = 0;

// ---- LINKED ALLOCATION DATA ----
File linked_files[MAX_FILES];
int linked_count = 0;

// ---- INDEXED ALLOCATION DATA ----
char indexed_filenames[MAX_FILES][30];
int indexed_index_blocks[MAX_FILES];
int indexed_file_blocks[MAX_FILES][MAX_BLOCKS_PER_FILE];
int indexed_length[MAX_FILES];
int indexed_count = 0;

void display_bit_vector() {
    printf("\n📊 Bit Vector:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d ", bit_vector[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

#endif
