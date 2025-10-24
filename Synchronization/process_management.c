#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "sync.h"
#include "deadlock.h"

void show_menu();
void handle_choice(int choice);

int main() {
    printf("\n=== OS Synchronization Simulator ===\n");
    show_menu();
    return 0;
}

void show_menu() {
    int choice;
    while (1) {
        printf("\n1. Thread Synchronization Demo");
        printf("\n2. Semaphore Example");
        printf("\n3. Deadlock Detection (Banker's Algorithm)");
        printf("\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        handle_choice(choice);
    }
}

void handle_choice(int choice) {
    switch (choice) {
        case 1: demo_threads(); break;
        case 2: demo_semaphore(); break;
        case 3: run_bankers(); break;
        case 4: exit(0);
        default: printf("Invalid choice!\n");
    }
}
