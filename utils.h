

/* ========================= utils.h ========================= */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define MAX_BLOCKS 100
#define MAX_FILES 50
#define MAX_BLOCKS_PER_FILE 20


typedef struct {
    int pid;
    int at;    /* Arrival Time */
    int bt;    /* Burst Time */
    int rt_time; /* Remaining Time (used in preemptive algos) */
    int priority; /* lower value -> higher priority */

    /* computed */
    int start_time; /* first time the process gets CPU */
    int completion_time;
    int tat; /* Turnaround time */
    int wt;  /* Waiting time */
    int resp; /* Response time */
} Process;

void print_gantt_pair(int pid, int s, int e) {
    printf("| P%d (%d-%d) ", pid, s, e);
}

void print_table(Process procs[], int n, int with_priority) {
    int i;
    double total_wt = 0, total_tat = 0, total_rt = 0;
    if (with_priority) {
        printf("\nPID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");
    } else {
        printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    }
    for (i = 0; i < n; ++i) {
        if (with_priority) printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].priority, procs[i].start_time, procs[i].completion_time, procs[i].tat, procs[i].wt, procs[i].resp);
        else printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].start_time, procs[i].completion_time, procs[i].tat, procs[i].wt, procs[i].resp);
    }
}

/* Copy processes array */
Process *copy_procs(Process src[], int n) {
    Process *dst = malloc(sizeof(Process) * n);
    for (int i = 0; i < n; ++i) dst[i] = src[i];
    return dst;
}

/* Average Time Calculator */
void print_average(Process procs[], int n){
    int i;
    double total_wt = 0, total_tat = 0, total_rt = 0;
    for (i = 0; i < n; ++i) {
        total_wt += procs[i].wt;
        total_tat += procs[i].tat;
        total_rt += procs[i].resp;
    }
    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\nAvg RT = %.2f\n", total_wt / n, total_tat / n, total_rt / n);
}

int is_valid_algo(const char *alg) {
    const char *valid_algos[] = {"all", "fcfs", "sjf", "srt", "pp", "pnp", "rr"};
    int count = sizeof(valid_algos) / sizeof(valid_algos[0]);
    for (int i = 0; i < count; i++) {
        if (strcmp(alg, valid_algos[i]) == 0)
            return 1;
    }
    return 0;
}


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

void red(const char *text) {
    printf("\033[1;31m%s\033[0m", text);
}

void green(const char *text) {
    printf("\033[1;32m%s\033[0m", text);
}

void yellow(const char *text) {
    printf("\033[1;33m%s\033[0m", text);
}

void cyan(const char *text) {
    printf("\033[1;36m%s\033[0m", text);
}

void print_header(const char *title) {
    cyan("\n========================================\n");
    yellow(title);
    cyan("\n========================================\n");
}

void delay(int ms) {
    usleep(ms * 1000);
}

#endif /* UTILS_H */
