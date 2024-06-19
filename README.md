# CPU_schedular:
# Project Description:
-A CPU scheduler is an essential part of an operating system that manages process execution. It determines which process will use the CPU and for what duration, aiming to maximize resource efficiency. By employing various algorithms and policies, it balances factors such as throughput, response time, and fairness to enhance overall system performance. Essentially, the CPU scheduler functions as a traffic controller for the CPU, directing the flow of processes to ensure smooth operation.
# How to run the project?
**Step 1:** Prepare the Environment
 **Install a C++ Compiler:**
 -Ensure you have a C++ compiler installed. For Linux and macOS, g++ is a common choice. On Windows, you can use MinGW or Visual Studio.
 -For Linux/macOS, you can install g++ via a package manager:
  **Download the JSON Library:**
  -Download the json.hpp file from the nlohmann/json GitHub repository(Link :https://github.com/nlohmann/json/releases/latest)
  -Place the json.hpp file in the same directory as your C++ source file.
**Step 2:** Create the Source File
 - Create a new C++ source file: Name it and copy the provided code into this file.
**Step 3:** Compile the Program
 -Open a terminal or command prompt. 
 -Navigate to the directory where your cpp file is located.
 -Compile the program using the g++ compiler:
**Step 4:** Run the Executable
 -Run the compiled program:
 -Provide input when prompted:
 -Example input:
 4
 1 0 8 2
 2 1 4 1
 3 2 9 3
 4 3 5 2
 3
**Step 5:** View the Output
 -Check the output file:
 - The program writes the results to a file named XYZ.json in the same directory.Open the XYZ.json file:
  -Use any text editor or a JSON viewer to examine the scheduling results.
# Prerequisites:
- A C++ compiler (e.g., g++, clang++)
- Basic understanding of how to compile and run C++ programs
# Internal Working of project:
This project implements a hybrid CPU scheduling algorithm that combines features of multiple scheduling techniques to balance performance metrics like waiting time, turnaround time, CPU utilization, and throughput. The hybrid scheduler uses priority scheduling along with Round Robin within each priority level, and it includes an aging mechanism to prevent starvation of lower-priority processes.
# Key Components:
**Process Structure:** Defines process attributes: ID, arrival time, burst time, remaining time, priority, and last execution time.
**Reading Input:** Reads process details and initializes remaining time and last execution time.
**Calculate Metrics:** Computes average waiting time, turnaround time, CPU utilization, and throughput based on completion times.
**Hybrid Scheduling:** Uses a priority queue and Round Robin within each priority level, incorporating aging to prevent starvation.
**Writing Results:** Outputs scheduling results to a JSON file, including the schedule, average waiting time, average turnaround time, CPU utilization, and throughput.
 # Learning Takeaways from the Project:
- Understanding the fundamental concepts of process scheduling in operating systems.
- Implementing various CPU scheduling algorithms in C++.
- Enhancing problem-solving skills by managing and manipulating arrays and vectors.
- Gaining practical experience with mathematical operations, such as finding factors of numbers.
- Developing proficiency in C++ programming, including the use of loops, conditionals, and standard libraries.
 # Resources and References:
 Online Resources
**Wikipedia** - Process Scheduling:
 Process Scheduling
 Overview of different scheduling algorithms, including FCFS, SJN, Round Robin, and Priority Scheduling.
**GeeksforGeeks** - CPU Scheduling Algorithms:
   CPU Scheduling Algorithms
  Detailed explanations and examples of various CPU scheduling algorithms.
**nlohmann/json GitHub Repository:**
 nlohmann/json
 The official repository for the JSON library used in the project. It includes documentation and usage examples.
**Documentation**
**C++ Standard Library Documentation:**
-C++ Reference
- Detailed reference for the C++ Standard Library, covering containers, algorithms, and file handling.
**GNU G++ Compiler Documentation:**
-G++ Documentation
-Official documentation for the GNU Compiler Collection, including usage and options for compiling C++ programs.
**nlohmann/json Documentation:**
 - nlohmann/json Documentation
- Comprehensive guide to using the nlohmann/json library for JSON parsing and serialization in C++.
- **Tools**
Compiler and IDE:
Visual Studio Code: A lightweight, free code editor with support for C++.
**JSON Viewer/Editor:**
- JSONLint: JSONLint: A tool for validating and formatting JSON.
- VSCode JSON Tools: Extensions for Visual Studio Code to view and edit JSON files.
**Version Control:**
-GitHub: A platform for hosting and collaborating on Git repositories.
