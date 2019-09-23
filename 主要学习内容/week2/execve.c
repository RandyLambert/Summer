#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
int main(int argc,char *argv[],char ** environ){
    

    //exec.test
    pid_t pid;
    int stat_val;

    printf("exal example\n");
    pid = fork();
    switch(pid){
    case -1:
            perror("process creation failed\n");
        case 0:
            printf("child process is running\n");
            printf("my pid = %d,parentpid = %d\n",getpid(),getppid());
            printf("uid = %d,gid = %d\n",getuid(),getgid());
            execve("processimage",argv,environ);
            printf("process never go to here!\n");
            exit(0);
        default:
            printf("parent process is running\n");
            break;
    }

    wait(&stat_val);
    exit(0);
}

