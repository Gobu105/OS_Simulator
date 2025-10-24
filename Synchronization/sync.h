#ifndef SYNC_H
#define SYNC_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "../utils.h"

sem_t mutex;

void* sem_worker(void* arg) {
    sem_wait(&mutex);
    printf("Critical section entered by thread %ld\n", pthread_self());
    sleep(1);
    printf("Thread %ld leaving critical section\n", pthread_self());
    sem_post(&mutex);
    return NULL;
}

void demo_semaphore() {
    pthread_t t1, t2, t3;
    sem_init(&mutex, 0, 1);

    pthread_create(&t1, NULL, sem_worker, NULL);
    pthread_create(&t2, NULL, sem_worker, NULL);
    pthread_create(&t3, NULL, sem_worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&mutex);
}

#endif
