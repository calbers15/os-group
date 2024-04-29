/*Cameron Albers, Austin Silva
  EECE.4811 - Operating Systems
  Michael Geiger, Yongshun Xu
  Project 4 - Memory Management Simulator*/

#ifndef TFUNCTIONS_H
#define TFUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <semaphore.h>

using namespace std;

class PageTable{
    public:
        int valid = 0;
        int physicalAddress = 0;
        int pageNumber = 0;
        int frameNumber = 0;
};

class FrameData{
    public:
        int frameNumber = 0;
        int physicalAddress = 0;
};

string intToHexadecimal(int num);

void evict(int threadNumber, string outputFile, int pageSize);

void processThread(int pageSize, int threadNumber, string threadFile, string outFile);

void processThread2(int pageSize, int threadNumber, string threadFile, string outFile);

void processThread3(int pageSize, int threadNumber, string threadFile, string outFile);

void processThread4(int pageSize, int threadNumber, string threadFile, string outFile);

#endif