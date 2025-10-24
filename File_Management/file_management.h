#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../utils.h"
#include "contiguous.h"
#include "linked.h"
#include "indexed.h"

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

void file_management();
void create_file();
void delete_file();
void show_directory();

// main shell
void file_management(){
    char command[50];
    print_header("📁 Mini File System Simulator");
    cyan("Type 'help' to see commands.\n\n");

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strcmp(command, "help") == 0) {
            cyan("\nAvailable Commands:\n");
            printf(" bit       → Show Bit Vector\n");
            printf(" create    → Create New File\n");
            printf(" show      → Show Directory\n");
            printf(" delete    → Delete File\n");
            printf(" clear     → Clear Screen\n");
            printf(" exit      → Exit Simulator\n\n");
        }
        else if (strcmp(command, "clear") == 0) {
            system("clear");
        }
        else if (strcmp(command, "bit") == 0) {
            display_bit_vector();
        }
        else if (strcmp(command, "create") == 0) {
            create_file();
        }
        else if (strcmp(command, "show") == 0) {
            show_directory();
        }
        else if (strcmp(command, "delete") == 0) {
            delete_file();
        }
        else if (strcmp(command, "exit") == 0) {
            red("💾 Exiting file system...\n");
            sleep(1);
            break;
        }
        else if (strlen(command) == 0) {
            continue;
        }
        else {
            red("❓ Unknown command: %s\n");
            cyan("Type 'help' for available commands.\n");
        }
    }
}

// --- Create File ---
void create_file() {
    char name[30];
    int size;
    int method;

    yellow("Enter file name: ");
    scanf("%s", name);
    yellow("Enter file size (in blocks): ");
    scanf("%d", &size);
    getchar(); // clear input buffer

    if (size > MAX_BLOCKS_PER_FILE) {
        printf("⚠️  File too large. Max size is %d blocks.\n", MAX_BLOCKS_PER_FILE);
        return;
    }
    
    printf("\nChoose allocation method:\n");
    cyan(" 1 → Contiguous\n 2 → Linked\n 3 → Indexed\n");
    yellow("Enter choice: ");
    scanf("%d", &method);
    getchar();

    int free_count = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) if (bit_vector[i] == 0) free_count++;

    if (free_count < size) {
        printf("❌ Not enough free blocks. Only %d blocks available.\n", free_count);
        if (free_count >= 1 && free_count < size)
            cyan("💡 Suggestion: Try Linked allocation (it can use scattered blocks).\n");
        return;
    }

    switch (method) {
        case 1:
            contiguous_allocation(name, size);
            break;
        case 2:
            linked_allocation(name, size);
            break;
        case 3:
            indexed_allocation(name, size);
            break;
        default:
            red("Invalid method.\n");
            return;
    }
}

// --- Delete File ---
void delete_file() {
    char name[30];
    yellow("Enter file name to delete: ");
    scanf("%s", name);
    getchar();

    if (delete_contiguous(name) || delete_linked(name) || delete_indexed(name))
        green("🗑️  File deleted successfully.\n");
    else
        red("❌ File not found.\n");
}

// --- Show Directory ---
void show_directory() {
    cyan("\n📂 Directory Listing:\n");
    show_contiguous_files();
    show_linked_files();
    show_indexed_files();
    printf("-----------------------------------------\n");
}

#endif
