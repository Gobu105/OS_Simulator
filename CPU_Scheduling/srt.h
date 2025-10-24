/* ========================= srt.h (Shortest Remaining Time - Preemptive) ========================= */
#ifndef SRT_H
#define SRT_H
#include "../utils.h"

/* -------- SRT Core Algorithm (Preemptive) -------- */
void srt(PCB input[], int n) {
    print_header("SRT (Shortest Remaining Time - Preemptive)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    while (completed < n) {
        int idx = -1, min_rt = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].rt_time < min_rt || 
                   (procs[i].rt_time == min_rt && procs[i].at < procs[idx].at)) {
                    min_rt = procs[i].rt_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        if (procs[idx].start_time == -1){
            procs[idx].start_time = time;
            update_state(&procs[idx], "READY");
            update_state(&procs[idx], "RUNNING");
        }

        /* Gantt segmentation (for future reference) */
        if (prev_pid != procs[idx].pid) {
            prev_pid = procs[idx].pid;
            seg_start = time;
        }

        procs[idx].rt_time -= 1;
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
    print_table(procs, n, 0);
    free(procs);
}

/* -------- SRT Gantt Chart (Preemptive) -------- */
void srtgantt(PCB input[], int n) {
    print_header("SRT (Shortest Remaining Time - Preemptive)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1, min_rt = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].rt_time < min_rt || 
                   (procs[i].rt_time == min_rt && procs[i].at < procs[idx].at)) {
                    min_rt = procs[i].rt_time;
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

        procs[idx].rt_time -= 1;
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

/* -------- SRT Averages (Preemptive) -------- */
void srtaverage(PCB input[], int n) {
    print_header("SRT (Shortest Remaining Time - Preemptive)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;

    while (completed < n) {
        int idx = -1, min_rt = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].rt_time < min_rt || 
                   (procs[i].rt_time == min_rt && procs[i].at < procs[idx].at)) {
                    min_rt = procs[i].rt_time;
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

        procs[idx].rt_time -= 1;
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

#endif /* SRT_H */

