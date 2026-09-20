#include <iostream>
using namespace std;

void FCFS() { // First Come First Serve
    int n; // Number of processes
    cout << "\n--- First Come First Serve (FCFS) ---" << endl;
    cout << "Enter number of processes: ";
    cin >> n;

    // Arrays for Burst Time (BT), Waiting Time (WT), and Turnaround Time (TAT)
    int bt[n], wt[n], tat[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter Burst time for P" << i + 1 << ": ";
        cin >> bt[i];
    }

    // Waiting time for the first process is always 0
    wt[0] = 0;

    // Calculate Waiting Time for subsequent processes
    // WT of current process = WT of previous process + BT of previous process
    for(int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate Turnaround Time (TAT = WT + BT)
    for(int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Display the results
    cout << "\nProcess\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

void SJF() { // Shortest Job First (Non-Preemptive)
    int n;
    cout << "\n--- Shortest Job First (SJF) ---" << endl;
    cout << "Enter number of processes: ";
    cin >> n;

    // Added p[n] to track the original process ID after sorting
    int bt[n], wt[n], tat[n], p[n];

    for(int i = 0; i < n; i++) {
        p[i] = i + 1; // Assign Process ID (1, 2, 3...)
        cout << "Enter Burst time for P" << p[i] << ": ";
        cin >> bt[i];
    }

    // Sorting processes by Burst Time in ascending order using Bubble Sort
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(bt[i] > bt[j]) { // If current BT is greater than next BT, swap them
                // Swap Burst Time
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process ID to keep it matched with its Burst Time
                int tempP = p[i];
                p[i] = p[j];
                p[j] = tempP;
            }
        }
    }

    wt[0] = 0;
    for(int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    for(int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << p[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

void Priority() { // Priority Scheduling (Non-Preemptive)
    int n;
    cout << "\n--- Priority Scheduling ---" << endl;
    cout << "Enter number of processes: ";
    cin >> n;

    // pr[n] stores the priority of each process
    int bt[n], wt[n], tat[n], pr[n], p[n];

    for(int i = 0; i < n; i++) {
        p[i] = i + 1;
        cout << "Enter Burst time for P" << p[i] << ": ";
        cin >> bt[i];
        cout << "Enter priority for P" << p[i] << " (Lower number = Higher Priority): ";
        cin >> pr[i];
    }

    // Sort processes based on Priority in ascending order (Lower number = Higher Priority)
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(pr[i] > pr[j]) {
                // Swap Priority
                int tempPr = pr[i]; pr[i] = pr[j]; pr[j] = tempPr;
                // Swap Burst Time
                int tempBt = bt[i]; bt[i] = bt[j]; bt[j] = tempBt;
                // Swap Process ID
                int tempP = p[i]; p[i] = p[j]; p[j] = tempP;
            }
        }
    }

    wt[0] = 0;
    for(int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    for(int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    cout << "\nProcess\tBT\tPR\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << p[i] << "\t" << bt[i] << "\t" << pr[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

void RR() { // Round Robin
    int n;
    cout << "\n--- Round Robin (RR) ---" << endl;
    cout << "Enter number of processes: ";
    cin >> n;

    // rem_bt[] tracks the remaining burst time for each process
    int bt[n], wt[n], tat[n], rem_bt[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter Burst time for P" << i + 1 << ": ";
        cin >> bt[i];
        rem_bt[i] = bt[i]; // Initially, remaining time is equal to burst time
    }

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    int current_time = 0; // Acts as the CPU clock
    bool all_done = false;

    // Keep traversing the processes until all of them are completely executed
    while (!all_done) {
        all_done = true;

        for (int i = 0; i < n; i++) {
            // If the process still has time remaining to execute
            if (rem_bt[i] > 0) {
                all_done = false; // Flag that there is still pending work

                if (rem_bt[i] > quantum) {
                    // Process executes for the full time quantum
                    current_time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    // Process requires less than or equal to the quantum to finish
                    current_time += rem_bt[i];
                    // WT = Time the process finished - Its original Burst Time
                    wt[i] = current_time - bt[i];
                    rem_bt[i] = 0; // Process is now finished
                }
            }
        }
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }
}

int main() {
    // Calling each scheduling algorithm sequentially
    FCFS();
    SJF();
    Priority();
    RR();

    return 0;
}