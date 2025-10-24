#ifndef STATES_H
#define STATES_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pcb.h"
#include "../utils.h"

extern PCB process_table[MAX_PROCESSES]; // use from pcb.c

void simulate_state_transitions() {
    print_header("Process State Transitions");

    for (int i = 0; i < MAX_PROCESSES; i++) {
        strcpy(process_table[i].state, "READY");
        yellow("Process moved to READY state\n");
        delay(300);

        strcpy(process_table[i].state, "RUNNING");
        green("Process is RUNNING\n");
        delay(500);

        strcpy(process_table[i].state, "WAITING");
        cyan("Process waiting for I/O\n");
        delay(400);

        strcpy(process_table[i].state, "TERMINATED");
        red("Process TERMINATED\n");
        delay(300);

        printf("\n");
    }
}

#endif
