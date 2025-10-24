#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../utils.h"

void demo_system_calls() {
    print_header("System Call Simulation (fork, exec, wait)");
    pid_t pid = fork();
    if (pid == 0) {
        cyan("\n[Child] Process created successfully!\n");
        sleep(0.5);
        printf("[Child] PID: %d | PPID: %d\n", getpid(), getppid());
        yellow("[Child] Executing new program (simulated exec)\n");
        delay(500);
        printf("[Child] Exiting...\n");
    } else if (pid > 0) {
        green("\n[Parent] Waiting for child to finish...\n");
        wait(NULL);
        green("[Parent] Child finished. Continuing execution.\n");
    } else {
        red("\nFork failed!\n");
    }
}

#endif
