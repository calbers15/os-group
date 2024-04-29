#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "schAlgos.h"

using namespace std;

int main(int argc, char *argv[]){
    
    string s, ss;
    vector<Process> proc;
    int id = 0;
    int interv;
    algorithmMetrics stcfMetric;
    algorithmMetrics roundRobinMetric;
    algorithmMetrics priorityMetric;
    algorithmMetrics fcfsMetric;
    algorithmMetrics sjfMetric;
    vector<algorithmMetrics> metrics;
    vector<algorithmMetrics> metrics2;
    int metricsSize = 0;
    
    
    s = argv[1];
    ss = argv[2];
    interv = atoi(argv[3]);

    ifstream in(s);
    ofstream out;

    out.open(ss, ios_base::app);

    while(!in.eof()){
        
        Process p;

        in >> p.burstTime;
        in >> p.procPri;
        in >> p.arrivalTime;
        p.pid = id;
        id = id + 1;

        proc.push_back(p);
    }

    in.close();
    int n = proc.size() - 1;

    fcfsMetric = fcfs(proc, ss, n, interv);
    sjfMetric = sjf(proc, ss, n, interv);
    stcfMetric = stcf(proc, ss, n, interv);
    roundRobinMetric = roundRobin(proc, ss, n, interv, 2);
    priorityMetric = priority(proc, ss, n, interv);

    metrics.push_back(stcfMetric);
    metrics.push_back(sjfMetric);
    metrics.push_back(roundRobinMetric);
    metrics.push_back(priorityMetric);
    metrics.push_back(fcfsMetric);

    metrics2 = metrics;

    out << endl;
    out << endl;

    out << "*** OVERALL SUMMARY ***" << endl;

    out << endl;

    sort(metrics.begin(), metrics.end(), WTComp);

    out << "Wait time comparison" << endl;

    metricsSize = metrics.size();

    for(int i = 0; i < metricsSize; i++){
        if(stcfMetric.avWait == metrics[0].avWait && stcfMetric.avTurnaround == metrics[0].avTurnaround && stcfMetric.contextSwitches == metrics[0].contextSwitches) {
            out << i+1 << " STCF         " << stcfMetric.avWait << endl;
        }

        if(sjfMetric.avWait == metrics[0].avWait && sjfMetric.avTurnaround == metrics[0].avTurnaround && sjfMetric.contextSwitches == metrics[0].contextSwitches) {
            out << i+1 << " SJF          " << sjfMetric.avWait << endl;
        }

        if(roundRobinMetric.avWait == metrics[0].avWait && roundRobinMetric.avTurnaround == metrics[0].avTurnaround && roundRobinMetric.contextSwitches == metrics[0].contextSwitches) {
            out << i+1 << " Round robin  " << roundRobinMetric.avWait << endl;
        }

        if(priorityMetric.avWait == metrics[0].avWait && priorityMetric.avTurnaround == metrics[0].avTurnaround && priorityMetric.contextSwitches == metrics[0].contextSwitches) {
            out << i+1 << " Priority     " << priorityMetric.avWait << endl;
        }

        if(fcfsMetric.avWait == metrics[0].avWait && fcfsMetric.avTurnaround == metrics[0].avTurnaround && fcfsMetric.contextSwitches == metrics[0].contextSwitches) {
            out << i+1 << " FCFS         " << fcfsMetric.avWait << endl;
        }
        metrics.erase(metrics.begin());
    }
    
    out << endl;

    metrics = metrics2;

    sort(metrics.begin(), metrics.end(), TTComp);

    out << "Turnaround Time Comparison" << endl;

    metricsSize = metrics.size();

    for(int i = 0; i < metricsSize; i++){
        if(stcfMetric.avTurnaround == metrics[0].avTurnaround && stcfMetric.avWait == metrics[0].avWait && stcfMetric.contextSwitches == metrics[0].contextSwitches) {

            out << i+1 << " STCF         " << stcfMetric.avTurnaround << endl;

        }

        if(sjfMetric.avTurnaround == metrics[0].avTurnaround && sjfMetric.avWait == metrics[0].avWait && sjfMetric.contextSwitches == metrics[0].contextSwitches) {

            out << i+1 << " SJF          " << sjfMetric.avTurnaround << endl;

        }

        if(roundRobinMetric.avTurnaround == metrics[0].avTurnaround && roundRobinMetric.avWait == metrics[0].avWait && roundRobinMetric.contextSwitches == metrics[0].contextSwitches) {

            out << i+1 << " Round robin  " << roundRobinMetric.avTurnaround << endl;

        }

        if(priorityMetric.avTurnaround == metrics[0].avTurnaround && priorityMetric.avWait == metrics[0].avWait && priorityMetric.contextSwitches == metrics[0].contextSwitches) {

            out << i+1 << " Priority     " << priorityMetric.avTurnaround << endl;

        }

        if(fcfsMetric.avTurnaround == metrics[0].avTurnaround && fcfsMetric.avWait == metrics[0].avWait && fcfsMetric.contextSwitches == metrics[0].contextSwitches) {

            out << i+1 << " FCFS         " << fcfsMetric.avTurnaround << endl;

        }

        metrics.erase(metrics.begin());        
    }

    out << endl;

    metrics = metrics2;

    sort(metrics.begin(), metrics.end(), CSComp);

    out << "Context Switch Comparison" << endl;

    metricsSize = metrics.size();

    for(int i = 0; i < 5; i++){
        if(stcfMetric.contextSwitches == metrics[0].contextSwitches && stcfMetric.avWait == metrics[0].avWait && stcfMetric.avTurnaround == metrics[0].avTurnaround) {

            out << i+1 << " STCF         " << stcfMetric.contextSwitches << endl;

        }

        if(sjfMetric.contextSwitches == metrics[0].contextSwitches && sjfMetric.avWait == metrics[0].avWait && sjfMetric.avTurnaround == metrics[0].avTurnaround) {

            out << i+1 << " SJF          " << sjfMetric.contextSwitches << endl;

        }

        if(roundRobinMetric.contextSwitches == metrics[0].contextSwitches && roundRobinMetric.avWait == metrics[0].avWait && roundRobinMetric.avTurnaround == metrics[0].avTurnaround) {

            out << i+1 << " Round robin  " << roundRobinMetric.contextSwitches << endl;

        }

        if(priorityMetric.contextSwitches == metrics[0].contextSwitches && priorityMetric.avWait == metrics[0].avWait && priorityMetric.avTurnaround == metrics[0].avTurnaround) {

            out << i+1 << " Priority     " << priorityMetric.contextSwitches << endl;

        }

        if(fcfsMetric.contextSwitches == metrics[0].contextSwitches && fcfsMetric.avWait == metrics[0].avWait && fcfsMetric.avTurnaround == metrics[0].avTurnaround) {

            out << i+1 << " FCFS         " << fcfsMetric.contextSwitches << endl;

        }

        metrics.erase(metrics.begin());
    }

    out.close();
    
    return 0;
}