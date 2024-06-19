#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include "json.hpp"
#include <fstream>


using namespace std;
using json = nlohmann::json;


//includes necessary headers for input/output, data structures, and JSON handling.
//json is a type alias for convenience

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int last_execution_time;
};

//Defines a Process struct to hold process attributes

void read_input(vector<Process>& processes) {
    int n;
    cin >> n;

    processes.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].process_id >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time for Round Robin
        processes[i].last_execution_time = 0; // For aging
    }
}
//Reads the number of processes and their details.
//Initializes remaining_time and last_execution_time for each process

void calculate_metrics(const vector<Process>& processes, const vector<int>& completion_times, float& avg_waiting_time, float& avg_turnaround_time) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        int turnaround_time = completion_times[i] - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;
        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;
    }
    avg_waiting_time = static_cast<float>(total_waiting_time) / processes.size();
    avg_turnaround_time = static_cast<float>(total_turnaround_time) / processes.size();
}

//Computes the average waiting time and turnaround time for processes based on their completion times

json hybrid_scheduling(vector<Process> processes, int quantum) {
    int current_time = 0;
    int total_idle_time = 0;
    vector<int> completion_times(processes.size());
    vector<int> schedule;

    auto cmp = [](const Process& a, const Process& b) { return a.priority > b.priority; };
    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);

    int i = 0;
    while (i < processes.size() || !pq.empty()) {
        while (i < processes.size() && processes[i].arrival_time <= current_time) {
            pq.push(processes[i]);
            ++i;
        }

        if (!pq.empty()) {
            Process current_process = pq.top();
            pq.pop();

            int time_slice = min(quantum, current_process.remaining_time);
            for (int j = 0; j < time_slice; ++j) {
                schedule.push_back(current_process.process_id);
            }
            current_time += time_slice;
            current_process.remaining_time -= time_slice;
            current_process.last_execution_time = current_time;

            if (current_process.remaining_time > 0) {
                while (i < processes.size() && processes[i].arrival_time <= current_time) {
                    pq.push(processes[i]);
                    ++i;
                }
                pq.push(current_process);
            } else {
                completion_times[current_process.process_id - 1] = current_time;
            }
        } else {
            total_idle_time++;
            ++current_time;
        }

        // Implement aging to prevent starvation
        vector<Process> temp_processes;
        while (!pq.empty()) {
            Process p = pq.top();
            pq.pop();
            if (current_time - p.last_execution_time > 10) { // Example aging threshold
                p.priority--;
            }
            temp_processes.push_back(p);
        }
        for (const auto& p : temp_processes) {
            pq.push(p);
        }
    }

    float avg_waiting_time, avg_turnaround_time;
    calculate_metrics(processes, completion_times, avg_waiting_time, avg_turnaround_time);
    float cpu_utilization = (static_cast<float>(current_time - total_idle_time) / current_time) * 100;
    float throughput = static_cast<float>(processes.size()) / current_time;

    json result;
    result["schedule"] = schedule;
    result["avg_waiting_time"] = avg_waiting_time;
    result["avg_turnaround_time"] = avg_turnaround_time;
    result["cpu_utilization"] = cpu_utilization;
    result["throughput"] = throughput;

    return result;
}
//Priority Queue: Manages processes based on priority.
//Round Robin: Uses Round Robin scheduling within each priority level.
//Aging: Adjusts priorities to prevent starvation.
//Metrics Calculation: Computes average waiting time, turnaround time, CPU utilization, and throughput



void write_to_json(const std::string& filename, const json& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << data.dump(4); // Pretty-print with 4-space indentation
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

//Writes the scheduling results to a JSON file

int main() {
    vector<Process> processes;
    read_input(processes);

    // Sorting processes by arrival time before we start
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int quantum;
    cin >> quantum;
    //Reads Input: Reads process details and quantum value.

    json output;
    output["hybrid"] = hybrid_scheduling(processes, quantum);

    // Writing JSON data to the following file
    write_to_json("hybrid_scheduling_results.json", output);

    return 0;
    
//Sorts Processes: Sorts by arrival time
//Executes Scheduling: Calls hybrid_scheduling function
//Writes Output: Writes results to hybrid_scheduling_results.json
}
