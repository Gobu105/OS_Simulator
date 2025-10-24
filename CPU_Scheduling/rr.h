/* ========================= rr.h (Round Robin) ========================= */
#ifndef RR_H
#define RR_H
#include "../utils.h"

/* -------- Round Robin Core Algorithm -------- */
void rr(PCB input[], int n, int quantum) {
    print_header("RR (Round Robin)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    int in_queue[1000];
    memset(in_queue, 0, sizeof(in_queue));

    /* Enqueue processes that arrive at time 0 */
    for (int i = 0; i < n; ++i)
        if (procs[i].at == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }

    while (completed < n) {
        if (front == rear) {
            /* No process ready -> jump to next arrival */
            int next_time = INT_MAX, idx = -1;
            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].rt_time > 0 && procs[i].at < next_time) {
                    next_time = procs[i].at;
                    idx = i;
                }

            if (idx == -1) break;
            time = procs[idx].at;

            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            continue;
        }

        int cur = queue[front++];

        if (procs[cur].start_time == -1){
            procs[cur].start_time = time;
            update_state(&procs[cur], "READY");
            update_state(&procs[cur], "RUNNING");
        }

        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;

        /* Enqueue new arrivals */
        for (int i = 0; i < n; ++i)
            if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }

        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur;  /* Requeue process */
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;
            update_state(&procs[cur], "TERMINATED");
            completed++;
        }
    }

    printf("\n");
    print_table(procs, n, 0);
    free(procs);
}

/* -------- Round Robin Gantt Chart -------- */
void rrgantt(PCB input[], int n, int quantum) {
    print_header("RR (Round Robin)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    int in_queue[1000];
    memset(in_queue, 0, sizeof(in_queue));

    printf("Gantt Chart:\n");

    for (int i = 0; i < n; ++i)
        if (procs[i].at == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }

    int prev_pid = -1, seg_start = -1;

    while (completed < n) {
        if (front == rear) {
            int next_time = INT_MAX, idx = -1;
            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].rt_time > 0 && procs[i].at < next_time) {
                    next_time = procs[i].at;
                    idx = i;
                }

            if (idx == -1) break;
            time = procs[idx].at;

            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            continue;
        }

        int cur = queue[front++];

        if (procs[cur].start_time == -1)
            procs[cur].start_time = time;

        if (prev_pid != procs[cur].pid) {
            if (prev_pid != -1)
                print_gantt_pair(prev_pid, seg_start, time);
            prev_pid = procs[cur].pid;
            seg_start = time;
        }

        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;

        for (int i = 0; i < n; ++i)
            if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }

        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur;
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;

            print_gantt_pair(procs[cur].pid, seg_start, time);

            completed++;
            prev_pid = -1;
            seg_start = -1;
        }
    }

    printf("|\n");
    free(procs);
}

/* -------- Round Robin Averages -------- */
void rraverage(PCB input[], int n, int quantum) {
    print_header("RR (Round Robin)");
    PCB *procs = copy_procs(input, n);

    for (int i = 0; i < n; ++i) {
        procs[i].rt_time = procs[i].bt;
        procs[i].start_time = -1;
    }

    int time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    int in_queue[1000];
    memset(in_queue, 0, sizeof(in_queue));

    for (int i = 0; i < n; ++i)
        if (procs[i].at == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }

    while (completed < n) {
        if (front == rear) {
            int next_time = INT_MAX, idx = -1;
            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].rt_time > 0 && procs[i].at < next_time) {
                    next_time = procs[i].at;
                    idx = i;
                }

            if (idx == -1) break;
            time = procs[idx].at;

            for (int i = 0; i < n; ++i)
                if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            continue;
        }

        int cur = queue[front++];

        if (procs[cur].start_time == -1)
            procs[cur].start_time = time;

        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;

        for (int i = 0; i < n; ++i)
            if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }

        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur;
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;
            completed++;
        }
    }

    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* RR_H */

