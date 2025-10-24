#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "thread.h"
#include "sync.h"
#include "deadlock.h"
#include "../utils.h"

// Main shell entry
void synchronization();

// --- Shell Implementation ---
void synchronization() {
    char command[50];
    print_header("🔁 OS Synchronization Simulator");
    cyan("Type 'help' to see available commands.\n\n");

    while (1) {
        printf("\nsync> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strcmp(command, "help") == 0) {
            cyan("\nAvailable Commands:\n");
            printf(" threads    → Run Thread Synchronization Demo\n");
            printf(" sem        → Run Semaphore Example\n");
            printf(" deadlock   → Run Banker's Algorithm (Deadlock Detection)\n");
            printf(" clear      → Clear Screen\n");
            printf(" exit       → Exit Simulator\n\n");
        }
        else if (strcmp(command, "threads") == 0) {
            cyan("\n🧵 Running Thread Synchronization Demo...\n");
            demo_threads();
        }
        else if (strcmp(command, "sem") == 0) {
            cyan("\n🚦 Running Semaphore Example...\n");
            demo_semaphore();
        }
        else if (strcmp(command, "deadlock") == 0) {
            cyan("\n⚙️  Running Banker's Algorithm...\n");
            run_bankers();
        }
        else if (strcmp(command, "clear") == 0) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
        else if (strcmp(command, "exit") == 0) {
            red("\n👋 Exiting Synchronization Simulator...\n");
            sleep(1);
            break;
        }
        else if (strlen(command) == 0) {
            continue;
        }
        else {
            red("❓ Unknown command!!\n");
            cyan("Type 'help' for available commands.\n");
        }
    }
}

#endif

