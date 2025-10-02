#ifndef MAPTASK_H
#define MAPTASK_H

#include <map>

class mapTask {
private:
    std::map<long long int, long long int> pageTable;
    long long int hit = 0, miss = 0;
public:
    void memoryRequest(long long int logicalAddress, long long int size);
    long long int pageHit();
    long long int pageMiss();
    long long int physicalAddress(long long int logicalAddress);
    long long int pageTableSize();
    long long int physicalMemoryAllocationSize();
};

#endif // MAPTASK_H
