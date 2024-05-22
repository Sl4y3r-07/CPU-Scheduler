// scheduling_algorithms.cpp
#include "scheduling_algo.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

struct Process{
    int proc_id;
    int arr_time;
    int b_time;
};

    const string Green0 = "\033[1;32m";
    const string RESET = "\033[0m";
    const string Yellow= "\033[1;33m";
    const string Red= "\033[1;31m";
    const string Blue = "\033[36m";
    const string Magenta = "\033[35m";
    const string Green1="\033[92m";

 bool compareArrivalTime(Process &p1, Process &p2)
    {
        return p1.arr_time<p2.arr_time;
    }
 bool compareBurstTime(Process &p1, Process &p2)
 {
        return p1.b_time<p2.b_time;
 }

void fcfs(int arrival_time[], int burst_time[], int process_count) {
    
    cout << Red << "\t\t\t***********************************\n";
    cout << Red << "\t\t\t*  First Come First Serve (FCFS)  *\n";
    cout << Red << "\t\t\t***********************************\n\n";
    cout <<Green0<<">"<<Green1<<" In this algorithm, the process that requests the CPU first is allocated the CPU first\n";
    cout <<Green0<<">"<<Green1<<" It is implemented by FIFO Queue\n";
    cout <<Green0<<">"<<Green1<<" This algorithm does not have any mechanism for prioritizing processes\n";
    cout <<Green0<<">"<<Green1<<" It is considered a non-preemptive algorithm\n";

    // Algo starts from here 

    vector<Process> processes(process_count);
    for(int i=0;i<process_count;i++)
    {
        processes[i]={i+1, arrival_time[i], burst_time[i]};
    }
    // sorting by arrival time
    sort(processes.begin(), processes.end(),compareArrivalTime);

    int waiting_time[process_count];
    waiting_time[0]= 0;

    int start_time[process_count];

    int current_time=0;

   
    cout << Green0 << ">" << Magenta << " Process Execution Details:\n";
    cout << Green0 << ">" << Magenta << " --------------------------\n";

    for(int i=0;i<process_count;i++)
    {
       if (current_time < processes[i].arr_time) {
            cout << Green0 << ">" << Blue << " CPU is idle from time " << current_time 
                 << " to " << processes[i].arr_time << "\n";
            current_time = processes[i].arr_time;
        }
       
       start_time[i] = current_time;
       waiting_time[i]= start_time[i]-processes[i].arr_time;

       cout << Green0 << ">" << Blue << " Process " << processes[i].proc_id << " is running from time " << current_time << " to " << current_time + processes[i].b_time << "\n";
       
       current_time += processes[i].b_time;

    }

    
    cout << Green0 << "\t\t+----------+--------------+------------+-------------+--------------+\n";
    cout << "\t\t| " << setw(8) << "Process" << " | " << setw(12) << "Arrival Time" << " | "<< setw(10) << "Burst Time" << " | " << setw(11) << "Start Time" << " | "<< setw(12) << "Waiting Time" << " |\n";
    cout << Green0 << "\t\t+----------+--------------+------------+-------------+--------------+\n";

    
     for (int i=0;i<process_count;i++) {
        cout << "\t\t| " << setw(8) <<processes[i].proc_id  << " | " << setw(12) << processes[i].arr_time << " | "<< setw(10) << processes[i].b_time << " | " << setw(11) << start_time[i] << " | "<< setw(12) << waiting_time[i] << " |\n";
    }

    
    cout << "\t\t+----------+--------------+------------+-------------+--------------+\n";  

    double avg_waiting_time=0;
    for(int i=0;i<process_count;i++)
    {
        avg_waiting_time+=waiting_time[i];
    }  
    avg_waiting_time= (double)avg_waiting_time/process_count;
    cout << Green0 << ">" << Blue << " Average waiting time is : "<< Magenta<<avg_waiting_time<<"\n";
    
}

