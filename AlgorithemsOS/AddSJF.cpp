// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// struct Process
// {
//       int pid;          // Process ID
//       int burst_time;   // Burst time
//       int arrival_time; // Arrival time
// };

// bool compare_burst_time(const Process &p1, const Process &p2)
// {
//       return p1.burst_time < p2.burst_time;
// }

// bool compare_arrival_time(const Process &p1, const Process &p2)
// {
//       return p1.arrival_time < p2.arrival_time;
// }

// void SJF_scheduling(vector<Process> &processes)
// {
//       // Sort processes by arrival time
//       sort(processes.begin(), processes.end(), compare_arrival_time);

//       int current_time = 0;
//       int total_waiting_time = 0;
//       int total_turnaround_time = 0;

//       cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";

//       for (int i = 0; i < processes.size(); i++)
//       {
//             // If process arrives after current time, wait
//             if (processes[i].arrival_time > current_time)
//             {
//                   current_time = processes[i].arrival_time;
//             }

//             // Sort remaining processes by burst time only if they have arrived
//             sort(processes.begin() + i, processes.end(), [current_time](const Process &p1, const Process &p2)
//                  { return p1.burst_time < p2.burst_time && p1.arrival_time <= current_time; });

//             int waiting_time = current_time - processes[i].arrival_time;
//             int turnaround_time = waiting_time + processes[i].burst_time;
//             total_waiting_time += waiting_time;
//             total_turnaround_time += turnaround_time;
//             current_time += processes[i].burst_time;

//             cout << processes[i].pid << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].arrival_time
//                  << "\t\t" << waiting_time << "\t\t" << turnaround_time << endl;
//       }

//       cout << "Average Waiting Time: " << (float)total_waiting_time / processes.size() << endl;
//       cout << "Average Turnaround Time: " << (float)total_turnaround_time / processes.size() << endl;
// }

// int main()
// {
//       vector<Process> processes;

//       // Add processes here (adjust as needed)
//       processes.push_back({1, 6, 0});
//       processes.push_back({2, 8, 1});
//       processes.push_back({3, 5, 2});
//       processes.push_back({4, 3, 3});

//       SJF_scheduling(processes);

//       return 0;
// }
