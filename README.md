# 🖥️ OS_Simulator
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Language: C](https://img.shields.io/badge/Language-C-blue)

**Author:** Gobu  
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

## 🗂️ Project Structure

OS_Simulator/
├── bios.h
├── bootloader.h
├── kernel.h
├── shell.h
├── cpu_scheduling.h
├── file_management/
│ ├── contiguous.h
│ ├── linked.h
│ └── indexed.h
├── utils.h
├── main.c
└── README.md

yaml
Copy code

---

## 🚀 How to Run

1. Clone the repository:


git clone https://github.com/username/OS_Simulator.git
cd OS_Simulator
Compile with GCC:


Copy code
gcc main.c -o os_simulator
Run the simulator:


Copy code
./os_simulator
Follow the shell commands to explore modules.

🖼 Example Output
text
Copy code
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
🤝 Contribution
Contributions are welcome!

Fork the repository

Create a new branch for your feature or bugfix

Submit a pull request

Please follow the existing code style and directory structure.