void sjf(int arrival_time[], int burst_time[], int process_count) {
   
    cout << Red << "\t\t\t***********************************\n";
    cout << Red << "\t\t\t*    Shortest Job First (SJF)     *\n";
    cout << Red << "\t\t\t***********************************\n\n";

    cout <<Green0<<">"<<Green1<<" In this type, CPU is assigned to the process that has the smallest next CPU burst\n";
    cout <<Green0<<">"<<Green1<<" If the next CPU bursts of two processes are the same, FCFS scheduling is used to break the tie\n";
    cout <<Green0<<">"<<Green1<<" It is non-preemptive (i.e, I have implemented non-preemptive for now.)\n";

    //Algo starts from here 

    vector<Process> processes(process_count);
    for(int i=0;i<process_count;i++)
    {
        processes[i]={i+1, arrival_time[i], burst_time[i]};
    }
    // sorting by arrival time
    sort(processes.begin(), processes.end(),compareArrivalTime);
    //Because, first process that is to be executed is to be decided by arrival time.
    sort(processes.begin()+1, processes.end(),compareBurstTime); //sorting by burst time :)

    int waiting_time[process_count];
    waiting_time[0]= 0;

    int start_time[process_count];

    int current_time=0;

    cout << Green0 << ">" << Magenta << " Process Execution Details:\n";
    cout << Green0 << ">" << Magenta << " --------------------------\n";

    for(int i=0;i<process_count;i++)
    {
       if (current_time < processes[i].arr_time) {
            cout << Green0 << ">" << Blue << " CPU is idle from time " << current_time 
                 << " to " << processes[i].arr_time << "\n";
            current_time = processes[i].arr_time;
        }
       
       start_time[i] = current_time;
       waiting_time[i]= start_time[i]-processes[i].arr_time;

       cout << Green0 << ">" << Blue << " Process " << processes[i].proc_id << " is running from time " << current_time << " to " << current_time + processes[i].b_time << "\n";
       
       current_time += processes[i].b_time;

    }

      cout << Green0 << "\t\t+----------+--------------+------------+-------------+--------------+\n";
    cout << "\t\t| " << setw(8) << "Process" << " | " << setw(12) << "Arrival Time" << " | "<< setw(10) << "Burst Time" << " | " << setw(11) << "Start Time" << " | "<< setw(12) << "Waiting Time" << " |\n";
    cout << Green0 << "\t\t+----------+--------------+------------+-------------+--------------+\n";

    
     for (int i=0;i<process_count;i++) {
        cout << "\t\t| " << setw(8) <<processes[i].proc_id  << " | " << setw(12) << processes[i].arr_time << " | "<< setw(10) << processes[i].b_time << " | " << setw(11) << start_time[i] << " | "<< setw(12) << waiting_time[i] << " |\n";
    }

    
    cout << "\t\t+----------+--------------+------------+-------------+--------------+\n";   

    double avg_waiting_time=0;
    for(int i=0;i<process_count;i++)
    {
        avg_waiting_time+=waiting_time[i];
    }  
    avg_waiting_time= (double)avg_waiting_time/process_count;

    cout << Green0 << ">" << Blue << " Average waiting time is : "<< Magenta<<avg_waiting_time<<"\n";
       

}

