// MT25022_Part_A_Program_A.c
// This program creates N child processes using fork() and executes a specified worker function in each.
// N defaults to 2, or specified as second argument.
// AI-generated with assistance from GitHub Copilot.
// Roll number: MT25022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "MT25022_Part_B_workers.h"

int main(int argc, char *argv[]) {
    // Check command line arguments
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <cpu|mem|io> [num_processes]\n", argv[0]);
        return 1;
    }
    int num_processes = 2; // Default
    if(argc >= 3) {
        num_processes = atoi(argv[2]);
    }
    // Create N child processes using fork()
    for(int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("fork failed");
            return 1;
        } else if(pid == 0) {
            // Child process: execute the worker function
            printf("Child process %d created, PID: %d\n", i+1, getpid());
            // Call the specified worker function based on argument
            if(strcmp(argv[1], "cpu") == 0) {
                cpu();
            } else if(strcmp(argv[1], "mem") == 0) {
                mem();
            } else if(strcmp(argv[1], "io") == 0) {
                io();
            } else {
                fprintf(stderr, "Invalid function: %s\n", argv[1]);
            }
            exit(0);
        }
    }
    // Parent process: wait for all children to finish
    for(int i = 0; i < num_processes; i++) {
        wait(NULL);
    }
    printf("Parent process done\n");
    return 0;
}