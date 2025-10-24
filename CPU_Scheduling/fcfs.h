/* ========================= fcfs.h ========================= */
#ifndef FCFS_H
#define FCFS_H
#include "../utils.h"

/* ---------- FCFS (First Come First Serve) ---------- */
void fcfs(PCB input[], int n) {
    print_header("FCFS (First Come First Serve)");
    PCB *procs = copy_procs(input, n);

    // Sort by arrival time, then PID
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (procs[i].at > procs[j].at ||
               (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                PCB tmp = procs[i];
                procs[i] = procs[j];
                procs[j] = tmp;
            }

    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at)
            time = procs[i].at; // CPU idle

        update_state(&procs[i], "READY");
        update_state(&procs[i], "RUNNING");

        procs[i].start_time = time;
        time += procs[i].bt;
        procs[i].completion_time = time;

        procs[i].tat = procs[i].completion_time - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].resp = procs[i].start_time - procs[i].at;

        update_state(&procs[i], "TERMINATED");
    }

    printf("\n");
    print_table(procs, n, 1);
    free(procs);
}

/* ---------- Gantt Chart ---------- */
void fcfsgantt(PCB input[], int n) {
    print_header("FCFS (First Come First Serve) — Gantt Chart");
    PCB *procs = copy_procs(input, n);

    // Sort by arrival time, then PID
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (procs[i].at > procs[j].at ||
               (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                PCB tmp = procs[i];
                procs[i] = procs[j];
                procs[j] = tmp;
            }

    int time = 0;
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at)
            time = procs[i].at;
        procs[i].start_time = time;

        print_gantt_pair(procs[i].pid, time, time + procs[i].bt);
        time += procs[i].bt;
    }
    printf("|\n");
    free(procs);
}

/* ---------- Averages ---------- */
void fcfsaverage(PCB input[], int n) {
    print_header("FCFS (First Come First Serve) — Averages");
    PCB *procs = copy_procs(input, n);

    // Sort by arrival, then PID
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (procs[i].at > procs[j].at ||
               (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                PCB tmp = procs[i];
                procs[i] = procs[j];
                procs[j] = tmp;
            }

    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at)
            time = procs[i].at;
        procs[i].start_time = time;
        time += procs[i].bt;
        procs[i].completion_time = time;
        procs[i].tat = procs[i].completion_time - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].resp = procs[i].start_time - procs[i].at;
    }

    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* FCFS_H */

