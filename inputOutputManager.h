// inputOutputManager.h

#ifndef INPUT_OUTPUT_MANAGER_H
#define INPUT_OUTPUT_MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "memoryManager.h"       // Include your memoryManager header
#include "mapTask.h"             // Include your mapTask header
#include "singleLevelTask.h"     // Include your singleLevelTask header
#include "twoLevelTask.h"        // Include your twoLevelTask header

using namespace std;

class inputOutputManager {
public:
    // Function to determine task size from string representation (e.g., "10K", "2M")
    inline long long int taskSize(string s);

    // Allocate memory based on trace file for mapTask objects
    inline void traceFileMemoryAllocationForMapTask(string fileName, vector<mapTask> &tasks, memoryManager &memoryManager);

    // Allocate memory based on trace file for singleLevelTask objects
    inline void traceFileMemoryAllocationForSingleLevelTask(string fileName, vector<singleLevelTask> &tasks, memoryManager &memoryManager);

    // Allocate memory based on trace file for twoLevelTask objects
    inline void traceFileMemoryAllocationForTwoLevelTask(string fileName, vector<twoLevelTask> &tasks, memoryManager &memoryManager);
};

#endif // INPUT_OUTPUT_MANAGER_H
