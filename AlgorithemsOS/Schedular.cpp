#include <iostream>
#include <queue>
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
            cout << "Job ID: " << job.jobId
                 << ", Description: " << job.description
                 << ", Priority: " << job.priority << endl;
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
      cout << "Executing Job ID: " << jobToExecute.jobId
           << ", Description: " << jobToExecute.description
           << ", Priority: " << jobToExecute.priority << endl;
}

// Main function to drive the job scheduler
int main()
{
      int choice;
      int jobId = 1; // Start job IDs from 1

      do
      {
            cout << "\nJob Scheduler Menu\n";
            cout << "1. Add Job\n";
            cout << "2. Display Jobs\n";
            cout << "3. Execute Job\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            // Ensure input validity
            if (cin.fail())
            {
                  cin.clear();
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
                  cout << "Exiting...\n";
                  break;
            default:
                  cout << "Invalid choice. Please try again.\n";
                  break;
            }
      } while (choice != 4);

      return 0;
}
