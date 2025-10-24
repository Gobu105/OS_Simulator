/* ========================= pp.h (Preemptive Priority) ========================= */
#ifndef PP_H
#define PP_H
#include "../utils.h"

/* -------- Preemptive Priority Core Algorithm -------- */
void pp(PCB input[], int n) {
    print_header("PP (Preemptive Priority - lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    while (completed < n) {
        int idx = -1, best_pr = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        if (procs[idx].start_time == -1) {
            procs[idx].start_time = time;
            update_state(&procs[idx], "READY");
            update_state(&procs[idx], "RUNNING");
        }

        if (prev_pid != procs[idx].pid) {
            prev_pid = procs[idx].pid;
            seg_start = time;
        }

        procs[idx].rt_time--;
        time++;

        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;
            update_state(&procs[idx], "TERMINATED");
            completed++;
            prev_pid = -1;
            seg_start = -1;
        }
    }

    printf("\n");
    print_table(procs, n, 1);
    free(procs);
}

/* -------- Preemptive Priority Gantt Chart -------- */
void ppgantt(PCB input[], int n) {
    print_header("PP (Preemptive Priority - lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1, best_pr = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        if (procs[idx].start_time == -1)
            procs[idx].start_time = time;

        if (prev_pid != procs[idx].pid) {
            if (prev_pid != -1)
                print_gantt_pair(prev_pid, seg_start, time);
            prev_pid = procs[idx].pid;
            seg_start = time;
        }

        procs[idx].rt_time--;
        time++;

        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;

            print_gantt_pair(procs[idx].pid, seg_start, time);

            completed++;
            prev_pid = -1;
            seg_start = -1;
        }
    }

    printf("|\n");
    free(procs);
}

/* -------- Preemptive Priority Averages -------- */
void ppaverage(PCB input[], int n) {
    print_header("PP (Preemptive Priority - lower value = higher priority)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    while (completed < n) {
        int idx = -1, best_pr = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr ||
                   (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) {
                    best_pr = procs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        if (procs[idx].start_time == -1)
            procs[idx].start_time = time;

        if (prev_pid != procs[idx].pid) {
            prev_pid = procs[idx].pid;
            seg_start = time;
        }

        procs[idx].rt_time--;
        time++;

        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;
            completed++;
            prev_pid = -1;
            seg_start = -1;
        }
    }

    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* PP_H */

