#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifndef SHELL_H
#define SHELL_H
#include"../Process_Management/process_management.h"
#include"../CPU_Scheduling/cpu_scheduling.h"
#include"../Memory_Management/memory_management.h"
#include"../File_Management/file_management.h"
#include"../Synchronization/synchronization.h"
#include"../utils.h"

void shell() {
    char command[50];

    print_header("🐚 Shell: Welcome to Mini OS!");
    cyan("🧰 Available OS Commands / Modules:\n");
    printf("------------------------------------------------------------\n");
    printf(" process      → Simulate Process Management\n");
    printf(" cpu          → Simulate CPU Scheduling\n");
    printf(" memory       → Simulate Memory Management\n");
    printf(" file         → Simulate File Management\n");
    printf(" sync         → Simulate Synchronization\n");
    printf(" time         → Show current system time\n");
    printf(" clear        → Clear the screen\n");
    printf(" exit         → Shut down system\n\n");
    printf("------------------------------------------------------------\n\n");
    cyan("Type 'help' to see available commands or 'exit' to shut down.\n\n");

    while (1) {
        printf("mini-os> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strcmp(command, "exit") == 0  ) {
            yellow("🔚 Shutting down...\n");
            sleep(2);
            break;
        } 
        else if (strcmp(command, "help") == 0) {
            cyan("\nAvailable Commands:\n");
            printf(" process      → Simulate Process Management\n");
            printf(" cpu          → Simulate CPU Scheduling\n");
            printf(" memory       → Simulate Memory Management\n");
            printf(" file         → Simulate File Management\n");
            printf(" sync         → Simulate Synchronization\n");
            printf(" time         → Show current system time\n");
            printf(" clear        → Clear the screen\n");
            printf(" exit         → Shut down system\n\n");
        } 
        else if (strcmp(command, "time") == 0) {
            system("date");
        }
        else if (strcmp(command, "clear") == 0) {
            system("clear");
        }
        else if (strcmp(command, "process") == 0) {
            process_management();
        }
        else if (strcmp(command, "cpu") == 0) {
            cpu_scheduling();
        }
        else if (strcmp(command, "memory") == 0) {
            memory_management();
        }
        else if (strcmp(command, "file") == 0) {
            file_management();
        }
        else if (strcmp(command, "sync") == 0) {
            synchronization();
        }
        else if (strlen(command) == 0) {
            continue; // ignore empty input
        }
        else {
            red("❓ Unknown command!!\n");
            cyan("Type 'help' to see available commands.\n\n");
        }
    }
}

#endif
