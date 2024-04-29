# Project 3 Directory

## Program 3
**Scheduling Algorithms**

### About:

This README is written for Project 3. The purpose of Project 3 is to introduce students to scheduling algorithms

## How the program operates

-Users input a datafile as input (testin1.dat, testin2.dat)

-The program reads the file and simulates 5 different scheduling algorithms

-The 5 different algorithms are as follows:

1. First Come First Serve (FCFS)
2. Shortest Job First (SJF)
3. Shortest Time to Completion First (STCF)
4. Round Robin
5. Non-preemptive Priority (NPP)

-The program simulates these algorithms in that order

### TO RUN

1. Navigate to root directory of project using cd commands
2. Run "ls" command to see if executable is present. Executable will be named "p3.exe"
3. If no executable is present, run "make p3" command to execute makefile
4. Run ./p3 <testin#.dat> <output.txt> <i> where "#" is either 1 or 2, and i is your desired output interval
5. You can name your output file anything, but if you will name it "output.txt", delete the prior instance of "output.txt"