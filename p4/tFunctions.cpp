/*Cameron Albers, Austin Silva
  EECE.4811 - Operating Systems
  Michael Geiger, Yongshun Xu
  Project 4 - Memory Management Simulator*/

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

//globals:

extern string mainMemory[10000];
extern vector<FrameData> freeFrames;
extern vector<FrameData> frameTable;
extern vector<PageTable> pageTable;
extern vector<PageTable> pageTable2;
extern vector<PageTable> pageTable3;
extern vector<PageTable> pageTable4;
int evictCount = 0;
extern sem_t semaphore;

string intToHexadecimal(int n){         //function from https://www.geeksforgeeks.org/program-decimal-hexadecimal-conversion/#
    string ans = "";

    while(n != 0){
        int rem = 0;    //remainder
        char ch;        //store each character
        rem = n % 16;   //storing remainder in rem


        //check if rem < 10
        if(rem < 10){
            ch = rem + 48;
        }

        else{
            ch = rem + 55;
        }

        ans += ch;
        n = n / 16;
    }

    //reverse ans to get final result
    int i = 0, j = ans.size() - 1;
    while (i <= j){
        swap(ans[i], ans[j]);
        i++;
        j--;
    }
    return ans;
}

void evict(int threadNum, string outFile, int pageSize){
    ofstream out;
    out.open(outFile, ios_base::app);

    int virtualTempAddress = 0;
    int whichTable = 0;

    for(int i = 0; i < pageTable.size(); i++){
        if(pageTable[i].frameNumber == evictCount){
            virtualTempAddress = i / pageSize;
            whichTable = 0;
            break;
        }

        if(!pageTable2.empty()){
            if(pageTable2[i].frameNumber == evictCount){
                virtualTempAddress = i / pageSize;
                whichTable = 1;
                break;
            }
        }

        if(!pageTable3.empty()){
            if(pageTable3[i].frameNumber == evictCount){
                virtualTempAddress = i / pageSize;
                whichTable = 2;
                break;
            }
        }

        if(!pageTable4.empty()){
            if(pageTable4[i].frameNumber == evictCount){
                virtualTempAddress = i /pageSize;
                whichTable = 3;
                break;
            }
        }
    }
    out << "P" << threadNum << ": evicting process " << whichTable << ", page " << virtualTempAddress << " from Frame " << evictCount << endl;

    if(whichTable == 0){
        for(int i = 0; i < pageTable.size(); i++){
            if(pageTable[i].frameNumber == evictCount){
                pageTable[i].valid = 0;
                pageTable[i].physicalAddress = 0;
                pageTable[i].frameNumber = 0;
            }
        }
    }

    if(whichTable == 1){
        for(int i = 0; i < pageTable2.size(); i++){
            if(pageTable2[i].frameNumber == evictCount){
                pageTable2[i].valid = 0;
                pageTable2[i].physicalAddress = 0;
                pageTable2[i].frameNumber = 0;
            }
        }
    }

    if(whichTable == 2){
        for(int i = 0; i < pageTable3.size(); i++){
            if(pageTable3[i].frameNumber == evictCount){
                pageTable3[i].valid = 0;
                pageTable3[i].physicalAddress = 0;
                pageTable3[i].frameNumber = 0;
            }
        }
    }

    if(whichTable == 3){
        for(int i = 0; i < pageTable4.size(); i++){
            if(pageTable4[i].frameNumber == evictCount){
                pageTable4[i].valid = 0;
                pageTable4[i].physicalAddress = 0;
                pageTable4[i].frameNumber = 0;
            }
        }
    }

    freeFrames.push_back(frameTable[evictCount]);

    evictCount++;

    if(evictCount > frameTable.size() - 1){
        evictCount = 0;
    }
}

