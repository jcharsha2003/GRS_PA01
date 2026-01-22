# Makefile for MT25022_PA01
# Compiles the C programs and cleans binaries.
# Roll number: MT25022

CC = gcc
CFLAGS = -lm
PTHREAD_CFLAGS = -pthread

all: progA progB

progA: MT25022_Part_A_Program_A.c MT25022_Part_B_workers.h
	$(CC) -o progA MT25022_Part_A_Program_A.c $(CFLAGS)

progB: MT25022_Part_A_Program_B.c MT25022_Part_B_workers.h
	$(CC) $(PTHREAD_CFLAGS) -o progB MT25022_Part_A_Program_B.c $(CFLAGS)

clean:
	rm -f progA progB

.PHONY: all clean