# Operating Systems Laboratory

A comprehensive collection of C++ implementations and Bash scripts demonstrating core operating system concepts. This repository serves as a practical exploration of system-level programming, covering process scheduling, memory management, and real-time system monitoring.

## Repository Contents

This project is divided into three main modules:

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

### 3. System Health Monitor (`System_Monitor.sh`)
A Bash shell script that provides a live, continuously updating dashboard of system resources directly in the terminal.
* **CPU Usage:** Monitors active processing load.
* **Memory (RAM) Usage:** Calculates the exact percentage of used memory.
* **Disk Space:** Tracks root directory storage capacity.
* **Color-Coded Alerts:** Automatically flags resource usage as OK (Green), WARNING (Yellow), or CRITICAL (Red) based on dynamic thresholds.

## Compilation & Execution

### Compiling and Running C++ Modules
These programs are written in standard C++ and can be compiled using `g++`.

**CPU Scheduling:**
```bash
g++ CPU_A.cpp -o CPU_A
./CPU_A
```

**Memory Management:**
```bash
g++ MAA.cpp -o MAA
./MAA
```

**Running the Bash Monitor**
The monitoring script requires execution permissions before running for the first time.
```bash
# Grant execution permissions (only needed once)
chmod +x System_Monitor.sh

# Run the live monitor
./System_Monitor.sh
```
(Press Ctrl + C to stop the monitor and return to the prompt.)

Author: Mohammed Ismail Elmaghraby
