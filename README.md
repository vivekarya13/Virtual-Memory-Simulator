# Virtual Memory Simulator — C++ Memory Management System

> Educational virtual memory simulator that models different page table implementations and memory-management strategies (map-based, single-level, two-level).  
> Simulates page translation, physical memory allocation, page faults, and measures performance (hit/miss rates, memory utilization, page table overhead, execution time).

---

## 📋 Project Overview

This project implements a configurable virtual memory simulator in C++. It models:

- **Page table implementations**: Map-based (STL `map`), single-level (linear), and two-level (hierarchical).  
- **Physical memory management**: Allocation/deallocation of frames.  
- **Trace-driven simulation**: Accepts trace files with memory access requests to drive the simulation.  
- **Performance monitoring**: Page hit/miss, memory utilization, page table sizes, and timing.

Primary educational goal: let students and researchers explore trade-offs between page table structures and memory-management strategies.

---

## 🏗️ Architecture

- **`final.cpp`** — CLI and main simulation orchestration  
- **`memoryManager.*`** — physical page frame allocation and bookkeeping  
- **`mapTask.*`** — map-based page table implementation (STL `map`)  
- **`singleLevelTask.*`** — single-level (flat) page table  
- **`twoLevelTask.*`** — hierarchical two-level implementation  
- **`inputOutputManager.*`** — trace parsing/generation, task size helpers  
- **`performanceModule.*`** — performance counters & reporting  
- **`testmodule.cpp`** — multithreaded synthetic trace generator  
- **`config.h`** — compile-time constants and memory layout

---

## 📁 Repository Structure

virtual-memory-simulator/

├── README.md

├── config.h

├── final.cpp

├── memoryManager.h

├── memoryManager.cpp

├── mapTask.h

├── mapTask.cpp

├── singleLevelTask.h

├── singleLevelTask.cpp

├── twoLevelTask.h

├── twoLevelTask.cpp

├── inputOutputManager.h

├── inputOutputManager.cpp

├── performanceModule.h

├── performanceModule.cpp

├── testmodule.cpp

├── input.txt

└── tracefile_*.txt


---

