#ifndef DEADLOCK_H
#define DEADLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utils.h"

void run_bankers() {
    int n, m; // n = number of processes, m = number of resources
    int **alloc, **max, **need, *avail;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Allocate memory for matrices
    alloc = (int **)malloc(n * sizeof(int *));
    max   = (int **)malloc(n * sizeof(int *));
    need  = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        alloc[i] = (int *)malloc(m * sizeof(int));
        max[i]   = (int *)malloc(m * sizeof(int));
        need[i]  = (int *)malloc(m * sizeof(int));
    }
    avail = (int *)malloc(m * sizeof(int));

    // Input allocation matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input max matrix
    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input available resources
    printf("\nEnter Available Resources (%d):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    print_header("Banker's Algorithm - Deadlock Avoidance");

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    bool *finish = (bool *)calloc(n, sizeof(bool));
    int *safeSeq = (int *)malloc(n * sizeof(int));
    int count = 0;

    // Safety algorithm
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > avail[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            red("\nSystem is in UNSAFE STATE (Deadlock possible!)\n");
            goto cleanup;
        }
    }

    green("\nSystem is in SAFE STATE.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

cleanup:
    for (int i = 0; i < n; i++) {
        free(alloc[i]);
        free(max[i]);
        free(need[i]);
    }
    free(alloc);
    free(max);
    free(need);
    free(avail);
    free(finish);
    free(safeSeq);
}

#endif