void rr(int arrival_time[], int burst_time[], int process_count) {
   
    cout << Red << "\t\t\t***********************************\n";
    cout << Red << "\t\t\t*    Round Robin Algorithm (RR)   *\n";
    cout << Red << "\t\t\t***********************************\n\n";

    cout <<Green0<<">"<<Green1<<" It is a preemptive scheduling algorithm\n";
    cout <<Green0<<">"<<Green1<<" A small unit of time, called a time quantum or time slice, is defined\n";
    cout <<Green0<<">"<<Green1<<" No process is allocated the CPU for more than 1 time quantum in a row\n";
  
    //Algo starts from here 
    int time_quantum;
    cout<<Green0<<">"<<Yellow<<" Enter the value of time quanta: "<<Blue;
    cin>>time_quantum;

    vector<Process> processes(process_count);
    for(int i=0;i<process_count;i++)
    {
        processes[i]={i+1, arrival_time[i], burst_time[i]};
    }
    // sorting by arrival time
    sort(processes.begin(), processes.end(),compareArrivalTime);

    vector<int> waiting_time(process_count, 0);
    vector<int> start_time(process_count, 0);
    vector<int> completion_time(process_count, 0);
    vector<int> turnaround_time(process_count, 0);

    int current_time=0; int process_completed=0;

    vector<int> temp_burst_time(process_count);
    for(int i=0;i<process_count;i++)
    {
        temp_burst_time[i]=processes[i].b_time;
    }

    vector<int> ready_process_queue;  // ready_process_queue for those processes that are ready for execution
    int idx=0;

    cout << Green0 << ">" << Magenta << " Process Execution Details:\n";
    cout << Green0 << ">" << Magenta << " --------------------------\n";
    
    while(process_completed!=process_count)
    {
      while(idx<process_count && processes[idx].arr_time<=current_time)
      {
        ready_process_queue.push_back(idx);
        idx++;
      }

      // when ready queue is emptied, then cpu will be idle and waiting for the processes to arrive
      if (ready_process_queue.empty()) {
            cout <<Green0<<">"<<Blue<<" CPU is idle from time " << current_time << " to " << processes[idx].arr_time << "\n";;
            current_time = processes[idx].arr_time;
            continue;
        }

        int i = ready_process_queue.front();  // for fetching first process in the ready_process_queue
        ready_process_queue.erase(ready_process_queue.begin()); // and second process will come in place of first process.
        
        if(temp_burst_time[i]==processes[i].b_time)
        {
            start_time[i]=current_time;
        }
       
        if (temp_burst_time[i] > 0) {
            if (temp_burst_time[i] > time_quantum) {
                current_time += time_quantum;
                temp_burst_time[i] -= time_quantum;
                 }
            else {
                current_time += temp_burst_time[i];
                temp_burst_time[i] = 0;
                completion_time[i]= current_time;
                process_completed++;
            }
      
          while (idx < process_count && processes[idx].arr_time <= current_time) {
                ready_process_queue.push_back(idx);
                idx++;
            }

           if(temp_burst_time[i]>0)
           {
             ready_process_queue.push_back(i);   // if the process has remaining burst time, then it needs to be add back to the ready_process_queue but at the back
           }
    }
    }

    for(int i=0;i<process_count;i++)
    {
        turnaround_time[i]= completion_time[i]-processes[i].arr_time;
        waiting_time[i]= turnaround_time[i]-processes[i].b_time;
    }

     cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";
    cout << "\t\t| " << setw(8) << "Process" << " | " << setw(12) << "Arrival Time" << " | " << setw(10) << "Burst Time" << " | " << setw(11) << "Start Time" << " | " << setw(14) << "Completion " << " | " << setw(14) << "Turnaround " << " | " << setw(12) << "Waiting Time" << " |\n";
    cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";

    for (int i = 0; i < process_count; i++) {
        cout << "\t\t| " << setw(8) << processes[i].proc_id << " | " << setw(12) << processes[i].arr_time << " | " << setw(10) << processes[i].b_time << " | " << setw(11) << start_time[i] << " | " << setw(14) << completion_time[i] << " | " << setw(14) << turnaround_time[i] << " | " << setw(12) << waiting_time[i] << " |\n";
    }

    cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";
 

    double avg_waiting_time=0;
    for(int i=0;i<process_count;i++)
    {
        avg_waiting_time+=waiting_time[i];
    }  
    avg_waiting_time= (double)avg_waiting_time/process_count;

    cout << Green0 << ">" << Blue << " Average waiting time is : "<< Magenta<<avg_waiting_time<<"\n";
       
}

void priority(int arrival_time[], int burst_time[], int process_count) {
    
    cout <<Red<< "\t\t\tPriority algorithm \n";
}

void multi_queue(int arrival_time[], int burst_time[], int process_count) {
    
    cout <<Red<< "\t\t\tMultilevel Queue Scheduling algorithm \n";
}
