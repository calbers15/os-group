#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid1, pid2;
    pid1 = fork();
    
    if(pid1 == 0){
            printf("Child 1 Process\n");
            printf("Child 1 ID: %d\n\n", (int) getpid());
            printf("Child 1 Finished\n\n");

        }

    else{
        wait(NULL);
        printf("First child complete\n");
        printf("Parent creating second child\n");
        pid2 = fork();
        if(pid2 == 0){
            printf("Child 2 Process\n");
            printf("Child 2 ID: %d\n\n", (int) getpid());
            printf("Child 2 Finished\n\n");
        }
        printf("Waiting for child to finish\n");
        wait(NULL);
        printf("Parent Process\n");
        printf("Parent ID: %d\n", (int) getpid());
    }
    

    return 0;
}