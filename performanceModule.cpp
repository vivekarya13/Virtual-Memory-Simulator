#include "performanceModule.h"
#include<vector>
performanceModule::performanceModule(memoryManager& mm) : memoryM(mm) {}

long long int performanceModule::getTotalMemoryForMapTaskPageTables(vector<mapTask> &tasks) {
    long long int totalPageTableSize = 0;
    for(auto &task : tasks) {
        totalPageTableSize += task.pageTableSize();
    }
    return totalPageTableSize;
}

long long int performanceModule::getTotalMemoryForSingleLevelTaskPageTables(vector<singleLevelTask> &tasks) {
    long long int totalPageTableSize = 0;
    for(auto &task : tasks) {
        totalPageTableSize += task.pageTableSize();
    }
    return totalPageTableSize;
}

long long int performanceModule::getTotalMemoryForTwoLevelTaskPageTables(vector<twoLevelTask> &tasks) {
    long long int totalPageTableSize = 0;
    for(auto &task : tasks) {
        totalPageTableSize += task.pageTableSize();
    }
    return totalPageTableSize;
}

long long int performanceModule::getAllocatedPhysicalMemoryForMapTask(vector<mapTask> &tasks) {
    long long int totalPhysicalMemoryAllocated = 0;
    for(auto &task : tasks) {
        totalPhysicalMemoryAllocated += task.physicalMemoryAllocationSize();
    }
    return totalPhysicalMemoryAllocated;
}

long long int performanceModule::getAllocatedPhysicalMemoryForSingleLevelTask(vector<singleLevelTask> &tasks) {
    long long int totalPhysicalMemoryAllocated = 0;
    for(auto &task : tasks) {
        totalPhysicalMemoryAllocated += task.physicalMemoryAllocationSize();
    }
    return totalPhysicalMemoryAllocated;
}

long long int performanceModule::getAllocatedPhysicalMemoryForTwoLevelTask(vector<twoLevelTask> &tasks) {
    long long int totalPhysicalMemoryAllocated = 0;
    for(auto &task : tasks) {
        totalPhysicalMemoryAllocated += task.physicalMemoryAllocationSize();
    }
    return totalPhysicalMemoryAllocated;
}

long long int performanceModule::getAvailableFreeSpace() {
    return memoryM.totalFreePages() * PAGE_SIZE;
}
