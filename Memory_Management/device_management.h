#ifndef DEVICE_MANAGEMENT_H
#define DEVICE_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#define DEVICES 5

int devices[DEVICES]; // -1 = free, else PID using it

void init_devices() {
    for (int i = 0; i < DEVICES; i++) devices[i] = -1;
    printf("\033[1;35m[Devices] Initialized %d devices.\n\033[0m", DEVICES);
}

void request_device(int device_id, int pid) {
    if (device_id < 0 || device_id >= DEVICES) {
        red("[Devices] Invalid device ID.\n");
        return;
    }
    if (devices[device_id] == -1) {
        devices[device_id] = pid;
        printf("[Devices] Process %d acquired device %d.\n", pid, device_id);
    } else {
        printf("[Devices] Device %d is busy.\n", device_id);
    }
}

void release_device(int device_id) {
    if (device_id < 0 || device_id >= DEVICES) {
        red("[Devices] Invalid device ID.\n");
        return;
    }
    if (devices[device_id] != -1) {
        printf("[Devices] Device %d released from process %d.\n", device_id, devices[device_id]);
        devices[device_id] = -1;
    } else {
        printf("[Devices] Device %d is already free.\n", device_id);
    }
}

void display_devices() {
    cyan("[Devices] Status: ");
    for (int i = 0; i < DEVICES; i++)
        printf("[%d:%s] ", i, devices[i] == -1 ? "Free" : "Busy");
    printf("\n");
}

#endif
