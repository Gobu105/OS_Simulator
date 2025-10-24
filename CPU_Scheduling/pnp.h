/* ========================= pnp.h (Non-preemptive Priority) ========================= */
#ifndef PNP_H
#define PNP_H
#include "../utils.h"

/* ---------- PNP (Non-Preemptive Priority Scheduling) ---------- */
void pnp(PCB input[], int n) {
    print_header("PNP (Non-Preemptive Priority — lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    int done = 0, time = 0;
    int completed[n];
    memset(completed, 0, sizeof(completed));

    while (done < n) {
        int idx = -1;
        int best_pr = INT_MAX;

        // Find available process with highest priority (lowest number)
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        update_state(&procs[idx], "READY");
        update_state(&procs[idx], "RUNNING");

        procs[idx].start_time = time;
        time += procs[idx].bt;
        procs[idx].completion_time = time;

        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;

        update_state(&procs[idx], "TERMINATED");

        completed[idx] = 1;
        done++;
    }

    printf("\n");
    print_table(procs, n, 1);
    free(procs);
}

/* ---------- PNP Gantt Chart ---------- */
void pnpgantt(PCB input[], int n) {
    print_header("PNP (Non-Preemptive Priority — lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    int done = 0, time = 0;
    int completed[n];
    memset(completed, 0, sizeof(completed));

    printf("Gantt Chart:\n");
    while (done < n) {
        int idx = -1;
        int best_pr = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        procs[idx].start_time = time;
        print_gantt_pair(procs[idx].pid, time, time + procs[idx].bt);
        time += procs[idx].bt;

        procs[idx].completion_time = time;
        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;

        completed[idx] = 1;
        done++;
    }

    printf("|\n");
    free(procs);
}

/* ---------- PNP Averages ---------- */
void pnpaverage(PCB input[], int n) {
    print_header("PNP (Non-Preemptive Priority — lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    int done = 0, time = 0;
    int completed[n];
    memset(completed, 0, sizeof(completed));

    while (done < n) {
        int idx = -1;
        int best_pr = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        procs[idx].start_time = time;
        time += procs[idx].bt;
        procs[idx].completion_time = time;

        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;

        completed[idx] = 1;
        done++;
    }

    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* PNP_H */

