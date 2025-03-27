# OS-Assignment-1

This repository contains an implementation of a producer-consumer problem using shared memory and semaphores in C. The producer generates items and places them in a shared table, while the consumer retrieves and processes these items. Synchronization is achieved using semaphores to ensure mutual exclusion and proper coordination between the producer and consumer.

## Features
- Shared memory for inter-process communication.
- Semaphores for synchronization.
- Multi-threaded implementation using `pthread`.
- Example Makefile for building and running the project.

## Prerequisites
- GCC compiler.
- POSIX-compliant system (Linux or macOS).
- Basic understanding of C programming and operating systems concepts.

## Files
- `producer.c`: Contains the producer implementation.
- `consumer.c`: Contains the consumer implementation.
- `Makefile`: Automates the build and run process.

## Build Instructions
can be built with commands given in assignment but I made a Makefile as well to make my life easier. 

if you want to use the make file

This will compile the `producer` and `consumer` executables.

## Run Instructions
To run the producer and consumer simultaneously:
```bash
make run
```

To stop the processes:
```bash
make stop
or
make kill
```

## Example Output
When running the producer and consumer, you should see output similar to the following:
```
Produced item 1
Consumed item 1
Produced item 2
Consumed item 2
Produced item 3
Consumed item 3
...
```

## Clean Up
To clean up the compiled binaries and other generated files as well as the shared memory locations, run:
```bash
make clean
```
I chose to cleanup memory locations in a seperate c file assignment didnt say how you wanted to stop the processes so i just kill them  but that doesnt clean up the shared memroy, hence why make clean is necessary.

## Implementation Details
- **Shared Memory**: The producer and consumer share a memory region (`/shm_table`) to store items.
- **Semaphores**:
  - `emptySlots`: Tracks the number of empty slots in the shared table.
  - `fullSlots`: Tracks the number of filled slots in the shared table.
  - `mutex`: Ensures mutual exclusion when accessing the shared table.
- **Synchronization**: The producer waits for an empty slot before producing, and the consumer waits for a filled slot before consuming.
