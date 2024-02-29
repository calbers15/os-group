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
    for (int i = 0; i < 5; i++){
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
            printf("Child %d with ID %d finished successfully\n\n", i, getpid());
            exit(0);
        }
    }


    for (int i = 0; i < 5; i++){
        wait(NULL);
    }
    return 0;
}