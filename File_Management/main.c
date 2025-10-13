#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"
#include "contiguous.h"
#include "linked.h"
#include "indexed.h"

void create_file();
void delete_file();
void show_directory();

// main shell
int main() {
    char command[50];
    printf("📁 Mini File System Simulator\n");
    printf("-----------------------------------------\n");
    printf("Type 'help' to see commands.\n\n");

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strcmp(command, "help") == 0) {
            printf("\nAvailable Commands:\n");
            printf(" bit       → Show Bit Vector\n");
            printf(" create    → Create New File\n");
            printf(" show      → Show Directory\n");
            printf(" delete    → Delete File\n");
            printf(" exit      → Exit Simulator\n\n");
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
            printf("💾 Exiting file system...\n");
            sleep(1);
            break;
        }
        else if (strlen(command) == 0) {
            continue;
        }
        else {
            printf("❓ Unknown command: %s\n", command);
            printf("Type 'help' for available commands.\n");
        }
    }

    return 0;
}

// --- Create File ---
void create_file() {
    char name[30];
    int size;
    int method;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file size (in blocks): ");
    scanf("%d", &size);
    getchar(); // clear input buffer

    if (size > MAX_BLOCKS_PER_FILE) {
        printf("⚠️  File too large. Max size is %d blocks.\n", MAX_BLOCKS_PER_FILE);
        return;
    }
    
    printf("\nChoose allocation method:\n");
    printf(" 1 → Contiguous\n 2 → Linked\n 3 → Indexed\n");
    printf("Enter choice: ");
    scanf("%d", &method);
    getchar();

    int free_count = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) if (bit_vector[i] == 0) free_count++;

    if (free_count < size) {
        printf("❌ Not enough free blocks. Only %d blocks available.\n", free_count);
        if (free_count >= 1 && free_count < size)
            printf("💡 Suggestion: Try Linked allocation (it can use scattered blocks).\n");
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
            printf("Invalid method.\n");
            return;
    }
}

// --- Delete File ---
void delete_file() {
    char name[30];
    printf("Enter file name to delete: ");
    scanf("%s", name);
    getchar();

    if (delete_contiguous(name) || delete_linked(name) || delete_indexed(name))
        printf("🗑️  File '%s' deleted successfully.\n", name);
    else
        printf("❌ File '%s' not found.\n", name);
}

// --- Show Directory ---
void show_directory() {
    printf("\n📂 Directory Listing:\n");
    show_contiguous_files();
    show_linked_files();
    show_indexed_files();
    printf("-----------------------------------------\n");
}

