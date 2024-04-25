#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "schAlgos.h"

using namespace std;

int findShortJob(vector<Process> processes, int currentTime){
    int min_burst = -1;
    int min_index = -1;

    for (int i = 0; i < processes.size()-1; i++){
        if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0){
            if (min_burst == -1 || processes[i].burstTime < min_burst){
                min_burst = processes[i].burstTime;
                min_index = i;
            }
        }
    }
    return min_index;
}

int findPriority(vector<Process> processes, int currentTime){
    int min_burst = -1;
    int min_index = -1;

    for(int i = 0; i <processes.size()-1; i++){
        if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0){
            if(min_burst == -1 || processes[i].procPri < min_burst){
                min_burst = processes[i].procPri;
                min_index = i;
            }
        }
    }

    return min_index;
}

void printSJF(vector<Process> proc, string s2, int currentTime, int currentProcess){
    ofstream out;

    out.open(s2, ios_base::app);

    vector<Process> readyProc;
    int y = 0;

    int empty = 0;

    out << endl;

    out << "t = " << currentTime << endl;

    if (proc[currentProcess].arrivalTime == currentTime){
        out << "CPU: Loading process " << proc[currentProcess].pid << " (CPU Burst = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if (proc[currentProcess].startTime <= currentTime && proc[currentProcess].burstTime > 0){
        out << "CPU: Running process " << proc[currentProcess].pid << " (remaining CPU Burst = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if (proc[currentProcess].burstTime == 0 && findShortJob(proc, currentTime) == -1) {
        out << "CPU: Finishing process " << proc[currentProcess].pid << endl;
    } 

    else if (proc[currentProcess].burstTime == 0) {
        out << "CPU: Finishing process " << proc[currentProcess].pid << "; loading process " << proc[findShortJob(proc, currentTime)].pid << " (CPU burst = " << proc[findShortJob(proc, currentTime)].burstTime << ")" << endl;
    }

    out << "Ready queue: ";

    int finished = 0;

    for (int x = 0; x < proc.size() - 1; x++){
        if (proc[x].arrivalTime <= currentTime && proc[x].burstTime > 0 && proc[x].startTime == -1){
            if(proc[findShortJob(proc, currentTime -1)].burstTime > 0 && findShortJob(proc, currentTime -1) != currentProcess && proc[findShortJob(proc, currentTime - 1)].burstTime && finished == 0){

                readyProc.push_back(proc[findShortJob(proc, currentTime -1)]);
                finished = 1;
            }

            if(proc[x].pid != proc[findShortJob(proc, currentTime - 1)].pid){
                readyProc.push_back(proc[x]);
            }
        }
    }

    for (int n = 0; n < readyProc.size(); n++){
        for(int j = 0; j <readyProc.size() - 1; j++){
            if(readyProc[j].burstTime > readyProc[j + 1].burstTime){
                swap(readyProc[j], readyProc[j + 1]);
            }
        }
    }

    for (int i = 0; i < readyProc.size(); i++){
        out << readyProc[i].pid;

        empty = 1;

        if(i < readyProc.size() - 1){
            out << "-";
        }
    }

    if(empty == 0){
        out << "empty";
    }

    out << endl;
    out.close();
}
