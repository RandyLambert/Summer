#include<sys/wait.h>
#include<stdio.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
    
    pid_t pid;
    if((pid = fork()) < 0){
        printf("error\n");
        exit(1);
    }
    else if(pid == 0){
        if((pid = fork()) < 0){
            printf("error\n");
            exit(1);
        }
        else if(pid > 0){
            exit(0); //parent from second fork == first child
        }
        sleep(2);
        printf("second child ,parent pid = %ld\n",(long)getppid());
        exit(0);
    }

    if(waitpid(pid,NULL,0) != pid) //wait for first pid
    {
        printf("error\n");
        exit(1);
    }


    
    return 0;
}