void processThread(int pageSize, int threadNumber, string threadFile, string outFile){
    //Variable declarations:
    ofstream out;
    out.open(outFile, ios_base::app);
    ifstream in(threadFile);
    char op;
    string regist;
    string registerIndex;
    int virtualAddr;
    int virtualAddrTemp;
    int registers[32];

    //pageTable declaration and population
    PageTable page;
    int tableSize;
    int pages = 0;
    fill(begin(registers), end(registers), 5);

    in >> tableSize;

    sem_wait(&semaphore);
    out << "Process " << threadNumber << " started" << endl;
    sem_post(&semaphore);

    for(int i = 0; i < tableSize; i++){
        if(i % pageSize == 0){
            pages = i / pageSize;
        }

        page.pageNumber = pages;
        pageTable.push_back(page);
    }

    while (in >> op){
        if(op == 'R'){
            in >> regist;
            in >> virtualAddr;
            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);

            if(pageTable[virtualAddr].valid == 1){
                registerIndex = regist.substr(1);
                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page" << pageTable[virtualAddr].pageNumber << " to frame " << pageTable[virtualAddr].frameNumber << endl;
                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << endl;
                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual address 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                sem_post(&semaphore);
            }


            if(pageTable[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable.size(); i++){

                    if(pageTable[i].pageNumber == pageTable[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual addr 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                
                sem_post(&semaphore);

            }

        }

        if(op == 'W'){ // Read operation

            in >> regist; // Read the register from the input file
            in >> virtualAddr; // Read the virtual address from the input file

            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);


            if(pageTable[virtualAddr].valid == 1){
                
                registerIndex = regist.substr(1);

                mainMemory[pageTable[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page " << pageTable[virtualAddr].pageNumber << " to frame " << pageTable[virtualAddr].frameNumber << endl;

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable[virtualAddr].physicalAddress] << " from register " << regist << endl;
                sem_post(&semaphore);

            }


            if(pageTable[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable.size(); i++){

                    if(pageTable[i].pageNumber == pageTable[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                mainMemory[pageTable[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable[virtualAddr].physicalAddress] << " from register " << regist << endl;
                
                sem_post(&semaphore);

            }

        }

    }

    in.close(); // Close the input file
    out.close(); // Close the output file

}

void processThread2(int pageSize, int threadNumber, string threadFile, string outFile){
        //Variable declarations:
    ofstream out;
    out.open(outFile, ios_base::app);
    ifstream in(threadFile);
    char op;
    string regist;
    string registerIndex;
    int virtualAddr;
    int virtualAddrTemp;
    int registers[32];

    //pageTable declaration and population
    PageTable page;
    int tableSize;
    int pages = 0;
    fill(begin(registers), end(registers), 5);

    in >> tableSize;

    sem_wait(&semaphore);
    out << "Process " << threadNumber << " started" << endl;
    sem_post(&semaphore);

    for(int i = 0; i < tableSize; i++){
        if(i % pageSize == 0){
            pages = i / pageSize;
        }

        page.pageNumber = pages;
        pageTable2.push_back(page);
    }

    while (in >> op){
        if(op == 'R'){
            in >> regist;
            in >> virtualAddr;
            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);

            if(pageTable2[virtualAddr].valid == 1){
                registerIndex = regist.substr(1);
                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable2[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page" << pageTable2[virtualAddr].pageNumber << " to frame " << pageTable2[virtualAddr].frameNumber << endl;
                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << endl;
                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual address 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                sem_post(&semaphore);
            }


            if(pageTable2[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable2[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable2[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable2.size(); i++){

                    if(pageTable2[i].pageNumber == pageTable2[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable2[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable2[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable2[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable2[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual addr 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                
                sem_post(&semaphore);

            }

        }

        if(op == 'W'){ // Read operation

            in >> regist; // Read the register from the input file
            in >> virtualAddr; // Read the virtual address from the input file

            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);


            if(pageTable2[virtualAddr].valid == 1){
                
                registerIndex = regist.substr(1);

                mainMemory[pageTable2[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page " << pageTable2[virtualAddr].pageNumber << " to frame " << pageTable2[virtualAddr].frameNumber << endl;

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable2[virtualAddr].physicalAddress] << " from register " << regist << endl;
                sem_post(&semaphore);

            }


            if(pageTable2[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable2[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable2[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable2.size(); i++){

                    if(pageTable2[i].pageNumber == pageTable2[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable2[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable2[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable2[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                mainMemory[pageTable2[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable2[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable2[virtualAddr].physicalAddress] << " from register " << regist << endl;
                
                sem_post(&semaphore);

            }

        }

    }

    in.close(); // Close the input file
    out.close(); // Close the output file

}

void processThread3(int pageSize, int threadNumber, string threadFile, string outFile){
    //Variable declarations:
    ofstream out;
    out.open(outFile, ios_base::app);
    ifstream in(threadFile);
    char op;
    string regist;
    string registerIndex;
    int virtualAddr;
    int virtualAddrTemp;
    int registers[32];

    //pageTable declaration and population
    PageTable page;
    int tableSize;
    int pages = 0;
    fill(begin(registers), end(registers), 5);

    in >> tableSize;

    sem_wait(&semaphore);
    out << "Process " << threadNumber << " started" << endl;
    sem_post(&semaphore);

    for(int i = 0; i < tableSize; i++){
        if(i % pageSize == 0){
            pages = i / pageSize;
        }

        page.pageNumber = pages;
        pageTable3.push_back(page);
    }

    while (in >> op){
        if(op == 'R'){
            in >> regist;
            in >> virtualAddr;
            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);

            if(pageTable3[virtualAddr].valid == 1){
                registerIndex = regist.substr(1);
                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable3[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page" << pageTable3[virtualAddr].pageNumber << " to frame " << pageTable3[virtualAddr].frameNumber << endl;
                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << endl;
                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual address 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                sem_post(&semaphore);
            }


            if(pageTable3[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable3[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable3[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable3.size(); i++){

                    if(pageTable3[i].pageNumber == pageTable3[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable3[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable3[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable3[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable3[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual addr 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                
                sem_post(&semaphore);

            }

        }

        if(op == 'W'){ // Read operation

            in >> regist; // Read the register from the input file
            in >> virtualAddr; // Read the virtual address from the input file

            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);


            if(pageTable3[virtualAddr].valid == 1){
                
                registerIndex = regist.substr(1);

                mainMemory[pageTable3[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page " << pageTable3[virtualAddr].pageNumber << " to frame " << pageTable3[virtualAddr].frameNumber << endl;

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable3[virtualAddr].physicalAddress] << " from register " << regist << endl;
                sem_post(&semaphore);

            }


            if(pageTable3[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable3[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable3[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable3.size(); i++){

                    if(pageTable3[i].pageNumber == pageTable3[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable3[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable3[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable3[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                mainMemory[pageTable3[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable3[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable3[virtualAddr].physicalAddress] << " from register " << regist << endl;
                
                sem_post(&semaphore);

            }

        }

    }

    in.close(); // Close the input file
    out.close(); // Close the output file

}

void processThread4(int pageSize, int threadNumber, string threadFile, string outFile){
    //Variable declarations:
    ofstream out;
    out.open(outFile, ios_base::app);
    ifstream in(threadFile);
    char op;
    string regist;
    string registerIndex;
    int virtualAddr;
    int virtualAddrTemp;
    int registers[32];

    //pageTable declaration and population
    PageTable page;
    int tableSize;
    int pages = 0;
    fill(begin(registers), end(registers), 5);

    in >> tableSize;

    sem_wait(&semaphore);
    out << "Process " << threadNumber << " started" << endl;
    sem_post(&semaphore);

    for(int i = 0; i < tableSize; i++){
        if(i % pageSize == 0){
            pages = i / pageSize;
        }

        page.pageNumber = pages;
        pageTable4.push_back(page);
    }

    while (in >> op){
        if(op == 'R'){
            in >> regist;
            in >> virtualAddr;
            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);

            if(pageTable4[virtualAddr].valid == 1){
                registerIndex = regist.substr(1);
                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable4[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page" << pageTable4[virtualAddr].pageNumber << " to frame " << pageTable4[virtualAddr].frameNumber << endl;
                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << endl;
                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual address 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                sem_post(&semaphore);
            }


            if(pageTable4[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable4[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable4[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable4.size(); i++){

                    if(pageTable4[i].pageNumber == pageTable4[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable4[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable4[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable4[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                registers[stoi(registerIndex)] = stoi(mainMemory[pageTable4[virtualAddr].physicalAddress]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": " << regist << " = 0x" << intToHexadecimal(registers[stoi(registerIndex)]) << " (mem at virtual addr 0x" << intToHexadecimal(virtualAddr) << ")" << endl;
                
                sem_post(&semaphore);

            }

        }

        if(op == 'W'){ // Read operation

            in >> regist; // Read the register from the input file
            in >> virtualAddr; // Read the virtual address from the input file

            sem_wait(&semaphore);
            out << "P" << threadNumber << " OPERATION: " << op << " " << regist << " " << virtualAddr << endl;
            sem_post(&semaphore);


            if(pageTable4[virtualAddr].valid == 1){
                
                registerIndex = regist.substr(1);

                mainMemory[pageTable4[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": valid translation from page " << pageTable4[virtualAddr].pageNumber << " to frame " << pageTable4[virtualAddr].frameNumber << endl;

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable4[virtualAddr].physicalAddress] << " from register " << regist << endl;
                sem_post(&semaphore);

            }


            if(pageTable4[virtualAddr].valid == 0){

                sem_wait(&semaphore);
                out << "P" << threadNumber << ": page " << pageTable4[virtualAddr].pageNumber << " not resident in memory" << endl;

                if(freeFrames.empty()){

                    evict(threadNumber, outFile, pageSize);

                }

                out << "P" << threadNumber << ": using free frame " << freeFrames[0].frameNumber << endl;
                out << "P" << threadNumber << ": new translation from page " << pageTable4[virtualAddr].pageNumber << " to frame " << freeFrames[0].frameNumber << endl;

                for (int i = 0; i < pageTable4.size(); i++){

                    if(pageTable4[i].pageNumber == pageTable4[virtualAddr].pageNumber){

                        virtualAddrTemp = i;
                        break;

                    }

                }

                for(int i = virtualAddrTemp; i < (virtualAddrTemp + pageSize); i++){

                    pageTable4[i].physicalAddress = freeFrames[0].physicalAddress + (i - virtualAddrTemp);
                    pageTable4[i].frameNumber = freeFrames[0].frameNumber;
                    pageTable4[i].valid = 1;

                }

                freeFrames.erase(freeFrames.begin());

                sem_post(&semaphore);

                registerIndex = regist.substr(1);

                mainMemory[pageTable4[virtualAddr].physicalAddress] = intToHexadecimal(registers[stoi(registerIndex)]);

                sem_wait(&semaphore);

                out << "P" << threadNumber << ": translated VA 0x" << intToHexadecimal(virtualAddr) << " to PA 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << endl;

                out << "P" << threadNumber << ": main memory address 0x" << intToHexadecimal(pageTable4[virtualAddr].physicalAddress) << " now holds = 0x" << mainMemory[pageTable4[virtualAddr].physicalAddress] << " from register " << regist << endl;
                
                sem_post(&semaphore);

            }

        }

    }

    in.close(); // Close the input file
    out.close(); // Close the output file

}
