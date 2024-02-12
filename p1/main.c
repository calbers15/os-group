#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid > 0){
        printf("Waiting for child to finish\n");
        wait(NULL);
        printf("Child Completed\n\n");
        printf("Parent Process\n");
        printf("Parent ID: %d\n\n", (int) getpid());
    }
    else if(pid == 0){
        printf("Child Process\n");
        printf("Child ID: %d\n\n", (int) getpid());

    }

    return 0;
}