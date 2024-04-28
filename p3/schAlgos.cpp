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

int findPriority(vector<Process> processes, int currentTime){
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

    else if(proc[currentProcess].burstTime == 0 && findPriority(proc, currentTime) == -1){
        out << "CPU: Finishing process " << proc[currentProcess].pid << endl;
    }

    else if(proc[currentProcess].burstTime == 0){
        out << "CPU: Finishing process " << proc[currentProcess].pid << "; loading process " << proc[findPriority(proc, currentTime)].pid << " (CPU burstTime = " << proc[findPriority(proc, currentTime)].burstTime << ")" << endl;
    }

    out << "ready queue: ";

    int finished = 0;

    for (int x = 0; x < proc.size() - 1; x++) {

        if (proc[x].arrivalTime <= currentTime && proc[x].burstTime > 0 && proc[x].startTime == -1) {

            if(proc[findPriority(proc, currentTime - 1)].burstTime > 0 && findPriority(proc, currentTime - 1) != currentProcess && proc[findPriority(proc, currentTime - 1)].burstTime && finished == 0){

                readyProc.push_back(proc[findPriority(proc, currentTime - 1)]);
                finished = 1;

            }

            if(proc[x].pid != proc[findPriority(proc, currentTime - 1)].pid){

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

                // Print scheduler metrice if the current time is a multiple of the interval
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

            // Print scheduler metrice if the current time is a multiple of the interval
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

algorithmMetrics roundRobin(vector<Process> processes, string s1, int numProcess, int interv, int quantum){

    int tempId;
    ofstream out;
    out.open(s1, ios_base::app);
    algorithmMetrics metric;
    int currentTime = 0;
    bool isProcessRunning = false;
    Process currentRunningProccess;
    int qCounter = 0;
    float numProcessFloat = numProcess;
    int numFinishedProcesses = 0;
    int contextSw = 0;
    string procSeq = "";
    queue<Process> readyQueue;

    out << endl;
    out << "*** RoundRobin Scheduling ***" << endl;

    while (numFinishedProcesses < numProcess) {

        
        if (currentTime % interv == 0 || currentTime % interv == interv){
            out << endl;
            out << "t = " << currentTime << endl;
        }
        for (int i = 0; i < numProcess; i++) {

            if (processes[i].arrivalTime <= currentTime && processes[i].hasRun == 0) {

                readyQueue.push(processes[i]);
                processes[i].hasRun = 1;

            }
        
        }

        if (isProcessRunning == false) {
            if (currentTime % interv == 0 || currentTime % interv == interv){
                out << "CPU: Loading process " << readyQueue.front().pid << " (CPU burst = " << readyQueue.front().burstTime << ")" << endl;
            }
            currentRunningProccess = readyQueue.front();
            if (processes[currentRunningProccess.pid].startTime == -1) { // If the process hasn't started yet

                processes[currentRunningProccess.pid].startTime = currentTime; // Set the start time

            }
            tempId = currentRunningProccess.pid;
            procSeq += to_string(tempId) + "-";
            contextSw++;
            if (currentTime % interv == 0 || currentTime % interv == interv){
                out << "Ready Queue: ";
                //Cycling through the queue to print out the ready queue
                queue<Process> tempQueue = readyQueue; // Create a temporary queue
                while (!tempQueue.empty()) { // Loop through the temporary queue until it's empty
                    out << tempQueue.front().pid;
                    tempQueue.pop();
                    if (!tempQueue.empty()) { // Only print the dash if there is another process after the current one
                        out << "-";
                    }
                }
                out << endl;
            }
            readyQueue.pop();
            isProcessRunning = true;
            
            currentRunningProccess.burstTime--;
        }
        
        else if (currentRunningProccess.burstTime == 0) {
            if (currentTime % interv == 0 || currentTime % interv == interv){
                out << "CPU: Finishing process " << currentRunningProccess.pid << "; loading process " << readyQueue.front().pid << " (CPU burst = " << readyQueue.front().burstTime << ")" << endl;
                out << "Ready Queue: ";
                queue<Process> tempQueue = readyQueue; // Create a temporary queue
                while (!tempQueue.empty()) { // Loop through the temporary queue until it's empty
                    out << tempQueue.front().pid;
                    tempQueue.pop();
                    if (!tempQueue.empty()) { // Only print the dash if there is another process after the current one
                        out << "-";
                    }
                }
                out << endl;
            }
            processes[currentRunningProccess.pid].turnaroundTime = currentTime - processes[currentRunningProccess.pid].arrivalTime;
            processes[currentRunningProccess.pid].waitTime = processes[currentRunningProccess.pid].turnaroundTime - processes[currentRunningProccess.pid].burstTime;
                
            if (!readyQueue.empty()) {
                
                currentRunningProccess = readyQueue.front();
                if (processes[currentRunningProccess.pid].startTime == -1) { // If the process hasn't started yet

                processes[currentRunningProccess.pid].startTime = currentTime; // Set the start time

                }
                readyQueue.pop();
                tempId = currentRunningProccess.pid;
                procSeq += to_string(tempId) + "-";
                contextSw++;
            }
            else {
                if (currentTime % interv == 0 || currentTime % interv == interv){
                    out << "empty";
                    out << endl;
                }
            }
            
            currentRunningProccess.burstTime--;
            numFinishedProcesses++;
            qCounter = 0;
        }

        else if (qCounter == quantum && !readyQueue.empty()) {
            if (currentTime % interv == 0 || currentTime % interv == interv){
                out << "CPU: Preempting process " << currentRunningProccess.pid << " (remaining CPU burst = " << currentRunningProccess.burstTime << ")" << "; loading process " << readyQueue.front().pid << " (CPU burst = " << readyQueue.front().burstTime << ")" << endl;
            
            
            
                out << "Ready Queue: ";
                queue<Process> tempQueue = readyQueue; // Create a temporary queue
                while (!tempQueue.empty()) { // Loop through the temporary queue until it's empty
                    out << tempQueue.front().pid;
                    tempQueue.pop();
                    if (!tempQueue.empty()) { // Only print the dash if there is another process after the current one
                        out << "-";
                    }
                }
                out << endl;
            }
            readyQueue.push(currentRunningProccess);
            currentRunningProccess = readyQueue.front();
            if (processes[currentRunningProccess.pid].startTime == -1) { // If the process hasn't started yet

                processes[currentRunningProccess.pid].startTime = currentTime; // Set the start time

            }
            tempId = currentRunningProccess.pid;
            procSeq += to_string(tempId) + "-";
            contextSw++;
            readyQueue.pop();
            currentRunningProccess.burstTime--;
            qCounter = 0;

        }

        else if (currentRunningProccess.burstTime != 0) {
            if (currentTime % interv == 0 || currentTime % interv == interv){
                out << "CPU: Running process " << currentRunningProccess.pid << " (remaining CPU burst = " << currentRunningProccess.burstTime << ")" << endl;
                out << "Ready Queue: ";
                queue<Process> tempQueue = readyQueue; // Create a temporary queue
                while (!tempQueue.empty()) { // Loop through the temporary queue until it's empty
                    out << tempQueue.front().pid;
                    tempQueue.pop();
                    if (!tempQueue.empty()) { // Only print the dash if there is another process after the current one
                        out << "-";
                    }
                }
                out << endl;
            }
                if (readyQueue.empty()) {
                    if (qCounter == quantum) {
                        qCounter = qCounter - 1;
                    }
                    if (currentTime % interv == 0 || currentTime % interv == interv){
                        out << "empty";
                    }
                }
                
            
            currentRunningProccess.burstTime--;
        }

        qCounter++;
        currentTime++;
        

            
    }
    procSeq.pop_back(); // Remove the last hyphen    
    
    out << endl;
    out << "*********************************************************" << endl;
    out << "Round robin Summary (WT = wait time, TT = turnaround time):" << endl;
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

    
    metric.contextSwitches = contextSw;
    out << "Process sequence: " << procSeq << endl;
    out << "Context switches: " << contextSw << endl;

    out << endl;
    out << endl;
    out.close(); // Close the output file

    return metric; // Return the average algorithMetric object
}

algorithmMetrics stcf(vector<Process> processes, string s1, int numProcess, int interv){
    ofstream out;
    out.open(s1, ios_base::app);
    algorithmMetrics metric;
    int currentTime = 0;
    int numFinishedProcesses = 0;
    int currentProcess = findShortJob(processes, currentTime);
    int tempId;
    string procSeq = "";
    int contextSw = 0;
    float numProcessFloat = numProcess;
    vector<Process> processCopy = processes;

    out << endl;
    out << "*** STCF Scheduling ***" << endl;
    printSJF(processes, s1, currentTime, currentProcess);

     while(numFinishedProcesses < numProcess) {

        if (currentProcess != findShortJob(processes, currentTime)) {
            tempId = processes[currentProcess].pid;
            procSeq += to_string(tempId) + "-";
            contextSw++;
        }
        currentProcess = findShortJob(processes, currentTime);

        if (currentProcess != -1) { // If there's a valid process to run

            if (processes[currentProcess].startTime == -1) { // If the process hasn't started yet

                processes[currentProcess].startTime = currentTime; // Set the start time
                processes[currentProcess].hasRun = 1; // Mark the process as started

            }

            processes[currentProcess].burstTime--;
            currentTime++;

            if (processes[currentProcess].burstTime == 0) {
            
                processes[currentProcess].turnaroundTime = currentTime - processes[currentProcess].arrivalTime;
                processes[currentProcess].waitTime = processes[currentProcess].turnaroundTime - processCopy[currentProcess].burstTime;
                numFinishedProcesses++;
                

            }

            if (currentTime % interv == 0 || currentTime % interv == interv) {

                printSJF(processes, s1, currentTime, currentProcess);

            }

        } 
        
        else {

            currentTime++;

            if (currentTime % interv == 0) {

                printSJF(processes, s1, currentTime, currentProcess);
                
            }
        }
    }
    tempId = processes[currentProcess].pid;
    procSeq += to_string(tempId) + "-";
    contextSw++;
    procSeq.pop_back(); // Remove the last hyphen
    metric.contextSwitches = contextSw;

    out << endl;
    out << "*********************************************************" << endl;
    out << "STCF Summary (WT = wait time, TT = turnaround time):" << endl;
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

    
    metric.contextSwitches = contextSw;

    out << endl;
    out << endl;
    out << "Process sequence: " << procSeq << endl;
    out << "Context Switches: " << contextSw << endl;
    out.close(); // Close the output file

    return metric; // Return the average algorithmMetric object

}

algorithmMetrics NPP(vector<Process> processes, string s1, int numProcess, int interv){
    
    ofstream out;
    int tempId;

    out.open(s1, ios_base::app);

    algorithmMetrics metric;
    int currentTime = 0;
    int numFinishedProcesses = 0;
    int currentProcess = findPriority(processes, currentTime);
    string procSeq;
    int contextSw;
    float numProcessFloat = numProcess;

    out << endl;

    out << "*** Priority Scheduling ***" << endl;

    printNPP(processes, s1, currentTime, currentProcess);

    while(numFinishedProcesses < numProcess){
        currentProcess = findPriority(processes, currentTime);

        if(currentProcess != -1){
            processes[currentProcess].startTime = currentTime;
            processes[currentProcess].waitTime = currentTime - processes[currentProcess].arrivalTime;
            processes[currentProcess].turnaroundTime = processes[currentProcess].waitTime + processes[currentProcess].burstTime;

            while(processes[currentProcess].burstTime > 0){
                processes[currentProcess].burstTime--;
                currentTime++;

                if(currentTime % interv == 0 || currentTime % interv == interv){
                    printNPP(processes, s1, currentTime, currentProcess);
                }
            }

            numFinishedProcesses++;
            tempId = processes[currentProcess].pid;
            procSeq += to_string(tempId) + "-";
            contextSw++;
        }

        else{
            currentTime++;

            if(currentTime % interv == 0){
                printNPP(processes, s1, currentTime, currentProcess);
            }
        }
    }

    procSeq.pop_back();
    metric.contextSwitches = contextSw;

    out << endl;
    out << "*********************************************************" << endl;
    out << "Priority Summary (WT = wait time, TT = turnaround time):" << endl;
    out << "PID     WT     TT" << endl;

    for(int i = 0; i < numProcess; i++){
        if(processes[i].waitTime < 10){
            out << " " << processes[i].pid << "      " << processes[i].waitTime << "      " << processes[i].turnaroundTime << endl;
        }

        if(processes[i].waitTime >= 10 && processes[i].waitTime < 100){
            out << " " << processes[i].pid << "      " << processes[i].waitTime << "      " << processes[i].turnaroundTime << endl;
        }

        if(processes[i].waitTime >= 100){
            out << " " << processes[i].pid << "      " << processes[i].waitTime << "      " << processes[i].turnaroundTime << endl;
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
    out << "Context switches: " << contextSw << endl;
    out.close();

    return metric;
}

algorithmMetrics fcfs(vector<Process> processes, string s1, int numProcess, int interv){

    ofstream out;
    out.open(s1, ios_base::app);

    algorithmMetrics metric;
    int currentTime = 0;
    int i = 0;
    int currentProcess = 0;
    float numProcessFloat = numProcess;
    string procSeq = "";
    int tempId = 0;
    int contextSw = 0;

    out << "*** FCFS Scheduling ***" << endl;

    while(i < numProcess){

        if(processes[currentProcess].arrivalTime <= currentTime){

            if(processes[currentProcess].arrivalTime == currentTime){

                if((currentTime % interv == 0) || (currentTime & interv == interv)){
                    printFCFS;
                }

                currentTime++;

            }

            while(processes[currentProcess].burstTime > 0){

                if(processes[currentProcess].startTime == -1){
                    processes[currentProcess].startTime = currentTime;
                    processes[currentProcess].waitTime = currentTime - processes[currentProcess].arrivalTime;
                    processes[currentProcess].turnaroundTime = processes[currentProcess].waitTime + processes[currentProcess].burstTime;
                }

                processes[currentProcess].burstTime = processes[currentProcess].burstTime - 1;

                if((currentTime % interv == 0) || (currentTime % interv == interv)){
                    printFCFS(processes, s1, currentTime, currentProcess);
                }

                currentTime++;
            }

            tempId = processes[currentProcess].pid;
            procSeq = procSeq + to_string(tempId) + "-";
            contextSw++;
            currentProcess++;
        }

        i++;
    }

    out << endl;
    out << "*********************************************************" << endl;
    out << "FCFS Summary (WT = Wait time, TT = turnaround time):" << endl;
    out << "PID     WT     TT" << endl;

    for(i = 0; i < numProcess; i++){
        if(processes[i].waitTime - 1  < 10){
            out << " " << processes[i].pid << "      " << processes[i].waitTime - 1 << "      " << processes[i].turnaroundTime - 1 << endl;
        }
        if(processes[i].waitTime - 1 >= 10){
            out << " " << processes[i].pid << "      " << processes[i].waitTime - 1 << "      " << processes[i].turnaroundTime - 1 << endl;
        }
    }

    for(int x = 0; x < numProcess; x++){
        metric.avWait = metric.avWait + processes[x].waitTime - 1;
        metric.avTurnaround = metric.avTurnaround + processes[x].turnaroundTime - 1;
    }

    metric.avWait = metric.avWait / numProcessFloat;
    metric.avTurnaround = metric.avTurnaround / numProcessFloat;

    out << "AVG" << "      " << metric.avWait << "   " << metric.avTurnaround << endl;

    out << endl;
    out << endl;
    metric.contextSwitches = contextSw;
    procSeq.pop_back();
    out << "Process sequence: " << procSeq << endl;
    out << "Context switches: " << contextSw << endl;

    out.close();

    return metric;
}