//THIS IS THE COMMIT TO BE GRADED
//Cameron Albers, Austin Silva
//EECE.4811 Operating Systems
//Michael Geiger, Yongshun Xu
//03/02/24

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    pid_t pid;
    printf("Parent Process\n");
    printf("Parent ID: %d\n\n", (int) getpid());

    int arg;
    arg = atoi(argv[1]);
    pid_t child_pids[arg];

    for (int i = 0; i < arg; i++){
        pid = fork();
        //If process creation fails - code taken from figure 5.1 textbook
        if(pid < 0){
            printf("Fork failed\n");
            exit(1);
        }
        //random comment
        else if(pid == 0){
            printf("Child Process %d\n", i);
            printf("Child %d ID: %d\n", i, getpid());

            char executable[10];
            sprintf(executable,"./t%d", (i % 5) + 1);
            execlp(executable, executable, NULL);
            exit(0);
        }
        else{
            child_pids[i] = pid;
        }
    }


    for (int i = 0; i < arg; i++){
        int status;
        pid_t finished_pid = waitpid(child_pids[i], &status, 0);
        if(finished_pid != -1){
            printf("Child %d with ID %d finished successfully\n\n", i, finished_pid);
        }
    }
    return 0;
}