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

