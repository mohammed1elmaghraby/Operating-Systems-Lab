#include <iostream>
#include <vector>
using namespace std;

// Function prototypes for the memory allocation algorithms
void FirstFit(int blocksize[], int m, int processsize[], int n);
void BestFit(int blocksize[], int m, int processsize[], int n);
void WorstFit(int blocksize[], int m, int processsize[], int n);
void NextFit(int blocksize[], int m, int processsize[], int n);

int main() {
    // Initial memory block sizes and incoming process sizes
    int blockSize[] = {50, 12, 30};
    int processSize[] = {12, 25, 30};

    // Calculate the number of blocks (m) and processes (n)
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    cout << "=== First Fit ===";
    FirstFit(blockSize, m, processSize, n);

    cout << "\n=== Best Fit ===";
    BestFit(blockSize, m, processSize, n);

    cout << "\n=== Worst Fit ===";
    WorstFit(blockSize, m, processSize, n);

    cout << "\n=== Next Fit ===";
    NextFit(blockSize, m, processSize, n);

    return 0;
}

void FirstFit(int blocksize[], int m, int processsize[], int n) {
    // Use std::vector to safely handle dynamic array sizes and initialize all allocations to -1 (Not Allocated)
    vector<int> allocation(n, -1);

    // Create a local copy of block sizes so we don't destroy the original data for subsequent algorithms
    vector<int> current_blocksize(blocksize, blocksize + m);

    // Iterate through each process to find it a memory block
    for (int i = 0; i < n; i++) {
        // Search sequentially through blocks starting from the beginning
        for (int j = 0; j < m; j++) {
            if (current_blocksize[j] >= processsize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                // Mark the block as used (or subtract process size if dealing with partitions)
                current_blocksize[j] = -1;
                // First Fit: Break immediately after finding the first suitable block
                break;
            }
        }
    }

    // Display the allocation results
    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processsize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
    cout <<"====================="<< endl;
}

void BestFit(int blocksize[], int m, int processsize[], int n) {
    vector<int> allocation(n, -1);
    vector<int> current_blocksize(blocksize, blocksize + m);

    for (int i = 0; i < n; i++) {
        int idx = -1; // Stores the index of the best block found so far

        // Check ALL blocks to find the tightest fit
        for (int j = 0; j < m; j++) {
            if (current_blocksize[j] >= processsize[i]) {
                // If this is the first block that fits, OR it is smaller than the previously found best block
                if (idx == -1 || current_blocksize[idx] > current_blocksize[j]) {
                    idx = j;
                }
            }
        }

        // If a suitable block was found, allocate it
        if (idx != -1) {
            allocation[i] = idx;
            current_blocksize[idx] = -1;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processsize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
    cout <<"====================="<< endl;
}

void WorstFit(int blocksize[], int m, int processsize[], int n) {
    vector<int> allocation(n, -1);
    vector<int> current_blocksize(blocksize, blocksize + m);

    for (int i = 0; i < n; i++) {
        int wstid = -1; // Stores the index of the worst (largest) block found so far

        // Check ALL blocks to find the largest available space
        for (int j = 0; j < m; j++) {
            if (current_blocksize[j] >= processsize[i]) {
                // If this is the first block that fits, OR it is larger than the previously found worst block
                if (wstid == -1 || current_blocksize[wstid] < current_blocksize[j])
                    wstid = j;
            }
        }

        // If a suitable block was found, allocate it
        if (wstid != -1) {
            allocation[i] = wstid;
            current_blocksize[wstid] = -1;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processsize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
    cout <<"====================="<< endl;
}

void NextFit(int blocksize[], int m, int processsize[], int n) {
    vector<int> allocation(n, -1);
    vector<int> current_blocksize(blocksize, blocksize + m);

    int j = 0; // Maintains the last allocated block index across different processes

    for (int i = 0; i < n; i++) {
        int count = 0; // Counter to prevent an infinite loop if no suitable block is available

        // Continue searching from the last allocated point (j)
        while (count < m) {
            if (current_blocksize[j] >= processsize[i]) {
                // Allocate and mark the block as used
                allocation[i] = j;
                current_blocksize[j] = -1;
                break; // Stop searching once a block is found
            }
            // Move to the next block sequentially, wrapping around to 0 if the end is reached (circular array)
            j = (j + 1) % m;
            count++; // Increment the search attempt counter
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processsize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1; 
        else
            cout << "Not Allocated"; 
        cout << endl;
    }
    cout <<"====================="<< endl;
}