# 🖥️ OS_Simulator
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Language: C](https://img.shields.io/badge/Language-C-blue)

**Author:** Jatin Joshi  
**Institution:** Fergusson College, Pune  
**Course:** MSc.CA, First Year  

---

## 📌 Project Overview

**OS_Simulator** is a command-line simulator demonstrating key operating system concepts using **C**.  
It helps students understand OS components like booting, process management, CPU scheduling, memory management, file systems, and synchronization in a visual, interactive way.

---

## ⚙️ Features

- **Booting Simulation**  
  - BIOS → Bootloader → Kernel → Shell  
  - Step-by-step visual output  

- **CPU Scheduling**  
  - FCFS, SJF, SRT, Round Robin, Priority (Preemptive & Non-preemptive)  
  - Gantt charts and average time calculations  

- **File Management System**  
  - Contiguous, Linked, and Indexed allocation  
  - File creation, deletion, and storage visualization  

- **Memory Management & Process Handling**  
  - Memory allocation simulation and PCB management  

- **Synchronization**  
  - Semaphore-based process synchronization examples  

---

## 🚀 How to Run

1. Clone the repository:

git clone https://github.com/Gobu105/OS_Simulator.git
cd OS_Simulator

Compile with GCC:
gcc OS.c -o os_simulator

Run the simulator:
./os_simulator

Follow the shell commands to explore modules.
🖼 Example Output:

Booting...
[BIOS] Initializing...
[Bootloader] Loading kernel...
[Kernel] Starting shell...
Shell> help
1. CPU Scheduling
2. File Management
3. Memory & Process
4. Synchronization
Select module:

---

🤝 Contribution
Contributions are welcome!

Fork the repository

Create a new branch for your feature or bugfix

Submit a pull request

Please follow the existing code style and directory structure.

---

Directory structure:
└── gobu105-os_simulator/

    ├── OS.c
    
    ├── utils.h
    
    ├── Booting_Stimulator/
    
    │   ├── BIOS.h
    
    │   ├── BootLoader.h
    
    │   ├── Kernel.h
    
    │   └── Shell.h
    
    ├── CPU_Scheduling/
    
    │   ├── cpu_scheduling.h
    
    │   ├── fcfs.h
    
    │   ├── pnp.h
    
    │   ├── pp.h
    
    │   ├── rr.h
    
    │   ├── sjf.h
    
    │   ├── srt.h
    
    │   └── swap.h
    
    ├── File_Management/
    
    │   ├── contiguous.h
    
    │   ├── file_management.h
    
    │   ├── indexed.h
    
    │   ├── linked.h
    
    ├── Memory_Management/
    
    │   ├── device_management.h
    
    │   ├── mem_management.h
    
    │   ├── memory_management.h
    
    │   └── virtual_memory.h
    
    ├── Process_Management/
    
    │   ├── pcb.h
    
    │   ├── process_management.h
    
    │   ├── states.h
    
    │   └── syscalls.h
    
    |── Synchronization/
    
    |   ├── deadlock.h
    
    |   ├── sync.h
    
    |   ├── synchronization.h
    
    |   └── thread.h
    
    └── README.md
