#include "twoLevelTask.h"
#include "memoryManager.h"
#include "config.h"
#include <iostream>
using namespace std;
extern memoryManager mManager;

void twoLevelTask::mapToTable(long long int logicalIndex, long long int physicalAddress) {
    long long int topIndex = (logicalIndex >> secondLevelEntrySizeInBits); //& for getting only lower 10 bit values
		// cout<<"reaching maptable"<<endl;
		// cout<<"top index "<<topIndex<<endl;
		long long int logicalAnd = pow(2,secondLevelEntrySizeInBits) - 1;
		long long int secondIndex = logicalIndex & logicalAnd;
		// cout<<"second index "<<secondIndex<<endl;
		if(firstLevel[topIndex] == nullptr)
		{
			// twoLevel two;
			firstLevel[topIndex] = new twoLevel(); //initialize the values to -1 if the page table in first index is empty
		}

		firstLevel[topIndex]->setPhysicalAddress(secondIndex,physicalAddress);
}

long long int twoLevelTask::physicalAddress(long long int logicalAddress) {
        long long int physicalPageNumber;
		int topAnd = secondLevelEntrySizeInBits + pageOffsetBit;
		long long int topIndex = (logicalAddress >> topAnd );
		int secondAnd = pow(2,secondLevelEntrySizeInBits)-1;
		long long int secondIndex = (logicalAddress >> pageOffsetBit ) & secondAnd;
		long long int pageOffset = logicalAddress & (PAGE_SIZE-1);//Gives the page offset
 		if(firstLevel[topIndex] == nullptr)
		{
			return -1;
		}
		physicalPageNumber = firstLevel[topIndex]-> getPhysicalPageNumber(secondIndex);
		if(physicalPageNumber == -1)
		{
			return -1;
			
		}
		physicalPageNumber = physicalPageNumber + pageOffset;
		return physicalPageNumber;
}

long long int twoLevelTask::findPage(long long int logicalIndex) {
   long long int physicalPageNumber;
		long long int topIndex = (logicalIndex >> secondLevelEntrySizeInBits); //& for getting only lower 10 bit values
		// cout<<"top index in find page "<<topIndex<<endl;
		long long int logicalAnd = pow(2,secondLevelEntrySizeInBits) - 1;
		long long int secondIndex = logicalIndex & logicalAnd;
		// cout<<"second index in find page "<<secondIndex<<endl;
		if(firstLevel[topIndex] == nullptr)
		{
			return -1;
		}
		

		physicalPageNumber = firstLevel[topIndex]->getPhysicalPageNumber(secondIndex);
		if(physicalPageNumber == -1)
		{
			return -1;
			
		}
		return physicalPageNumber;
}

void twoLevelTask::memoryRequest(long long int logicalAddress, long long int size) {
    long long int totalPageNeeded,i,initialLogicalPage;
		totalPageNeeded = (size + PAGE_SIZE -1) / PAGE_SIZE;
		// cout<<"Total Page needed------------------------------------"<<endl;
		initialLogicalPage = logicalAddress / PAGE_SIZE;
		for(i=0;i<totalPageNeeded;i++)
		{
			initialLogicalPage +=i;
			// cout<<"Initial Logical Page Now: "<<initialLogicalPage<<endl;
			if(findPage(initialLogicalPage) == -1)
			{
				long long int physicalMemoryAllocation = mManager.initializePhysicalAddress();
				if(physicalMemoryAllocation == -1)
				{
					cout<<"No physical Memory is not available for allocation for the task "<<endl;
					return;
				}
				// cout<<"Physical Memory Allocation  "<<physicalMemoryAllocation<<endl;
				mapToTable(initialLogicalPage,physicalMemoryAllocation);
				miss++; //calculate the page miss
				initialLogicalPage-=i;
				// cout<<"Initial Logical Page Later: "<<initialLogicalPage<<endl;
			}
			else
			{

				hit++; //calculate the pagehit
				initialLogicalPage-=i;
				// cout<<"Initial Logical Page Later: "<<initialLogicalPage<<endl;
			}
		}

}

long long int twoLevelTask::pageHit() {
    return hit;
}

long long int twoLevelTask::pageMiss() {
    return miss;
}

long long int twoLevelTask::pageTableSize() {
  long long int index,j;
		long int count=0;
		for(index=0;index<firstLevelPageSize;index++){
			if(firstLevel[index]==nullptr)
			{
				continue;
			}
			for(j=0;j<secondLevelPageSize;j++)
			{
				if((firstLevel[index]->getPhysicalPageNumber(j)) != -1) //confirms if there any second level address saved
				{
				count++;
				break;
				}
			}

		}
		// cout<<" -------- count ------- "<<count<<endl;
		if(count != 0)
		{
			return ((firstLevelPageSize * PTESize) + (count * PTESize * secondLevelPageSize));
		}else{
			return 0; //if count 0 means no first level or second level is allocated to the task
		}
}

long long int twoLevelTask::physicalMemoryAllocationSize() {
    long long int index,j;
		int count=0;
		for(index=0;index<firstLevelPageSize;index++){
			if(firstLevel[index] == nullptr)
				{
					continue;
				}
			for(j=0;j<secondLevelPageSize;j++)
			{
				
				if((firstLevel[index]->getPhysicalPageNumber(j)) != -1)
				{
				count++;
				}
			}
		}
		
		// cout<<"Count "<<count<<endl;
		return count * PAGE_SIZE;

	}

