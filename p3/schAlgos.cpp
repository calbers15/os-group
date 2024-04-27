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

algorithmMetrics sjf(vector<Process> processes, string s1, int numProcess, int interv){
    ofstream out;

    out.open(s1, ios_base::app);

    algorithmMetrics metric;
    int currentTime = 0;
    int finishedProc = 0;
    int currentProc = findShortJob(processes, currentTime);
    int tempId;
    string procSeq = "";
    int contextSw = 0;
    float numProcessFloat = numProcess;

    out << endl;

    out << "*** SJF SCHEDULING ***" << endl;

    printSJF(processes, s1, currentTime, currentProc);

    while(finishedProc < numProcess){

        // Find the index of the process with the shortest job
        currentProc = findShortJob(processes, currentTime);
	    
	//Set start time
	    if(processes[currentProc].startTime = -1){
	
		    processes[currentProc].startTime = currentTime;
	
	    }
	    
        // If a process is found, execute it
        if (currentProc != -1) {
            // calculate the wait time for the process
            processes[currentProc].waitTime = currentTime - processes[currentProc].arrivalTime;
            processes[currentProc].turnaroundTime = processes[currentProc].waitTime + processes[currentProc].burstTime;

            // Iterate through the process burst time and update the current time
            while (processes[currentProc].burstTime > 0) {

		        processes[currentProc].burstTime--;
                currentTime++;

                // Print scheduler state if the current time is a multiple of the interval
                if (currentTime % interv == 0 || currentTime % interv == interv){

                    printSJF(processes, s1, currentTime, currentProc);

                }
                
            }

            // Increment the number of finished processes
            finishedProc++;
            tempId = processes[currentProc].pid;
            procSeq += to_string(tempId) + "-";
            contextSw++;

        } 
        
        else {

            // If no process was found, increment the current time
            currentTime++;

            // Print scheduler state if the current time is a multiple of the interval
            if (currentTime % interv == 0 ){

                printSJF(processes, s1, currentTime, currentProc);

            }
        }
    }
    procSeq.pop_back(); // Remove the last hyphen
    metric.contextSwitches = contextSw;
    out << endl;
    out << "*********************************************************" << endl;
    out << "SJF Summary (WT = wait time, TT = turnaround time):" << endl;
    out << "PID     WT     TT" << endl;

    for(int i = 0; i < numProcess; i++){

        if(processes[i].waitTime < 10){

            out << " " << processes[i].pid << "      " << processes[i].waitTime << "      " << processes[i].turnaroundTime << endl;
        
        }

        if(processes[i].waitTime >= 10 && processes[i].waitTime < 100){

            out << " " << processes[i].pid << "      " << processes[i].waitTime << "     " << processes[i].turnaroundTime << endl;
        
        }
        if (processes[i].waitTime >= 100){

            out << " " << processes[i].pid << "     " << processes[i].waitTime << "     " << processes[i].turnaroundTime << endl;
        
        }

    }

    for(int x = 0; x < numProcess; x++){

        metric.avWait = metric.avWait + processes[x].waitTime;
        metric.avTurnaround = metric.avTurnaround + processes[x].turnaroundTime;

    }
    metric.avWait = metric.avWait / numProcessFloat;
    metric.avTurnaround = metric.avTurnaround / numProcessFloat;

    out << "AVG" << "     " << metric.avWait << "   " << metric.avTurnaround << endl;

    out << "Process sequence: " << procSeq << endl;
    out << "Context Switches: " << contextSw << endl;
    out.close(); // Close the output file
    return metric;
}
