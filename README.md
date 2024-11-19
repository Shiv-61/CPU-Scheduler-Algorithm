
# CPU Scheduler Algorithm

A repository to explore and implement various CPU scheduling algorithms, focusing on understanding their functionality, efficiency, and trade-offs.

## **Implemented Algorithms**

1. **First-Come, First-Served (FCFS)**  
   - Simple and straightforward.  
   - Processes are executed in the order of arrival.  
   - May result in high waiting time due to the **convoy effect**.

2. **Shortest Job Next (SJN)**  
   - Prioritizes processes with the shortest execution time.  
   - Minimizes average waiting time but may cause starvation for longer processes.
 
3. **Round Robin (RR)**  
   - Each process gets a fixed time slice (quantum).  
   - Ensures fairness and is widely used in time-sharing systems.

4. **Priority Scheduling (Non-Preemptive)**  
   - Executes processes based on priority, without interruption.  
   - Lower-priority processes wait until higher-priority ones are complete.  
   - May cause starvation if not managed with aging.

5. **Priority Scheduling (Preemptive)**  
   - Interrupts lower-priority processes if a higher-priority process arrives.  
   - Ensures responsiveness for high-priority processes.  
   - Aging can be implemented to prevent starvation.

---

## **Features**

- Visual representation of scheduling algorithms.
- Performance metrics: Average Waiting Time, Turnaround Time, and CPU Utilization.
- Adjustable parameters for experiments (e.g., quantum time, priority levels).
- Practical examples and simulations.

---

## **How to Use**

1. Clone the repository:  
   ```bash
   git clone https://github.com/Shiv-61/CPU-Scheduler-Algorithm.git
   ```

2. Navigate to the directory:  
   ```bash
   cd CPU-Scheduler-Algorithm
   ```

3. Run the simulation program to experiment with the algorithms.

---

## **Technologies Used**

- Programming Language: C++.
- Libraries Used : STL and unistd.h libraries.

---

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
