#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <semaphore.h>
#include "tFunctions.h"

using namespace std;

//Globals (mirrored from tFunctions.cpp)
extern string mainMemory[10000];
extern vector<FrameData> freeFrames;
extern vector<FrameData> frameTable;
extern vector<PageTable> pageTable;
extern vector<PageTable> pageTable2;
extern vector<PageTable> pageTable3;
extern vector<PageTable> pageTable4;
extern sem_t semaphore;

int main (int argc, char *argv[]){
    string inputFile, outputFile;
    int rngSeed = 0;
    int pageSize = 0;
    int memorySize = 0;
    int threadCount = 0;
    string threadFile1;
    string threadFile2;
    string threadFile3;
    sem_init(&semaphore, 0, 1);

    inputFile = argv[1];
    outputFile = argv[2];
    rngSeed = atoi(argv[3]);

    srand(rngSeed);

    ifstream in(inputFile);
    ofstream out;
    out.open(outputFile, ios_base::app);

    in >> memorySize;
    in >> pageSize;
    in >> threadCount;
    in >> threadFile1;

    if(threadCount == 2 || threadCount == 3){
        in >> threadFile2;
    }

    if(threadCount == 3){
        in >> threadFile3;
    }

    for(int i = 0; i < memorySize; i++){
        string str = to_string(rand() % 4811);
        mainMemory[i] = str;

        if(i % pageSize == 0 || i == 0){
            FrameData frame;
            frame.frameNumber = i /pageSize;
            frame.physicalAddress = i;
            freeFrames.push_back(frame);
        }
    }

    frameTable = freeFrames;

    thread thread1(processThread, pageSize, 0, threadFile1, outputFile);
    thread thread2;
    thread thread3;

    if(threadCount == 2 || threadCount == 3){
        thread2 = thread(processThread2, pageSize, 1, threadFile2, outputFile);
    }

    if(threadCount == 3){
        thread3 = thread(processThread3, pageSize, 2, threadFile3, outputFile);
    }

    thread1.join();

    if(threadCount == 2 || threadCount == 3){
        thread2.join();
    }

    if(threadCount == 3){
        thread3.join();
    }

    out << "Main: progarm complete" << endl;

    in.close();
    out.close();
    
    return 0;
}