// scheduling_algorithms.cpp
#include "scheduling_algo.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct Process{
    int proc_id;
    int arr_time;
    int b_time;
};

struct Process_priority{
    int proc_id;
    int arr_time;
    int b_time;
    int priority;
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

 bool compareArrivalTime_priority(Process_priority &p1, Process_priority &p2 )
 {
   if(p1.arr_time==p2.arr_time)
   {
    return p1.priority<p2.priority;
   }
   else 
   {
    return p1.arr_time<p2.arr_time;
   }
 }

  int next_process(vector<Process_priority> &processes, int current_time,vector<int> &temp_burst_time)
 {
    int next_process_idx=-1;
    int higher_priority=INT_MAX;
    for(int i=0;i<processes.size();i++)
    {
       if(processes[i].arr_time<=current_time && temp_burst_time[i]>0)
       {
          if(processes[i].priority<higher_priority)
          {
            next_process_idx=i;
            higher_priority= processes[i].priority;
          }
       }
    }

    return next_process_idx;
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
    cout <<Green0<<">"<<Green1<<" It is non-preemptive \n";

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
 

    double avg_waiting_time = 0; double avg_turnaround_time=0;
    for (int i = 0; i < process_count; ++i) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time+=turnaround_time[i];
    }
    avg_waiting_time = avg_waiting_time / process_count;
    avg_turnaround_time= avg_turnaround_time/process_count;


    cout << Green0 << ">" << Blue << " Average waiting time is : " << Magenta << avg_waiting_time << "\n";
    cout << Green0 << ">" << Blue << " Average turnaround time is : " << Magenta << avg_turnaround_time << "\n";
     
}

void priority(int arrival_time[], int burst_time[], int process_count) {
    
    cout << Red << "\t\t\t***********************************\n";
    cout << Red << "\t\t\t*        Priority Algorithm       *\n";
    cout << Red << "\t\t\t***********************************\n\n";

    cout <<Green0<<">"<<Green1<<" Each process is assigned a priority. Process with highest priority is to be executed first and so on\n";
    cout <<Green0<<">"<<Green1<<" Processes with same priority are executed on their arrival time\n";
    cout <<Green0<<">"<<Green1<<" It is preemptive (which is implemented here, though it can be non preemptive also)\n";
   
    cout<<Green0<<">"<<Yellow<<" Enter the priority of the processes (starting from 1): \n";
    int priority_=0;
    vector<Process_priority> processes(process_count);
    for(int i=0;i<process_count;i++)
    {   cout<<Green0<< ">"<<Blue<<" Process "<<i+1<<" "<<Magenta;
        cin>>priority_;
        processes[i]={i+1, arrival_time[i], burst_time[i],priority_};
    }

    sort(processes.begin(),processes.end(),compareArrivalTime_priority);

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

    cout << Green0 << ">" << Magenta << " Process Execution Details:\n";
    cout << Green0 << ">" << Magenta << " --------------------------\n"<<Blue;

    // In this we need to check whether the next process having higher priority than the current process executing
    while(process_completed!=process_count)
    {
       
       int i= next_process(processes,current_time,temp_burst_time);
       
       if(i!=-1)
       {
       // when next process is selected
       if(temp_burst_time[i]==processes[i].b_time)
       {
        start_time[i]=current_time;
       }

       temp_burst_time[i]--; current_time++;

       if(temp_burst_time[i]==0)
       {
         process_completed++;
         completion_time[i]=current_time;
         turnaround_time[i]=completion_time[i]-processes[i].arr_time;
         waiting_time[i]=turnaround_time[i]-processes[i].b_time;
        }
       }
       else {
         current_time++;
       }
    }
    
   cout << "\t\t+----------+--------------+------------+----------+-------------+----------------+-----------------+-------------+\n";
    cout << "\t\t| " << setw(8) << "Process" << " | " << setw(12) << "Arrival Time" << " | " << setw(10) << "Burst Time" << " | " << setw(8) << "Priority" << " | " << setw(11) << "Start Time" << " | " << setw(14) << "Completion " << " | " << setw(14) << "Turnaround " << " | " << setw(12) << "Waiting Time" << " |\n";
    cout << "\t\t+----------+--------------+------------+----------+-------------+----------------+-----------------+-------------+\n";

    for (int i = 0; i < process_count; i++) {
        cout << "\t\t| " << setw(8) << processes[i].proc_id << " | " << setw(12) << processes[i].arr_time << " | " << setw(10) << processes[i].b_time << " | " << setw(8) << processes[i].priority << " | " << setw(11) << start_time[i] << " | " << setw(14) << completion_time[i] << " | " << setw(14) << turnaround_time[i] << " | " << setw(12) << waiting_time[i] << " |\n";
    }

    cout << "\t\t+----------+--------------+------------+----------+-------------+----------------+-----------------+-------------+\n";

    double avg_waiting_time = 0; double avg_turnaround_time=0;
    for (int i = 0; i < process_count; ++i) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time+=turnaround_time[i];
    }
    avg_waiting_time = avg_waiting_time / process_count;
    avg_turnaround_time= avg_turnaround_time/process_count;


    cout << Green0 << ">" << Blue << " Average waiting time is : " << Magenta << avg_waiting_time << "\n";
    cout << Green0 << ">" << Blue << " Average turnaround time is : " << Magenta << avg_turnaround_time << "\n";
    
}

