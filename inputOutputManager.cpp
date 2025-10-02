// inputOutputManager.cpp

#include "inputOutputManager.h"
using namespace std;
// Function to convert size string (e.g., "10K", "2M") to bytes
long long int inputOutputManager::taskSize(string s) {
 string str,pseudoString;
     pseudoString = s;
     s.pop_back();
     str = s.back();
    long long int returnSize;
 if(str=="K" || str == "k")
    {
        string numValue = pseudoString.substr(0,pseudoString.size()-2);
        returnSize = stoll(numValue,nullptr,10);
        return returnSize*1024;
    }
    else if(str=="M" || str == "m")
    {
      string numValue = pseudoString.substr(0,pseudoString.size()-2);
        returnSize = stoll(numValue,nullptr,10);
        return returnSize*1024*1024;  
    }
    else
    {
       string numValue = pseudoString.substr(0,pseudoString.size()-1); 
       returnSize = stoll(numValue,nullptr,10);
        return returnSize;
    }
}

// Function to allocate memory for mapTask objects using a trace file
void inputOutputManager::traceFileMemoryAllocationForMapTask(string fileName, vector<mapTask> &tasks, memoryManager &memoryManager) {
   fstream file;
		string str,soloTask;
		file.open(fileName,ios::in);
		if(file.is_open())
		{
			while(getline(file, soloTask))
			{
				string task,address,size;
				stringstream ss(soloTask);
				vector<string>strValue;
				while(getline(ss,str,':'))
				{
					strValue.push_back(str);
				}
				task = strValue[0];
				address = strValue[1];
				size = strValue[2];
				long long int logicalAddress = stoll(address,nullptr,16); //logical address of the task
				long long int reqSize = taskSize(size); //task size
				long long int taskIndex = stoll(task.substr(1),nullptr,10);
				if(taskIndex >= tasks.size())
				{
					tasks.resize(taskIndex + 1);
				}
				tasks[taskIndex].memoryRequest(logicalAddress,reqSize);
			}
		}
		file.close();
}

// Function to allocate memory for singleLevelTask objects using a trace file
void inputOutputManager::traceFileMemoryAllocationForSingleLevelTask(string fileName, vector<singleLevelTask> &tasks, memoryManager &memoryManager) {
    fstream file;
		string str,soloTask;
		file.open(fileName,ios::in);
		if(file.is_open())
		{
			while(getline(file, soloTask))
			{
				string task,address,size;
				stringstream ss(soloTask);
				vector<string>strValue;
				while(getline(ss,str,':'))
				{
					strValue.push_back(str);
				}
				task = strValue[0];
				address = strValue[1];
				size = strValue[2];
				long long int logicalAddress = stoll(address,nullptr,16);
				long long int reqSize = taskSize(size);
				long long int taskIndex = stoll(task.substr(1),nullptr,10);
				// cout<<logicalAddress<<endl;
				if(taskIndex >= tasks.size())
				{
					tasks.resize(taskIndex + 1);
				}
				tasks[taskIndex].memoryRequest(logicalAddress,reqSize);
			}
		}
		file.close();
}

// Function to allocate memory for twoLevelTask objects using a trace file
void inputOutputManager::traceFileMemoryAllocationForTwoLevelTask(string fileName, vector<twoLevelTask> &tasks, memoryManager &memoryManager) {
fstream file;
		string str,soloTask;
		file.open(fileName,ios::in);
		if(file.is_open())
		{
			while(getline(file, soloTask))
			{
				string task,address,size;
				stringstream ss(soloTask);
				vector<string>strValue;
				while(getline(ss,str,':'))
				{
					strValue.push_back(str);
				}
				task = strValue[0];
				address = strValue[1];
				size = strValue[2];
				long long int logicalAddress = stoll(address,nullptr,16);
				long long int reqSize = taskSize(size);
				long long int taskIndex = stoll(task.substr(1),nullptr,10);
				if(taskIndex >= tasks.size())
				{
					tasks.resize(taskIndex + 1);
				}
				tasks[taskIndex].memoryRequest(logicalAddress,reqSize);
			}
		}
		file.close();
}
