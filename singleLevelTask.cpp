#include "singleLevelTask.h"
#include "memoryManager.h"
#include "config.h"
#include <iostream>

using namespace std;
extern memoryManager mManager;

singleLevelTask::singleLevelTask(long long int size) : pageTable(size, -1) {}

void singleLevelTask::memoryRequest(long long int logicalAddress, long long int size) {
	long long int totalPageNeeded,i,initialLogicalPage;
		totalPageNeeded = size / PAGE_SIZE;//Total Physical Page needed
		initialLogicalPage = logicalAddress / PAGE_SIZE;
		for(i=0;i<totalPageNeeded;i++)
		{
			initialLogicalPage +=i;
			if(pageTable[initialLogicalPage] == -1)
			{
				long long int physicalMemoryAllocation = mManager.initializePhysicalAddress();
				if(physicalMemoryAllocation == -1)
				{
					cout<<"No physical Memory is not available for allocation for the task "<<endl;
					return;
				}

				pageTable[initialLogicalPage] = physicalMemoryAllocation; //physical memory is allocated to corresponding logical address
				miss++;//Counts the Page Miss
				initialLogicalPage-=i;
			}
			else
			{
				hit++; //counts the page Hit
				initialLogicalPage-=i;
			}
		}
}

long long int singleLevelTask::pageHit() {
    return hit;
}

long long int singleLevelTask::pageMiss() {
    return miss;
}

long long int singleLevelTask::physicalAddress(long long int logicalAddress) {
    long long int logicalPageNumber = logicalAddress/PAGE_SIZE,physicalPageNumber;
		if(pageTable[logicalPageNumber] == -1)
		{
			cout<<"page not present";
			return -1;
		}
		else
		{
			long int pageOffset = logicalAddress % PAGE_SIZE;
			physicalPageNumber = pageTable[logicalPageNumber] + pageOffset;
			return physicalPageNumber;
		}
}

long long int singleLevelTask::pageTableSize() {
    return pageTable.size() * PTESize;
}

long long int singleLevelTask::physicalMemoryAllocationSize() {
   long long int i,count=0;
		for(i=0;i<pageTable.size();i++)
		{
			if(pageTable[i] != -1)
			{
				count++;
			}
		}
		return (count*PAGE_SIZE);
}
