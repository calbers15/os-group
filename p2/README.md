# Project 2 Directory

## Program 2: 2/28/24
**Multi-threaded Programming**


### About:

This README is written for Project 2. The purpose of Project 1 is to introduce students
to multithreaded programming with producers and consumers.

### How the Program Operates

-Users input the program executable's name, number of producers, consumers, and buffer size (example: ./p2 2 2 2)

-The program creates specified number of threads and allocates memory for shared buffer

-Producers will produce n = 2 * buffer_size elements, values of elements range from 1-10 for readability

-Consumers will consume n = total_values / num_consumers, with one consumer handling extra values if needed

-Buffer is limited, so if full/empty, producers/consumers wait to perform operation

-Once all producers have produced all possible values, they are joined

-Once all consumers have consumed all possible values, they are joined



### TO RUN

1. Naviagte to root directory of project using cd commands
2. Type ./p2 <num_producers> <num_consumers> <buffer_size>
3. Hit enter


### TROUBLESHOOTING

#### Re-run CMake

1. Delete the executable, along with all test program executables. (rm p2)

2. Delete the build folder (rm -r build)

3. Create a new build folder (mkdir build)

4. Re-run CMake (cmake ..) , (cmake --build .)

5. Move all executables to project's root directory (mv p2 ..)

#### Check your input

You must input three numbers onto the command line, if not the program will not work.
