#include "mapTask.h"
#include "memoryManager.h"
#include "config.h"
#include <iostream>

using namespace std;
extern memoryManager mManager;

void mapTask::memoryRequest(long long int logicalAddress, long long int size) {
  long long int totalPageNeeded,i,initialLogicalPage;
		totalPageNeeded = (size + PAGE_SIZE -1) / PAGE_SIZE; //Total Physical Page needed
		initialLogicalPage = logicalAddress / PAGE_SIZE;
		
		for(i=0;i<totalPageNeeded;i++) //here we are looping with every needed page
		{
			initialLogicalPage +=i;
			if(pageTable.find(initialLogicalPage) == pageTable.end()) //Checking if page is there in map table or not
			{
				long long int physicalMemoryAllocation = mManager.initializePhysicalAddress(); // Memory Manager Returns the physical address
				if(physicalMemoryAllocation == -1)
				{
					cout<<"No physical Memory is not available for allocation for the task "<<endl;
					return;
				}
				pageTable[initialLogicalPage] = physicalMemoryAllocation; //Assigning value to  Map Table
				miss++; //Counting the page miss 
				initialLogicalPage-=i;
			}
			else
			{
				hit++;//counting the page hit
				initialLogicalPage-=i;
			}
		}
}

long long int mapTask::pageHit() {
    return hit;
}

long long int mapTask::pageMiss() {
    return miss;
}

long long int mapTask::physicalAddress(long long int logicalAddress) {
    long long int logicalPageNumber = logicalAddress/PAGE_SIZE,physicalPageNumber;
		if(pageTable.find(logicalPageNumber) == pageTable.end())
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
long long int mapTask::pageTableSize() {
    return pageTable.size() * PTESize;
}
long long int mapTask::physicalMemoryAllocationSize() {
    return pageTable.size() * PAGE_SIZE;
}
