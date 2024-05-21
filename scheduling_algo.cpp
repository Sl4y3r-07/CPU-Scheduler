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




    

    
}

void sjf(int arrival_time[], int burst_time[], int process_count) {
   
    cout <<Red<< "\t\t\tShortest Job Scheduling\n";
}

void rr(int arrival_time[], int burst_time[], int process_count) {
   
    cout <<Red<< "\t\t\tRound Robin algorithm \n";
}

void priority(int arrival_time[], int burst_time[], int process_count) {
    
    cout <<Red<< "\t\t\tPriority algorithm \n";
}

void multi_queue(int arrival_time[], int burst_time[], int process_count) {
    
    cout <<Red<< "\t\t\tMultilevel Queue Scheduling algorithm \n";
}
