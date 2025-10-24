#ifndef PCB_H
#define PCB_H

#define MAX_PROCESSES 5
#include <stdio.h>
#include <string.h>
#include"../utils.h"

void create_process_table();
void display_processes();

static PCB process_table[MAX_PROCESSES];

void create_process_table() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_table[i].pid = i + 1;
        strcpy(process_table[i].state, "NEW");
        process_table[i].priority = i + 1;
    }
    magenta("\nProcess Table Initialized.\n");
    display_processes();
}

void display_processes() {
    printf("\n%-10s %-15s %-10s\n", "PID", "STATE", "PRIORITY");
    printf("----------------------------------\n");
    for (int i = 0; i < MAX_PROCESSES; i++)
        printf("%-10d %-15s %-10d\n",
               process_table[i].pid,
               process_table[i].state,
               process_table[i].priority);
}

#endif
