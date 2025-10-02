#ifndef PERFORMANCE_MODULE_H
#define PERFORMANCE_MODULE_H

#include <vector>
#include "memoryManager.h"
#include "mapTask.h"
#include "singleLevelTask.h"
#include "twoLevelTask.h"

class performanceModule {
private:
    memoryManager& memoryM;

public:
    inline performanceModule(memoryManager& mm);

    inline long long int getTotalMemoryForMapTaskPageTables(std::vector<mapTask> &tasks);
    inline long long int getTotalMemoryForSingleLevelTaskPageTables(std::vector<singleLevelTask> &tasks);
    inline long long int getTotalMemoryForTwoLevelTaskPageTables(std::vector<twoLevelTask> &tasks);
    
    inline long long int getAllocatedPhysicalMemoryForMapTask(std::vector<mapTask> &tasks);
    inline long long int getAllocatedPhysicalMemoryForSingleLevelTask(std::vector<singleLevelTask> &tasks);
    inline long long int getAllocatedPhysicalMemoryForTwoLevelTask(std::vector<twoLevelTask> &tasks);
    
    inline long long int getAvailableFreeSpace(); // Available physical page size
};

#endif // PERFORMANCE_MODULE_H
