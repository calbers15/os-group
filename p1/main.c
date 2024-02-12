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
        wait(NULL);
        printf("Parent Process\n");
    }
    else if(pid == 0){
        printf("Child Process\n");
    }

    return 0;
}