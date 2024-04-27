#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "schAlgos.h"

using namespace std;

int findShortJob(vector<Process> processes, int currentTime){
    int min_burstTime = -1;
    int min_index = -1;

    for (int i = 0; i < processes.size()-1; i++){
        if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0){
            if (min_burstTime == -1 || processes[i].burstTime < min_burstTime){
                min_burstTime = processes[i].burstTime;
                min_index = i;
            }
        }
    }
    return min_index;
}

int findprocPri(vector<Process> processes, int currentTime){
    int min_burstTime = -1;
    int min_index = -1;

    for(int i = 0; i <processes.size()-1; i++){
        if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0){
            if(min_burstTime == -1 || processes[i].procPri < min_burstTime){
                min_burstTime = processes[i].procPri;
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
        out << "CPU: Loading process " << proc[currentProcess].pid << " (CPU burstTime = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if (proc[currentProcess].startTime <= currentTime && proc[currentProcess].burstTime > 0){
        out << "CPU: Running process " << proc[currentProcess].pid << " (remaining CPU burstTime = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if (proc[currentProcess].burstTime == 0 && findShortJob(proc, currentTime) == -1) {
        out << "CPU: Finishing process " << proc[currentProcess].pid << endl;
    } 

    else if (proc[currentProcess].burstTime == 0) {
        out << "CPU: Finishing process " << proc[currentProcess].pid << "; loading process " << proc[findShortJob(proc, currentTime)].pid << " (CPU burstTime = " << proc[findShortJob(proc, currentTime)].burstTime << ")" << endl;
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

void printNPP(vector<Process> proc, string s2, int currentTime, int currentProcess){
    ofstream out;

    out.open(s2, ios_base::app);

    vector<Process> readyProc;
    int y = 0;

    int empty = 0;

    out << endl;

    out << "t = " << currentTime << endl;

    if(proc[currentProcess].arrivalTime == currentTime){
        out << "CPU: Loading process " << proc[currentProcess].pid << " (CPU burstTime = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if(proc[currentProcess].startTime <= currentTime && proc[currentProcess].burstTime > 0){
        out << "CPU: Running process " << proc[currentProcess].pid << " (remaining CPU burstTime = " << proc[currentProcess].burstTime << ")" << endl;
    }

    else if(proc[currentProcess].burstTime == 0 && findprocPri(proc, currentTime) == -1){
        out << "CPU: Finishing process " << proc[currentProcess].pid << endl;
    }

    else if(proc[currentProcess].burstTime == 0){
        out << "CPU: Finishing process " << proc[currentProcess].pid << "; loading process " << proc[findprocPri(proc, currentTime)].pid << " (CPU burstTime = " << proc[findprocPri(proc, currentTime)].burstTime << ")" << endl;
    }

    out << "ready queue: ";

    int finished = 0;

    for (int x = 0; x < proc.size() - 1; x++) {

        if (proc[x].arrivalTime <= currentTime && proc[x].burstTime > 0 && proc[x].startTime == -1) {

            if(proc[findprocPri(proc, currentTime - 1)].burstTime > 0 && findprocPri(proc, currentTime - 1) != currentProcess && proc[findprocPri(proc, currentTime - 1)].burstTime && finished == 0){

                readyProc.push_back(proc[findprocPri(proc, currentTime - 1)]);
                finished = 1;

            }

            if(proc[x].pid != proc[findprocPri(proc, currentTime - 1)].pid){

                readyProc.push_back(proc[x]);

            }

        }

    }

    for (int w = 0; w < readyProc.size(); w++){
 
        for (int j = 0; j < readyProc.size() - 1; j++){

            if (readyProc[j].procPri > readyProc[j + 1].procPri){

                swap(readyProc[j], readyProc[j + 1]);

            }

        }
    }
    if (currentTime == 0) {
        for (int i = 1; i < readyProc.size(); i++) {

            out << readyProc[i].pid;

            empty = 1; // Set the empty flag to indicate that the ready queue is not empty

            // Add a separator between process pids in the ready queue
            if (i < readyProc.size() - 1) {

                out << "-";

            }

        }
    }
    else if (currentTime > 0) {
        for (int i = 0; i < readyProc.size(); i++) {

            out << readyProc[i].pid;

            empty = 1; // Set the empty flag to indicate that the ready queue is not empty

            // Add a separator between process pids in the ready queue
            if (i < readyProc.size() - 1) {

                out << "-";

            }

        }
    }
    // If the empty flag is not set, the ready queue is empty
    if (empty == 0) {

        out << "empty";

    }

    out << endl;
    out.close(); // Close the output file

}

void printFCFS(vector<Process> proc, string s2, int currentTime, int curProc){

    ofstream out;
    
    out.open(s2, ios_base::app);

    int empty = 0;

    out << endl;

    out << "t = " << currentTime << endl;

    if (proc[curProc].arrivalTime == currentTime) {

        out << "CPU: Loading process " << proc[curProc].pid << " (CPU burst = " << proc[curProc].burstTime << ")" << endl;

    }
    
    else if (proc[curProc].startTime <= currentTime && proc[curProc].burstTime > 0) {

        out << "CPU: Running process " << proc[curProc].pid << " (remaining CPU burst = " << proc[curProc].burstTime << ")" << endl;

    } 
    
    else if (proc[curProc].burstTime == 0 && curProc + 1 > proc.size() - 2) {
    
        out << "CPU: Finishing process " << proc[curProc].pid << endl;

    } 
    
    else if (proc[curProc].burstTime == 0) {
    
        out << "CPU: Finishing process " << proc[curProc].pid << "; loading process " << proc[curProc + 1].pid << " (CPU burst = " << proc[curProc + 1].burstTime << ")" << endl;

    }

    
    out << "Ready queue: ";

    for (int i = 0; i < proc.size() - 1; i++) {

        
        if(proc[i].arrivalTime <= currentTime && proc[i].burstTime > 0 && proc[i].startTime == -1){

            out << proc[i].pid;

            empty = 1; 

            
            if (i < proc.size() - 2 && proc[i + 1].arrivalTime <= currentTime) {

                out << "-";

            }

        }

    }

    
    if (empty == 0) {

        out << "empty";

    }

    out << endl;
    out.close();

}