#include<iostream>
#include<string> //Header file is defined for string
#include<map> //This Header File is for CPP MAP
#include<vector> //This Header File is for CPP Vector
#include<fstream> // This Header File is for file function
#include<sstream>
#include<math.h>
#include<chrono> //This Header File is for execution time calculation
#include"config.h" // All the important related data is defined here
#include"memoryManager.h"
#include"mapTask.h"
#include"singleLevelTask.h"
#include"twoLevelTask.h"
#include"performanceModule.cpp"
#include"inputOutputManager.cpp"
using namespace std;
static memoryManager mManager;
int main()
{
	// TestModule testModule;
	// long long int tracefile_4KB_4GB_4GBValue;
	// cout<<"Give the trace size multiple of 5"<<endl;
    // cout<<"Because for each Task it will generate 5 section."<<endl;
	// cin>>tracefile_4KB_4GB_4GBValue;
    // testModule.generateTrace(tracefile_4KB_4GB_4GBValue/5);
	cout<<"Press 1 For map implementation: "<<endl;
	cout<<"Press 2 For Single Level Page implementation: "<<endl;
	cout<<"Press 3 For Two Level Page implementation: "<<endl;
	int test;
	cin>>test;
	inputOutputManager IOManager;
	performanceModule perfModule(mManager);
	if(test == 1)
	{
	cout<<"FOR mapTask Implementation of page Table"<<endl;
	auto start = chrono::high_resolution_clock::now();
	vector<mapTask> tasks;
	
	//-------------------------------------------------------------------------
	IOManager.traceFileMemoryAllocationForMapTask("tracefile_4KB_4GB_4GB.txt",tasks,mManager);

	long long int pMemory = perfModule.getAllocatedPhysicalMemoryForMapTask(tasks),i=0;
	cout<<endl<<"Total physical Memory: "<<pMemory/1024<<"KB"<<endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Execution time: " << duration.count() << " microseconds" <<endl;
	long long int totalPageHit = 0,totalPageMiss = 0;
	for(auto &soloTask : tasks)
		{
		//for map page table
		cout<<"--------------------------------------"<<endl;
		cout<<"Task : no "<<i++<<endl;
		cout<<"page table size: "<<soloTask.pageTableSize()<<" B"<<endl;
		cout<<"physical memory allocation : "<<soloTask.physicalMemoryAllocationSize()/1024<<" KB "<<endl;
		cout<<": Page Hit: "<<soloTask.pageHit()<<" pageMiss: "<<soloTask.pageMiss()<<endl;
		totalPageHit += soloTask.pageHit();
		totalPageMiss += soloTask.pageMiss();
		cout<<"--------------------------------------"<<endl;
		}
		cout<<"Available Physical Memory: "<<perfModule.getAvailableFreeSpace()<<" B"<<endl;
		cout<<"Total Page Hit : "<<totalPageHit<<endl;
		cout<<"Total Page Miss : "<<totalPageMiss<<endl;
		cout<<"--------------------------------------"<<endl;
	}
	else if( test == 2)
	{
	cout<<"FOR singleLevelTask Implementation of page Table"<<endl;
	
	auto start = chrono::high_resolution_clock::now();
	vector<singleLevelTask>singleLevelTasks;

	IOManager.traceFileMemoryAllocationForSingleLevelTask("tracefile_4KB_4GB_4GB.txt",singleLevelTasks,mManager);
	long long int pMemory = perfModule.getAllocatedPhysicalMemoryForSingleLevelTask(singleLevelTasks),i=0;
	cout<<endl<<"Total physical Memory: "<<pMemory/1024<<"KB"<<endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Execution time: " << duration.count() << " microseconds" <<endl;
	long long int totalPageHit = 0,totalPageMiss = 0;
	for(auto &soloTask : singleLevelTasks)
		{
		//for single level page table
		cout<<"--------------------------------------"<<endl;
		cout<<"Task : no "<<i++<<endl;
		cout<<"page table size: "<<soloTask.pageTableSize()<<" B"<<endl;
		cout<<"physical memory allocation : "<<soloTask.physicalMemoryAllocationSize()/1024<<" KB "<<endl;
		cout<<": Page Hit: "<<soloTask.pageHit()<<" pageMiss: "<<soloTask.pageMiss()<<endl;
		totalPageHit += soloTask.pageHit();
		totalPageMiss += soloTask.pageMiss();
		cout<<"--------------------------------------"<<endl;
		}
		cout<<"Available Physical Memory: "<<perfModule.getAvailableFreeSpace()<<" B"<<endl;
		cout<<"Total Page Hit : "<<totalPageHit<<endl;
		cout<<"Total Page Miss : "<<totalPageMiss<<endl;
		cout<<"--------------------------------------"<<endl;
	}
	else if(test == 3)
	{
	
	cout<<"FOR Two Level Implementation of page Table"<<endl;
	auto start = chrono::high_resolution_clock::now();
	vector<twoLevelTask>twoLevelTasks;
	IOManager.traceFileMemoryAllocationForTwoLevelTask("tracefile_4KB_4GB_4GB.txt",twoLevelTasks,mManager);
	cout<<"IO manager reached"<<endl;
	long long int pMemory = perfModule.getAllocatedPhysicalMemoryForTwoLevelTask(twoLevelTasks),i=0;
	cout<<"performance module reached"<<endl;
	cout<<endl<<"Total physical Memory: "<<pMemory/1024<<"KB"<<endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Execution time: " << duration.count() << " microseconds" <<endl;
	long long int totalPageHit = 0,totalPageMiss = 0;
	for(auto &soloTask : twoLevelTasks)
		{
		//for two level page table
		cout<<"--------------------------------------"<<endl;
		cout<<"Task : no "<<i++<<endl;
		cout<<"page table size: "<<soloTask.pageTableSize()<<" B"<<endl;
		cout<<"physical memory allocation : "<<soloTask.physicalMemoryAllocationSize()/1024<<" KB "<<endl;
		cout<<": Page Hit: "<<soloTask.pageHit()<<" pageMiss: "<<soloTask.pageMiss()<<endl;
		totalPageHit += soloTask.pageHit();
		totalPageMiss += soloTask.pageMiss();
		cout<<"--------------------------------------"<<endl;
		}
		cout<<"Available Physical Memory: "<<perfModule.getAvailableFreeSpace()<<" B"<<endl;
		cout<<"--------------------------------------"<<endl;
		cout<<"Total Page Hit : "<<totalPageHit<<endl;
		cout<<"Total Page Miss : "<<totalPageMiss<<endl;
		cout<<"--------------------------------------"<<endl;
	}
	else{
		cout<<"Please Enter the Correct Values Given.";
	}
}