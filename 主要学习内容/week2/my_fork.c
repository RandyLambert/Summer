#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){

    pid_t pid;
    printf("Start of fork testing\n");
    pid = fork();

    printf("Return of fork success:pid = %d\n",pid);
    printf("father :%d       %d",getpid(),getppid());
    
    return 0;
}

