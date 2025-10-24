#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 20  // limit for safety

// Worker function
void* worker(void* arg) {
    int id = *(int*)arg;
    printf("🧵 Thread %d is working...\n", id);
    sleep(1 + rand() % 3);  // random delay to simulate work
    printf("✅ Thread %d finished.\n", id);
    return NULL;
}

// Demo function
void demo_threads() {
    int n;
    printf("Enter number of threads to create (1–%d): ", MAX_THREADS);

    if (scanf("%d", &n) != 1) {
        printf("⚠️  Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // clear buffer
        return;
    }

    if (n <= 0) {
        printf("⚠️  Number of threads must be greater than 0.\n");
        return;
    }

    if (n > MAX_THREADS) {
        printf("⚠️  Too many threads! Limit is %d.\n", MAX_THREADS);
        return;
    }

    pthread_t *threads = (pthread_t*)malloc(n * sizeof(pthread_t));
    int *ids = (int*)malloc(n * sizeof(int));
    if (!threads || !ids) {
        printf("❌ Memory allocation failed.\n");
        free(threads);
        free(ids);
        return;
    }

    printf("\nCreating %d threads...\n\n", n);

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            printf("❌ Failed to create thread %d.\n", i + 1);
            n = i; // adjust for join loop
            break;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n✅ All %d threads completed successfully.\n", n);

    free(threads);
    free(ids);
}

#endif

