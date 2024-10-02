#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// Job structure to hold job details
struct Job
{
      int jobId;
      string description;
      int priority;

      // Operator overloading for priority comparison (higher priority first)
      bool operator<(const Job &other) const
      {
            return priority < other.priority;
      }
};

// Process structure for SJF scheduling
struct Process
{
      int pid;          // Process ID
      int burst_time;   // Burst time
      int arrival_time; // Arrival time
};

// Priority queue to manage jobs
priority_queue<Job> jobQueue;

// Function to add a job to the queue
void addJob(int jobId, const string &description, int priority)
{
      Job newJob = {jobId, description, priority};
      jobQueue.push(newJob);
      cout << "Added Job ID: " << jobId << ", Priority: " << priority << endl;
}

// Function to display all jobs in the queue
void displayJobs()
{
      if (jobQueue.empty())
      {
            cout << "No jobs in the queue." << endl;
            return;
      }

      priority_queue<Job> tempQueue = jobQueue; // Create a copy to display jobs
      while (!tempQueue.empty())
      {
            Job job = tempQueue.top();
            tempQueue.pop();
            cout << "Job ID = [" << job.jobId << "]"
                 << ", Description = [" << job.description << "]"
                 << ", Priority = [" << job.priority << "]" << endl;
      }
}

// Function to execute the highest-priority job
void executeJob()
{
      if (jobQueue.empty())
      {
            cout << "No jobs to execute." << endl;
            return;
      }

      Job jobToExecute = jobQueue.top();
      jobQueue.pop();
      cout << "Executing Job ID = " << jobToExecute.jobId
           << ", Description = " << jobToExecute.description
           << ", Priority = " << jobToExecute.priority << endl;
}

/*SJF Algo. Code Implement--->*/

// Function to compare processes by burst time
bool compare_burst_time(const Process &p1, const Process &p2)
{
      return p1.burst_time < p2.burst_time;
}

// Function to compare processes by arrival time
bool compare_arrival_time(const Process &p1, const Process &p2)
{
      return p1.arrival_time < p2.arrival_time;
}

// Function to perform SJF scheduling
void SJF_scheduling(vector<Process> &processes)
{
      // Sort processes by arrival time
      sort(processes.begin(), processes.end(), compare_arrival_time);

      int current_time = 0;
      int total_waiting_time = 0;
      int total_turnaround_time = 0;

      cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";

      for (int i = 0; i < processes.size(); i++)
      {
            // If process arrives after current time, wait
            if (processes[i].arrival_time > current_time)
            {
                  current_time = processes[i].arrival_time;
            }

            // Sort remaining processes by burst time only if they have arrived
            sort(processes.begin() + i, processes.end(), [current_time](const Process &p1, const Process &p2)
                 { return p1.burst_time < p2.burst_time && p1.arrival_time <= current_time; });

            int waiting_time = current_time - processes[i].arrival_time;
            int turnaround_time = waiting_time + processes[i].burst_time;
            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;
            current_time += processes[i].burst_time;

            cout << processes[i].pid << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].arrival_time
                 << "\t\t" << waiting_time << "\t\t" << turnaround_time << endl;
      }

      cout << "Average Waiting Time: " << (float)total_waiting_time / processes.size() << endl;
      cout << "Average Turnaround Time: " << (float)total_turnaround_time / processes.size() << endl;
}

int main()
{
      int MainChoice;
      int jobId = 1; // Start job IDs from 1

      do
      {
            cout << "\nMain Menu\n";
            cout << "1. Job Scheduler\n";
            cout << "2. SJF Scheduling\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> MainChoice;

            // Ensure input validity
            if (cin.fail())
            {
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "Invalid input. Please enter a number." << endl;
                  continue;
            }

            switch (MainChoice)
            {
            case 1:
            {
                  int choice;
                  do
                  {
                        cout << "\nJob Scheduler Menu\n";
                        cout << "1. Add Job\n";
                        cout << "2. Display Jobs\n";
                        cout << "3. Execute Job\n";
                        cout << "4. Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        if (cin.fail())//For Output Not Gone To Infinite Loop.
                        {
                              cin.clear();
                              cin.ignore(numeric_limits<streamsize>::max(), '\n');
                              cout << "Invalid input. Please enter a number." << endl;
                              continue;
                        }

                        switch (choice)
                        {
                        case 1:
                        {
                              string description;
                              int priority;
                              cout << "Enter job description: ";
                              cin.ignore(); // Clear the newline character left in the input buffer
                              getline(cin, description);
                              cout << "Enter job priority (higher number = higher priority): ";
                              cin >> priority;

                              if (cin.fail())
                              {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Invalid priority input. Please enter an integer." << endl;
                              }
                              else
                              {
                                    addJob(jobId++, description, priority);
                              }
                              break;
                        }
                        case 2:
                              displayJobs();
                              break;
                        case 3:
                              executeJob();
                              break;
                        case 4:
                              cout << "Returning to main menu...\n";
                              break;
                        default:
                              cout << "Invalid choice. Please try again.\n";
                              break;
                        }
                  } while (choice != 4);

                  break;
            }
            case 2:
            {
                  vector<Process> processes;

                  // Add processes here (adjust as needed)
                  processes.push_back({1, 6, 0});
                  processes.push_back({2, 8, 1});
                  processes.push_back({3, 5, 2});
                  processes.push_back({4, 3, 3});

                  SJF_scheduling(processes);
                  break;
            }
            case 3:
                  cout << "Exiting...\n";
                  break;
            default:
                  cout << "Invalid choice. Please try again.\n";
                  break;
            }
      } while (MainChoice != 3);

      return 0;
}