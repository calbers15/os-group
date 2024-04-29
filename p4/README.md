# Project 4 Directory

## Program 4
**Memory Management Simulator**

### About:

This README is written for Project 4. The purpose of Project 4 is to introduce students to memory management with page tables.

## How the program operates

-Users input an input file (infile#.txt), where # is 1-4.
-Users input an output file to be generated as the program runs.
-The input file provides the memory size, page size, number of threads to create, and the thread#.txt file to run in said threads.
-The threads process read/write instructions and allocates/deallocates space in main memory to complete instructions

### TO RUN

1. Navigate to root directory of project using cd commands
2. Run "ls" command to see if executable is present in directory. Executable will be named "p4.exe"
3. If no executable is present, run "make p4" command to execute makefile
4. Run ./p4 <infileX.txt> <outputY.txt> <Z> command, where "X" is the input file (1-4), "Y" is a user defined naming convention for output files, and "Z" is the seed for the RNG (random number generator)
5. To test multiple times, rename <outputY.txt> to any number of your choice. To name an output file the same name, please delete the prior output file