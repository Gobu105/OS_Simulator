
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "pcb.h"
#include "states.h"
#include "syscalls.h"
#include "../utils.h"

// Helper: trim leading/trailing whitespace (in-place)
static void trim_whitespace(char *s) {
    char *end;
    // trim leading
    while (isspace((unsigned char)*s)) s++;
    if (*s == 0) {
        // string was all spaces
        *s = '\0';
        return;
    }
    // trim trailing
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    // move trimmed string to start if needed
    if (s != s) { /* no-op to emphasize */ }
    // If original pointer had leading spaces, shift left
    if (s != NULL && s != (char *)0) {
        // this block is intentionally left empty; caller passes buffer start
    }
}

// safer trim that works with buffer start
static void trim_whitespace_inplace(char *buf) {
    // trim leading
    char *start = buf;
    while (*start && isspace((unsigned char)*start)) start++;
    // shift left if needed
    if (start != buf) memmove(buf, start, strlen(start) + 1);
    // trim trailing
    char *end = buf + strlen(buf) - 1;
    while (end >= buf && isspace((unsigned char)*end)) { *end = '\0'; end--; }
}

// Main shell entry
void process_management_shell();

// --- Shell Implementation ---
void main() {
    char command[128];

    print_header("🧠 OS Process Management Simulator");
    printf("Type 'help' to see available commands.\n\n");

    while (1) {
        printf("proc> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            // EOF (Ctrl+D) or read error -> exit cleanly
            printf("\n\n👋 Input closed. Exiting Process Management Simulator...\n");
            return;
        }

        // remove newline and trim whitespace
        trim_whitespace_inplace(command);

        if (strlen(command) == 0) {
            // empty line, just prompt again
            continue;
        }

        if (strcmp(command, "help") == 0) {
            printf("\nAvailable Commands:\n");
            printf(" pcb        → Initialize & Display Process Table\n");
            printf(" states     → Simulate Process State Transitions\n");
            printf(" syscalls   → Demonstrate fork(), exec(), wait()\n");
            printf(" all        → Run All Process Management Demos\n");
            printf(" clear      → Clear Screen\n");
            printf(" exit       → Exit Simulator\n\n");
            continue;
        }

        if (strcmp(command, "pcb") == 0) {
            printf("\n📋 Creating Process Table...\n");
            create_process_table();
            continue;
        }

        if (strcmp(command, "states") == 0) {
            printf("\n🔄 Simulating Process State Transitions...\n");
            simulate_state_transitions();
            continue;
        }

        if (strcmp(command, "syscalls") == 0) {
            printf("\n⚙️  Demonstrating System Calls...\n");
            demo_system_calls();
            continue;
        }

        if (strcmp(command, "all") == 0) {
            printf("\n🚀 Running Full Process Management Demo...\n");
            create_process_table();
            simulate_state_transitions();
            demo_system_calls();
            continue;
        }

        if (strcmp(command, "clear") == 0) {
    #ifdef _WIN32
            system("cls");
    #else
            system("clear");
    #endif
            continue;
        }

        if (strcmp(command, "exit") == 0) {
            printf("\n👋 Exiting Process Management Simulator...\n");
            // short pause for UX (optional)
            sleep(1);
            return; // return from function — ensures clean exit
        }

        // unknown command
        printf("❓ Unknown command: %s\n", command);
        printf("Type 'help' for available commands.\n");
    } // while
}
