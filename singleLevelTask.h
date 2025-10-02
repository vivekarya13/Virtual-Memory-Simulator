#ifndef SINGLELEVELTASK_H
#define SINGLELEVELTASK_H

#include <vector>
#include"config.h"

class singleLevelTask {
private:
    std::vector<long long int> pageTable;
    long long int hit = 0, miss = 0;
public:
    singleLevelTask(long long int size = logicalMemorySize/PAGE_SIZE);
    void memoryRequest(long long int logicalAddress, long long int size);
    long long int pageHit();
    long long int pageMiss();
    long long int physicalAddress(long long int logicalAddress);
    long long int pageTableSize();
    long long int physicalMemoryAllocationSize();
};

#endif // SINGLELEVELTASK_H
