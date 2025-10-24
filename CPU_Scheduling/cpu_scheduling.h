#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../utils.h"
#include "fcfs.h"
#include "sjf.h"
#include "srt.h"
#include "pp.h"
#include "pnp.h"
#include "rr.h"

#ifndef CPU_SCHEDULING_H
#define CPU_SCHEDULING_H

void cpu_scheduling();

// --- Main Shell ---
void cpu_scheduling() {
    char command[64];
    char alg[16];
    int n = 0, quantum = 2;
    PCB *procs = NULL;

    print_header("💻 CPU Scheduling Simulator");
    cyan("Type 'help' to see available commands.\n\n");

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove newline

        if (strlen(command) == 0) continue;

        if (strcmp(command, "help") == 0) {
            cyan("\nAvailable Commands:\n");
            printf(" scheduling   → Enter processes\n");
            printf(" gantt [alg]  → Show Gantt chart for all or specific algorithm\n");
            printf(" table [alg]  → Show table for all or specific algorithm\n");
            printf(" average      → Show average WT and TAT of all algorithms\n");
            printf(" quantum x    → Set RR time quantum\n");
            printf(" clear        → Clear the screen\n");
            printf(" exit         → Exit simulator\n\n");
        }

        else if (strcmp(command, "exit") == 0) {
            red("💾 Exiting CPU scheduling simulator...\n");
            sleep(1);
            break;
        }
        else if (strcmp(command, "clear") == 0) {
            system("clear");
        }
        else if (strcmp(command, "scheduling") == 0) {
            yellow("Enter number of processes: ");
            if (scanf("%d", &n) != 1 || n <= 0) {
                red("❌ Invalid number of processes.\n");
                while (getchar() != '\n');
                continue;
            }

            free(procs);
            procs = (PCB*) malloc(sizeof(PCB) * n);
            if (!procs) {
                fprintf(stderr, "❌ Memory allocation failed.\n");
                exit(1);
            }

            for (int i = 0; i < n; ++i) {
                procs[i].pid = i + 1;

                // Arrival Time
                do {
                    printf("Process %d - Arrival Time: ", i + 1);
                    if (scanf("%d", &procs[i].at) != 1 || procs[i].at < 0) {
                        red("❌ Invalid input! Arrival time must be >= 0.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                } while (1);

                // Burst Time
                do {
                    printf("Process %d - Burst Time: ", i + 1);
                    if (scanf("%d", &procs[i].bt) != 1 || procs[i].bt <= 0) {
                        red("❌ Invalid input! Burst time must be > 0.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                } while (1);

                procs[i].priority = 0;
                procs[i].rt_time = procs[i].bt;
            }

            // Priority entry for PP/PNP
            int need_prio = 0;
            yellow("Do you want to enter priorities for PP/PNP? (1/0): ");
            if (scanf("%d", &need_prio) != 1 || (need_prio != 0 && need_prio != 1)) {
                cyan("Skipping priority entry.\n");
                need_prio = 0;
            }

            if (need_prio) {
                for (int i = 0; i < n; ++i) {
                    do {
                        printf("Priority for P%d (lower = higher): ", procs[i].pid);
                        if (scanf("%d", &procs[i].priority) != 1 || procs[i].priority < 0) {
                            red("❌ Invalid priority! Must be >= 0.\n");
                            while (getchar() != '\n');
                            continue;
                        }
                        break;
                    } while (1);
                }
            }

            // RR Quantum
            do {
                yellow("Enter time quantum for RR (suggested 2): ");
                if (scanf("%d", &quantum) != 1 || quantum <= 0) {
                    red("❌ Invalid quantum! Must be > 0.\n");
                    while (getchar() != '\n');
                    continue;
                }
                break;
            } while (1);

            while (getchar() != '\n'); // clear buffer
            green("✅ Processes entered successfully.\n");
        }

        else if (strncmp(command, "quantum", 7) == 0) {
            int q;
            if (sscanf(command + 7, "%d", &q) == 1 && q > 0) {
                quantum = q;
                printf("RR quantum set to %d\n", quantum);
            } else {
                red("❌ Invalid quantum value.\n");
            }
        }

        else if (strncmp(command, "gantt", 5) == 0 || strncmp(command, "table", 5) == 0) {
            int show_gantt = strncmp(command, "gantt", 5) == 0;
            int show_table = strncmp(command, "table", 5) == 0;

            if (n == 0 || !procs) {
                red("❌ No processes entered yet. Use 'scheduling' first.\n");
                continue;
            }

            yellow("Enter algorithm name (all/fcfs/sjf/srt/pp/pnp/rr): ");
            fgets(alg, sizeof(alg), stdin);
            alg[strcspn(alg, "\n")] = 0;
            if (!is_valid_algo(alg)) strcpy(alg, "all");

            if (show_gantt) {
                if (!strcmp(alg, "fcfs") || !strcmp(alg, "all")) fcfsgantt(procs, n);
                if (!strcmp(alg, "sjf") || !strcmp(alg, "all")) sjfgantt(procs, n);
                if (!strcmp(alg, "srt") || !strcmp(alg, "all")) srtgantt(procs, n);
                if (!strcmp(alg, "pp")  || !strcmp(alg, "all")) ppgantt(procs, n);
                if (!strcmp(alg, "pnp") || !strcmp(alg, "all")) pnpgantt(procs, n);
                if (!strcmp(alg, "rr")  || !strcmp(alg, "all")) rrgantt(procs, n, quantum);
            }

            if (show_table) {
                if (!strcmp(alg, "fcfs") || !strcmp(alg, "all")) fcfs(procs, n);
                if (!strcmp(alg, "sjf") || !strcmp(alg, "all")) sjf(procs, n);
                if (!strcmp(alg, "srt") || !strcmp(alg, "all")) srt(procs, n);
                if (!strcmp(alg, "pp")  || !strcmp(alg, "all")) pp(procs, n);
                if (!strcmp(alg, "pnp") || !strcmp(alg, "all")) pnp(procs, n);
                if (!strcmp(alg, "rr")  || !strcmp(alg, "all")) rr(procs, n, quantum);
            }
        }

        else if (strcmp(command, "average") == 0) {
            if (n == 0 || !procs) {
                red("❌ No processes entered yet. Use 'scheduling' first.\n");
                continue;
            }

            yellow("Enter algorithm name (all/fcfs/sjf/srt/pp/pnp/rr): ");
            fgets(alg, sizeof(alg), stdin);
            alg[strcspn(alg, "\n")] = 0;
            if (!is_valid_algo(alg)) strcpy(alg, "all");

            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all")) fcfsaverage(procs, n);
            if (!strcmp(alg, "sjf") || !strcmp(alg, "all")) sjfaverage(procs, n);
            if (!strcmp(alg, "srt") || !strcmp(alg, "all")) srtaverage(procs, n);
            if (!strcmp(alg, "pp")  || !strcmp(alg, "all")) ppaverage(procs, n);
            if (!strcmp(alg, "pnp") || !strcmp(alg, "all")) pnpaverage(procs, n);
            if (!strcmp(alg, "rr")  || !strcmp(alg, "all")) rraverage(procs, n, quantum);
        }

        else {
            red("❓ Unknown command!!\n");
            cyan("Type 'help' for available commands.\n");
        }
    }

    free(procs);
}

#endif

