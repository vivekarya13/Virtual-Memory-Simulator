#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "config.h"

using namespace std;

mutex mtx; // Mutex for synchronizing file access

class TestModule {
public:
    long long int generateAddresses(long long int sectionStart, int j) {
        if (j == 2) {
            long long int address = sectionStart - (rand() % 2048) * PAGE_SIZE;
            return address;
        }
        long long int address = sectionStart + (rand() % 2048) * PAGE_SIZE;
        return address;
    }

    int taskValue() {
        return ((rand() % 9) + 1);
    }

    void generateTraceSection(ofstream &outFile, int taskId, long long int sectionStart, int j, const string &size) {
        long long int address = generateAddresses(sectionStart, j);
        lock_guard<mutex> lock(mtx); // Lock mutex to ensure thread-safe file writing
        outFile << "T" << taskId << ":0x" << hex << address << ":" << size << endl;
    }

    void generateTrace(int numTasks) {
        std::srand(std::time(0));
        ofstream outFile("input.txt");
        if (!outFile) {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        for (int i = 1; i <= numTasks; ++i) {
            int taskId = taskValue();

            // Create threads for each section
            vector<thread> threads;
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, TEXT_SECTION_START_ADDRESS, 1, "4KB");
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, DATA_SECTION_START_ADDRESS, 1, "8KB");
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, HEAP_SECTION_START_ADDRESS, 1, "12KB");
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, SHARED_LIB_SECTION_START_ADDRESS, 1, "16KB");
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, STACK_SECTION_START_ADDRESS, 2, "24KB");

            // Wait for all threads to finish
            for (auto &t : threads) {
                t.join();
            }
        }

        outFile.close();
    }
};

int main() {
    TestModule testModule;
    long long int inputSize;
    cout << "Give the trace size multiple of 5" << endl;
    cout << "Because for each Task it will generate 5 sections." << endl;
    cin >> inputSize;

    if (inputSize % 5 != 0) {
        cerr << "Error: Input size must be a multiple of 5." << endl;
        return 1;
    }

    testModule.generateTrace(inputSize / 5);
    return 0;
}
