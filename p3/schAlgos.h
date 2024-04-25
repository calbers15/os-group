#ifndef SCH_ALGOS_H
#define SCH_ALGOS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

//define 
class Process{
public:
    float pid;
    float burstTime;
    float procPri;
    float arrivalTime;
    float startTime = -1;
    float waitTime;
    float turnaroundTime;
    bool hasRun = false;
    bool isComplete = false;
};

//define algorithmMetrics class to keep track of the metrics for each scheudling algorithm
class algorithmMetrics{
public:
    float contextSwitches = 0;
    float avTurnaround = 0;
    float avWait = 0;
};

//function to sort through data and find shortest job
int findShortJob(vector<Process> processes, int currentTime);

//function to sort through data and find priority
int findPriority(vector<Process> processes, int currentTime);

//print first come first serve function
void printFCFS(vector<Process> proc, string s2, int currentTime, int currentProcess);

//print shortest job first function
void printSJF(vector<Process> proc, string s2, int currentTime, int currentProcess);

//print non preemptive prioriry
void printNPP(vector<Process> proc, string s2, int currentTime, int currentProcess);

//priority scheduling function
algorithmMetrics priority(vector<Process> processes, string s1, int numProccess, int interv);

//shortest job first function
algorithmMetrics sjf(vector<Process> processes, string s1, int numProcess, int interv);

//shortest time to completion first function
algorithmMetrics stcf(vector<Process> processes, string s1, int numProcess, int interv);

//round robin function
algorithmMetrics rr(vector<Process> processes, string s1, int numProcess, int interv);

//first come first serve function
algorithmMetrics fcfs(vector<Process> processes, string s1, int numProcess, int interv);

//waiting time comparison
bool WTComp(algorithmMetrics x, algorithmMetrics y);

//turnaround time comparison
bool TTComp(algorithmMetrics x, algorithmMetrics y);

//completion time comparison
bool CSComp(algorithmMetrics x, algorithmMetrics y);

#endif