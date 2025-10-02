#ifndef TWO_LEVEL_H
#define TWO_LEVEL_H

#define firstLevelPageSize pow(2,firstLevelEntrySizeInBits)
#define secondLevelPageSize pow(2,secondLevelEntrySizeInBits)
#include <iostream>
#include <vector>
#include"config.h"
#include <cmath>



using namespace std;

class twoLevel {
private:
    std::vector<long long int> secondLevelPage;

public:
    twoLevel() {
        long long int arraySize = pow(2, secondLevelEntrySizeInBits);
        secondLevelPage.resize(arraySize, -1);
    }

    void setPhysicalAddress(long long int index, long long int physicalAddress) {
        if (index < secondLevelPage.size()) {
            secondLevelPage[index] = physicalAddress;
        }
    }

    long long int getPhysicalPageNumber(long long int index) const {
        if (index < secondLevelPage.size()) {
            return secondLevelPage[index];
        }
        return -1; // Return -1 if index is out of bounds
    }
};

class twoLevelTask {
private:
    long long int hit = 0, miss = 0;
    std::vector<twoLevel*> firstLevel;

public:
    twoLevelTask() {
        firstLevel.resize(firstLevelPageSize, nullptr);
    }

    void mapToTable(long long int logicalIndex, long long int physicalAddress);
    long long int physicalAddress(long long int logicalAddress);
    long long int findPage(long long int logicalIndex);
    void memoryRequest(long long int logicalAddress, long long int size);
    long long int pageHit();
    long long int pageMiss();
    long long int pageTableSize();
    long long int physicalMemoryAllocationSize();
};

#endif // TWO_LEVEL_H