void srtf(int arrival_time[], int burst_time[], int process_count)
{
    cout << Red << "\t\t\t***********************************\n";
    cout << Red << "\t\t\t*  Shortest Remaining Time First  *\n";
    cout << Red << "\t\t\t***********************************\n\n";

    cout <<Green0<<">"<<Green1<<" It schedules the process with the least remaining burst time.\n";
    cout <<Green0<<">"<<Green1<<" It is preemptive version of Shortest Job First Scheduling.\n";
    cout <<Green0<<">"<<Green1<<" It minimizes the average waiting time.\n";

    vector<Process> processes(process_count);
    for(int i=0;i<process_count;i++)
    {
        processes[i]={i+1, arrival_time[i], burst_time[i]};
    }

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

    cout << Green0 << ">" << Magenta << " Process Execution Details:\n";
    cout << Green0 << ">" << Magenta << " --------------------------\n"<<Blue;
    
    
    while (process_completed != process_count) {
        int min_time = INT_MAX;
        int shortest_burst_process = -1;

        for (int i = 0; i < process_count; ++i) {
            if (processes[i].arr_time <= current_time && temp_burst_time[i] < min_time && temp_burst_time[i] > 0) {
                min_time = temp_burst_time[i];
                shortest_burst_process = i;
            }
        }

        if (shortest_burst_process == -1) {
            //cpu idle time
            cout << Green0 << ">" << Blue << " CPU is idle at time " << current_time << "\n";
            current_time++;
            continue;
        }

        if (temp_burst_time[shortest_burst_process] == processes[shortest_burst_process].b_time) {
            start_time[shortest_burst_process] = current_time;
        }

        temp_burst_time[shortest_burst_process]--;
        current_time++;

        if (temp_burst_time[shortest_burst_process] == 0) {
            process_completed++;
            completion_time[shortest_burst_process] = current_time;
            waiting_time[shortest_burst_process] = completion_time[shortest_burst_process] - processes[shortest_burst_process].b_time - processes[shortest_burst_process].arr_time;
            turnaround_time[shortest_burst_process] = completion_time[shortest_burst_process] - processes[shortest_burst_process].arr_time;

            if (waiting_time[shortest_burst_process] < 0) {
                waiting_time[shortest_burst_process] = 0;
            }
        }
    }

    cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";
    cout << "\t\t| " << setw(8) << "Process" << " | " << setw(12) << "Arrival Time" << " | " << setw(10) << "Burst Time" << " | " << setw(11) << "Start Time" << " | " << setw(14) << "Completion" << " | " << setw(14) << "Turnaround" << " | " << setw(12) << "Waiting Time" << " |\n";
    cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";

    for (int i = 0; i < process_count; ++i) {
        cout << "\t\t| " << setw(8) << processes[i].proc_id << " | " << setw(12) << processes[i].arr_time << " | " << setw(10) << processes[i].b_time << " | " << setw(11) << start_time[i] << " | " << setw(14) << completion_time[i] << " | " << setw(14) << turnaround_time[i] << " | " << setw(12) << waiting_time[i] << " |\n";
    }

    cout << "\t\t+----------+--------------+------------+-------------+----------------+-----------------+-------------+\n";

    double avg_waiting_time = 0; double avg_turnaround_time=0;
    for (int i = 0; i < process_count; ++i) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time+=turnaround_time[i];
    }
    avg_waiting_time = avg_waiting_time / process_count;
    avg_turnaround_time= avg_turnaround_time/process_count;


    cout << Green0 << ">" << Blue << " Average waiting time is : " << Magenta << avg_waiting_time << "\n";
    cout << Green0 << ">" << Blue << " Average turnaround time is : " << Magenta << avg_turnaround_time << "\n";
    
}






 








    
    
   
    
    



