#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid1, pid2;
    printf("Parent Process\n");
    printf("Parent ID: %d\n\n", (int) getpid());
    pid1 = fork();
    
    if (pid1 == 0){
        printf("Child 1 Process\n");
        printf("Child 1 ID: %d\n", (int) getpid());
        printf("Child 1 Complete\n\n");
    }

    else{
        printf("Parent creating Child Process 2\n");
        pid2 = fork();
        if(pid2 == 0){
            printf("Child 2 Process\n");
            printf("Child 2 ID: %d\n", (int) getpid());
        }
        else{
            wait(NULL);
            printf("Child 2 Complete\n\n");
        }

    }
    return 0;
}