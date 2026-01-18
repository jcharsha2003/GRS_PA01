// MT25022_Part_A_Program_B.c
// This program creates N threads using pthreads and executes a specified worker function in each.
// N defaults to 2, or specified as second argument.
// AI-generated with assistance from GitHub Copilot.
// Roll number: MT25022

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "MT25022_Part_B_workers.h"

void *worker(void *arg) {
    char *func = (char *)arg;
    printf("Thread executing %s\n", func);
    // Call the specified worker function
    if(strcmp(func, "cpu") == 0) {
        cpu();
    } else if(strcmp(func, "mem") == 0) {
        mem();
    } else if(strcmp(func, "io") == 0) {
        io();
    } else {
        fprintf(stderr, "Invalid function: %s\n", func);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    // Check command line arguments
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <cpu|mem|io> [num_threads]\n", argv[0]);
        return 1;
    }
    int num_threads = 2; // Default
    if(argc >= 3) {
        num_threads = atoi(argv[2]);
    }
    pthread_t threads[8]; // Max 8
    // Create N threads using pthread_create
    for(int i = 0; i < num_threads; i++) {
        if(pthread_create(&threads[i], NULL, worker, argv[1]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }
    // Main thread: wait for all threads to finish
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done\n");
    return 0;
}