#ifndef CONFIG_H
#define CONFIG_H
#define physicalMemorySize ( 1ULL << 32 )
#define logicalMemorySize ( 1ULL << 32 )
#define PAGE_SIZE 4096 //4KB
//for 2 level
// #define secondLevelPageTable std::vector<long long int>
// #define TopLevelPageTable std::vector<secondLevelPageTable>
#define PTESize 4


#define TEXT_SECTION_START_ADDRESS 0x00400000//text section starting address
#define DATA_SECTION_START_ADDRESS 0x10000000 //data section starting address
#define HEAP_SECTION_START_ADDRESS 0x20000000 //heap section starting address
#define SHARED_LIB_SECTION_START_ADDRESS 0x60000000 //shared library starting address
#define STACK_SECTION_START_ADDRESS 0xFFF00000 //stack section starting address(increases downward)
#include <vector>
#include<math.h>

const int pageOffsetBit = log2(PAGE_SIZE);
const int firstLevelEntrySizeInBits = (log2(logicalMemorySize) - log2(PAGE_SIZE))/2;
const int secondLevelEntrySizeInBits = log2(logicalMemorySize) - (pageOffsetBit + firstLevelEntrySizeInBits);
// long long int firstLevelPageSize = pow(2,firstLevelEntrySizeInBits);
// long long int secondLevelPageSize = pow(2,secondLevelEntrySizeInBits);
#endif