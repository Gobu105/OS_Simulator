#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mem_management.h"
#include "device_management.h"
#include "virtual_memory.h"
#include "../utils.h"

#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#define CMD_SIZE 64

void memory_management() {
    char command[CMD_SIZE];

    print_header("🖥️  OS Memory Simulator");
    cyan("Type 'help' to see available commands.\n\n");

    init_memory();
    init_devices();
    init_virtual_memory();

    while (1) {
        printf("Memory> ");
        fgets(command, CMD_SIZE, stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strlen(command) == 0) continue;

        // Exit
        if (strcmp(command, "exit") == 0) {
            red("💾 Exiting OS Shell...\n");
            sleep(1);
            break;
        }

        // Help
        else if (strcmp(command, "help") == 0) {
            cyan("\nAvailable Commands:\n");
            magenta(" --- Memory Management ---\n");
            printf(" mem alloc <size>        → Allocate memory units\n");
            printf(" mem free <start> <size> → Free memory units\n");
            printf(" mem status              → Show memory status\n");
            magenta(" --- Device Management ---\n");
            printf(" dev req <dev> <pid>     → Request a device\n");
            printf(" dev rel <dev>           → Release a device\n");
            printf(" dev status              → Show device status\n");
            magenta(" --- Virtual Memory ---\n");
            printf(" vm load <page>          → Load page into memory\n");
            printf(" vm status               → Show page table\n");
            printf(" exit                    → Exit shell\n\n");
        }

        // --- Memory Management ---
        else if (strncmp(command, "mem alloc ", 10) == 0) {
            int size = atoi(command + 10);
            allocate_memory(size);
        }
        else if (strncmp(command, "mem free ", 9) == 0) {
            int start, size;
            sscanf(command + 9, "%d %d", &start, &size);
            free_memory(start, size);
        }
        else if (strcmp(command, "mem status") == 0) display_memory();

        // --- Device Management ---
        else if (strncmp(command, "dev req ", 8) == 0) {
            int dev, pid;
            sscanf(command + 8, "%d %d", &dev, &pid);
            request_device(dev, pid);
        }
        else if (strncmp(command, "dev rel ", 8) == 0) {
            int dev;
            sscanf(command + 8, "%d", &dev);
            release_device(dev);
        }
        else if (strcmp(command, "dev status") == 0) display_devices();

        // --- Virtual Memory ---
        else if (strncmp(command, "vm load ", 8) == 0) {
            int page;
            sscanf(command + 8, "%d", &page);
            load_page(page);
        }
        else if (strcmp(command, "vm status") == 0) display_page_table();

        else {
            red("❓ Unknown command!!\n");
            cyan("Type 'help' for available commands.\n");
        }
    }
}

#endif
