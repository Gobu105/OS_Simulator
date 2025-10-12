#include<stdio.h>
#include<unistd.h>
#ifndef KERNEL_H
#define KERNEL_H

void kernel() {
    printf("🧩 Kernel: Initializing system components...\n");
    sleep(1);
    printf("⚙️  Process Manager Initialized\n");
    printf("💾 Memory Manager Initialized\n");
    printf("🖨️  Device Drivers Loaded\n");
    sleep(1);
    printf("🌐 Starting user-space process: init\n\n");
}

#endif
