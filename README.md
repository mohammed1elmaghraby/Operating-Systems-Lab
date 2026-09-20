# Operating Systems Laboratory

A collection of C++ implementations demonstrating core operating system concepts. This repository serves as a practical exploration of system-level programming, specifically focusing on process scheduling and memory management techniques.

## Repository Contents

This project is currently divided into two main modules:

### 1. CPU Scheduling Algorithms (`CPU_A.cpp`)
Simulates how an operating system scheduler assigns CPU time to different processes. 
* **First-Come, First-Served (FCFS):** Processes are executed strictly in the order they arrive.
* **Shortest Job First (SJF):** Non-preemptive scheduling that selects the waiting process with the smallest execution time.
* **Priority Scheduling:** Processes are executed based on a predefined priority level.
* **Round Robin (RR):** Each process is assigned a fixed time slot (quantum) in a cyclic order, ensuring fairness and preventing starvation.

### 2. Memory Allocation Strategies (`MAA.cpp`)
Demonstrates how an operating system allocates continuous memory blocks to incoming processes.
* **First Fit:** Allocates the first memory block that is large enough.
* **Best Fit:** Searches all blocks and allocates the smallest block that is large enough to minimize wasted leftover space.
* **Worst Fit:** Allocates the largest available block to leave a substantial remaining chunk for future processes.
* **Next Fit:** Operates like First Fit, but begins its search from the last allocated block rather than the beginning of the memory array.

## Compilation & Execution

These programs are written in standard C++ and can be compiled using `g++` via the terminal.

### Compiling and Running Memory Management
```bash
# Compile the code
g++ MAA.cpp -o MAA

# Execute the program
./MAA
