
#ifndef SCHEDULING_ALGO_H
#define SCHEDULING_ALGO_H

void fcfs(int arrival_time[], int burst_time[], int process_count);
void sjf(int arrival_time[], int burst_time[], int process_count);
void rr(int arrival_time[], int burst_time[], int process_count);
void priority(int arrival_time[], int burst_time[], int process_count);
void srtf(int arrival_time[], int burst_time[], int process_count);

#endif
