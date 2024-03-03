# Project 1 Directory
Cameron Albers, Austin Silva

03/02/24

EECE.4811 Operating Systems

Project 1

**Due Date**

*2/14/24*

## About:

This README is written for Project 1. The purpose of Project 1 is to introduce students
to processes and process management.

### How the Program Operates

-Users input the program executable's name, as well as the number of processes the user would like to create (example: ./p1 4)

-The program's parent process creates the desired amount of child processes

-The child processes can execute any one of the five predetermined test programs

-If there are more than five child processes, the sixth child process's test program rolls back to execute test program 1

-Once a child processes has finished executing its  program, the parent process is notified that the child has finished

-The parent process outputs a message that the child process has finished it's execution

-Once all child processes have finished executing, the parent process can end, and it outputs a message



### TO RUN

1. Naviagte to root directory of project using cd commands
2. Type ./p1 <num_processes>
3. Hit enter


### TROUBLESHOOTING

#### Re-run CMake

1. Delete the executable, along with all test program executables. (rm p1 t1 t2 t3 t4 t5)

2. Delete the build folder (rm -r build)

3. Create a new build folder (mkdir build)

4. Re-run CMake (cmake ..) , (cmake --build .)

5. Move all executables to project's root directory (mv p1 t1 t2 t3 t4 t5 ..)

#### Check your input

You must input a number onto the command line, if not the program will not work.