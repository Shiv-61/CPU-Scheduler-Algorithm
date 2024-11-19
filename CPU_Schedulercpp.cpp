#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

// Structure to represent a process
struct Process
{
    int id;
    int burstTime;
    int remainingTime;
    int priority;
    int arrivalTime;

    Process(int i, int bt, int p = 0, int at = 0)
        : id(i), burstTime(bt), remainingTime(bt), priority(p), arrivalTime(at) {}
};

// Function to simulate First-Come, First-Served (FCFS) CPU scheduling
void fcfsScheduler(const std::vector<Process> &processes)
{
    std::cout << "\nFCFS CPU Scheduling\n";

    int currentTime = 0, totalWaitTime = 0, totalTurnaroundTime = 0;

    for (const auto &process : processes)
    {
        int waitTime = currentTime;
        currentTime += process.burstTime;
        int turnaroundTime = currentTime;

        totalWaitTime += waitTime;
        totalTurnaroundTime += turnaroundTime;

        std::cout << "Process " << process.id
                  << ": Wait time = " << waitTime
                  << ", Turnaround time = " << turnaroundTime << "\n";
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

// Function to simulate Shortest Job First (SJF) CPU scheduling
void sjfScheduler(std::vector<Process> processes)
{
    std::cout << "\nSJF CPU Scheduling\n";

    std::sort(processes.begin(), processes.end(),
              [](const Process &a, const Process &b)
              { return a.burstTime < b.burstTime; });

    int currentTime = 0, totalWaitTime = 0, totalTurnaroundTime = 0;

    for (const auto &process : processes)
    {
        int waitTime = currentTime;
        currentTime += process.burstTime;
        int turnaroundTime = currentTime;

        totalWaitTime += waitTime;
        totalTurnaroundTime += turnaroundTime;

        std::cout << "Process " << process.id
                  << ": Wait time = " << waitTime
                  << ", Turnaround time = " << turnaroundTime << "\n";
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

// Function to simulate Shortest Remaining Job First (SRJF) CPU scheduling
void srjfScheduler(std::vector<Process> processes)
{
    std::cout << "\nSRJF CPU Scheduling\n";

    int currentTime = 0, completed = 0;
    int totalWaitTime = 0, totalTurnaroundTime = 0;

    while (completed < processes.size())
    {

        auto it = std::min_element(processes.begin(), processes.end(),
                                   [&](const Process &a, const Process &b)
                                   {
                                       return (a.remainingTime > 0 && (b.remainingTime == 0 || a.remainingTime < b.remainingTime));
                                   });

        if (it == processes.end() || it->remainingTime == 0)
        {
            currentTime++;
            continue;
        }

        it->remainingTime--;
        currentTime++;

        if (it->remainingTime == 0)
        {
            completed++;
            int turnaroundTime = currentTime;
            int waitTime = turnaroundTime - it->burstTime;

            totalWaitTime += waitTime;
            totalTurnaroundTime += turnaroundTime;

            std::cout << "Process " << it->id
                      << ": Wait time = " << waitTime
                      << ", Turnaround time = " << turnaroundTime << "\n";
        }
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

// Function to simulate Round Robin CPU scheduling
void roundRobinScheduler(std::vector<Process> processes, int timeQuantum)
{
    std::queue<Process *> processQueue;
    for (auto &process : processes)
    {
        processQueue.push(&process);
    }

    std::cout << "\nRound Robin CPU Scheduling\n";
    std::cout << "Time Quantum: " << timeQuantum << " units\n";

    int currentTime = 0;
    int totalWaitTime = 0, totalTurnaroundTime = 0;

    while (!processQueue.empty())
    {
        Process *current = processQueue.front();
        processQueue.pop();

        int timeToRun = std::min(current->remainingTime, timeQuantum);
        current->remainingTime -= timeToRun;
        currentTime += timeToRun;

        std::cout << "Process " << current->id << " executed for " << timeToRun << " units.\n";

        if (current->remainingTime == 0)
        {
            int turnaroundTime = currentTime;
            int waitTime = turnaroundTime - current->burstTime;

            totalWaitTime += waitTime;
            totalTurnaroundTime += turnaroundTime;

            std::cout << "Process " << current->id
                      << " completed: Wait time = " << waitTime
                      << ", Turnaround time = " << turnaroundTime << "\n";
        }
        else
        {
            processQueue.push(current);
        }
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

// Function to simulate Priority Preemptive Scheduler
void priorityPreemptiveScheduler(std::vector<Process> processes)
{
    std::cout << "\nPriority (Preemptive) CPU Scheduling\n";

    int currentTime = 0, completed = 0, totalWaitTime = 0, totalTurnaroundTime = 0;

    while (completed < processes.size())
    {

        auto it = std::min_element(processes.begin(), processes.end(),
                                   [&](const Process &a, const Process &b)
                                   {
                                       return (a.remainingTime > 0 && (b.remainingTime == 0 || a.priority < b.priority));
                                   });

        if (it == processes.end() || it->remainingTime == 0)
        {
            currentTime++;
            continue;
        }

        it->remainingTime--;
        currentTime++;

        if (it->remainingTime == 0)
        {
            completed++;
            int turnaroundTime = currentTime;
            int waitTime = turnaroundTime - it->burstTime;

            totalWaitTime += waitTime;
            totalTurnaroundTime += turnaroundTime;

            std::cout << "Process " << it->id
                      << ": Wait time = " << waitTime
                      << ", Turnaround time = " << turnaroundTime << "\n";
        }
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

// Function to simulate Priority Non-Preemptive Scheduler
void priorityNonPreemptiveScheduler(std::vector<Process> processes)
{
    std::cout << "\nPriority (Non-Preemptive) CPU Scheduling\n";

    std::sort(processes.begin(), processes.end(),
              [](const Process &a, const Process &b)
              { return a.priority < b.priority; });

    int currentTime = 0, totalWaitTime = 0, totalTurnaroundTime = 0;

    for (const auto &process : processes)
    {
        int waitTime = currentTime;
        currentTime += process.burstTime;
        int turnaroundTime = currentTime;

        totalWaitTime += waitTime;
        totalTurnaroundTime += turnaroundTime;

        std::cout << "Process " << process.id
                  << ": Wait time = " << waitTime
                  << ", Turnaround time = " << turnaroundTime << "\n";
    }

    std::cout << "\nAverage Wait Time: " << (float)totalWaitTime / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << "\n";
}

int main()
{
    char ch;
    bool check = false;
    while (!check)
    {
        int id, bt, pri;
        id = bt = pri = 0;
        std::cout << "Enter process ID, Burst-Time, Priority : " << std::endl;
        std::cin >> id;
        std::cin >> bt;
        std::cin >> pri;

        vector<Process> processes;
        processes.push_back(Process(id, bt, pri));
        int timeQuantum = 3;

        std::cout << "Choose a CPU Scheduling Algorithm:\n";
        std::cout << "1. First-Come, First-Served (FCFS)\n";
        std::cout << "2. Shortest Job First (SJF)\n";
        std::cout << "3. Priority Scheduling (Non-Preemptive)\n";
        std::cout << "4. Priority Scheduling (Preemptive)\n";
        std::cout << "5. Round Robin (RR)\n";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            fcfsScheduler(processes);
            break;
        case 2:
            sjfScheduler(processes);
            break;
        case 3:
            priorityNonPreemptiveScheduler(processes);
            break;
        case 4:
            priorityPreemptiveScheduler(processes);
            break;
        case 5:
            std::cout << "Time Quantum : " << timeQuantum;
            roundRobinScheduler(processes, timeQuantum);
            break;
        default:
            std::cout << "Invalid choice! Exiting...\n";
            break;
        }
        cout << "Want to add Process(y/n) : ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y')//adds one more process for the user
            check = false;
        else if (ch == 'n' || ch == 'N')
            check = true;
        else
        {
            cout << "Invalid Input" << endl;
            break;
        }
    }
    return 0;
}
