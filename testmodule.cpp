// testmodule.cpp

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

// Mutex for synchronizing file access
std::mutex mtx;

// Configuration constants (Ensure these are defined in config.h)
#ifndef CONFIG_H
#define CONFIG_H

const long long int PAGE_SIZE = 4096; // 4KB
const long long int TEXT_SECTION_START_ADDRESS = 0x00400000;
const long long int DATA_SECTION_START_ADDRESS = 0x00600000;
const long long int HEAP_SECTION_START_ADDRESS = 0x00800000;
const long long int SHARED_LIB_SECTION_START_ADDRESS = 0x00A00000;
const long long int STACK_SECTION_START_ADDRESS = 0x7FFDF000;

#endif // CONFIG_H

class TestModule {
public:
    // Generates a logical address within a section
    long long int generateAddress(long long int sectionStart, bool isStack) {
        if (isStack) {
            // For stack, generate addresses below the start address
            return sectionStart - (rand() % 2048) * PAGE_SIZE;
        }
        // For other sections, generate addresses above the start address
        return sectionStart + (rand() % 2048) * PAGE_SIZE;
    }

    // Generates a random task ID between 1 and 9
    int generateTaskId() {
        return (rand() % 9) + 1;
    }

    // Thread function to generate a single section trace
    void generateTraceSection(ofstream &outFile, int taskId, long long int sectionStart, bool isStack, const string &size) {
        long long int address = generateAddress(sectionStart, isStack);
        stringstream ss;
        ss << "T" << taskId << ":0x" << hex << address << ":" << size << endl;

        // Lock mutex to ensure thread-safe file writing
        std::lock_guard<std::mutex> lock(mtx);
        outFile << ss.str();
    }

    // Generates trace for a single task using multiple threads
    void generateTaskTrace(ofstream &outFile, int taskId) {
        // Define the sections and their sizes
        struct Section {
            long long int startAddress;
            bool isStack;
            string size;
        };

        vector<Section> sections = {
            {TEXT_SECTION_START_ADDRESS, false, "4KB"},
            {DATA_SECTION_START_ADDRESS, false, "8KB"},
            {HEAP_SECTION_START_ADDRESS, false, "12KB"},
            {SHARED_LIB_SECTION_START_ADDRESS, false, "16KB"},
            {STACK_SECTION_START_ADDRESS, true, "24KB"}
        };

        // Create a thread for each section
        vector<thread> threads;
        for (const auto &sec : sections) {
            threads.emplace_back(&TestModule::generateTraceSection, this, ref(outFile), taskId, sec.startAddress, sec.isStack, sec.size);
        }

        // Wait for all threads to complete
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    // Generates the entire trace file with the specified number of tasks
    void generateTrace(int numTasks, const string &fileName = "input.txt") {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        ofstream outFile(fileName, ios::out);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open file " << fileName << " for writing." << endl;
            return;
        }

        // Generate trace for each task
        for (int i = 0; i < numTasks; ++i) {
            int taskId = generateTaskId();
            generateTaskTrace(outFile, taskId);
        }

        outFile.close();
        cout << "Trace generation completed. Output written to " << fileName << endl;
    }
};

int main() {
    TestModule testModule;
    long long int inputSize;

    cout << "Enter the number of tasks to generate (each task generates 5 sections): ";
    cin >> inputSize;

    if (inputSize <= 0) {
        cerr << "Error: Number of tasks must be a positive integer." << endl;
        return 1;
    }

    testModule.generateTrace(static_cast<int>(inputSize));
    return 0;
}
