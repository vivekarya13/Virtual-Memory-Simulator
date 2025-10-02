#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include<vector>

class memoryManager{
private:
	std::vector<bool> totalPhysicalPage;
public:
	memoryManager();
	long long int initializePhysicalAddress();
	void setFreePage(long long int address);
	long long int totalFreePages();
};

#endif
