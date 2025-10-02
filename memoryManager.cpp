#include"memoryManager.h"
#include"config.h"
memoryManager :: memoryManager() : totalPhysicalPage(physicalMemorySize/PAGE_SIZE,true){};

memoryManager mManager;
long long int memoryManager :: initializePhysicalAddress() //Allocate physical pages to single logical address
{
	long long int totalPageNumber = totalPhysicalPage.size();
	long unsigned int i;
		for(i=0;i<totalPageNumber;i++)
		{
			if(totalPhysicalPage[i])
			{
				totalPhysicalPage[i] = false;
				return (i * PAGE_SIZE);
			}
		}
		return -1;
}

void memoryManager :: setFreePage(long long int address)
{
	long long int pageIndex;
	pageIndex = address/PAGE_SIZE;
	totalPhysicalPage[pageIndex] = true;
}

long long int memoryManager :: totalFreePages()
{
	  {
	long long int pageCount=0,i;
	for(i=0;i<totalPhysicalPage.size();i++)                              
	{
		if (totalPhysicalPage[i])
		{
			pageCount++;
		}
	}
	return pageCount;
   }
}
