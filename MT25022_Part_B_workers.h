#ifndef WORKERS_H
#define WORKERS_H

// MT25022_Part_B_workers.h
// Header file containing the three worker functions: cpu, mem, io.
// Each function runs a loop for 2000 iterations (last digit 2 * 1000).
// AI-generated with assistance from GitHub Copilot.
// Roll number: MT25022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

// Loop count: last digit of roll no * 1000 = 2 * 1000 = 2000
#define LOOP_COUNT 2000

// CPU-intensive function: performs complex mathematical calculations
void cpu() {
    double result = 0.0;
    for(int i = 0; i < LOOP_COUNT; i++) {
        // Perform some floating-point computations
        result += sin(i) * cos(i) + tan(i / (i + 1.0));
    }
    printf("CPU function completed, result: %f\n", result);
}

// Memory-intensive function: allocates, fills, and frees large memory blocks
void mem() {
    const size_t block_size = 1024 * 1024; // 1 MB
    for(int i = 0; i < LOOP_COUNT; i++) {
        char *buffer = (char *)malloc(block_size);
        if(buffer == NULL) {
            perror("malloc failed");
            return;
        }
        memset(buffer, 'A', block_size); // Fill with data
        free(buffer);
    }
    printf("Memory function completed\n");
}

// I/O-intensive function: performs file write operations with sync
void io() {
    const char *filename = "temp_io_file.txt";
    const char *data = "This is a test data for I/O operations.\n";
    size_t data_len = strlen(data);
    for(int i = 0; i < LOOP_COUNT; i++) {
        int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if(fd == -1) {
            perror("open failed");
            return;
        }
        if(write(fd, data, data_len) == -1) {
            perror("write failed");
            close(fd);
            return;
        }
        if(fsync(fd) == -1) {
            perror("fsync failed");
        }
        close(fd);
    }
    // Clean up the file
    unlink(filename);
    printf("I/O function completed\n");
}

#endif