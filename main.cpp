#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "scheduling_algo.h"
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {

    const string Green0 = "\033[1;32m";
    const string RESET = "\033[0m";
    const string Yellow= "\033[1;33m";
    const string Red= "\033[1;31m";
    const string Blue = "\033[36m";
    const string Magenta = "\033[35m";
    const string Green1="\033[92m";


    cout <<Red<< "\t\t\t***********************************\n";
    cout <<Red<< "\t\t\t*      CPU Scheduler Simulator    *\n";
    cout <<Red<< "\t\t\t***********************************\n\n";

    if (argc == 1) {
        cout << "Usage: CPU_Scheduler [Process Count]\n";
    } else {

        int Process_count = stoi(argv[1]); 
        cout << Green0 << ">"<<Yellow<<" Number of processes to schedule: " <<Blue<<Process_count << endl;
        cout << Green0 << ">"<<Yellow<<" Enter Arrival Time and Burst Time for each Process\n";
       
        int Arrival_time[Process_count],Burst_time[Process_count];

        for(int i=1;i<=Process_count;i++)
        {
          cout<<Green0<< ">"<<Blue<<" Process "<<i<<"\n";
          cout<<Magenta<<"\t Arrival Time: ";
          cin>>Arrival_time[i-1];
          cout<<Magenta<<"\t Burst Time: ";
          cin>>Burst_time[i-1];
        }

        cout<<Green0<<">"<<Yellow<<" Select Scheduling Algorithm \n";
        cout<<Green1<<"\t 1. First Come First Served (FCFS)\n";
        cout<<Green1<<"\t 2. Shortest Job First (SJF)\n";
        cout<<Green1<<"\t 3. Round Robin (RR)\n";
        cout<<Green1<<"\t 4. Priority Algorithm\n";
        cout<<Green1<<"\t 5. Multilevel Queue Scheduling\n";
 
        int algo_choice;
        cout<<Green0<<">"<<Yellow<<" Enter the choice: "<<Blue;
        cin>>algo_choice;

        if(algo_choice==1)
        {
            fcfs(Arrival_time,Burst_time,Process_count);
        }

        if(algo_choice==2)
        {
            sjf(Arrival_time,Burst_time,Process_count);
        }

        if(algo_choice==3)
        {
           rr(Arrival_time,Burst_time,Process_count);
        }

        if(algo_choice==4)
        {
            priority(Arrival_time,Burst_time,Process_count);
        }

        if(algo_choice==5)
        {
            multi_queue(Arrival_time,Burst_time, Process_count);
        }

   }

    return 0;
}
