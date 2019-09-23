#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    int pid;
    printf("father progress,and father progress pid is %d\n",getpid());

    if(0 == fork()){
        printf("father progress forked,and child progress pid is %d\n",getpid());
    }
    else{
        if(0 == fork()){
            printf("father progress forked,and child progress pid is %d\n",getpid());
                while(1) ;
        }
        else{
            if(0 == fork()){
                printf("father progress forked,and child progress pid is %d\n",getpid());
            }
            else{
                if(-1 == (pid = wait(NULL))){
                    printf("no child progress,and wait() return -1\n");
                }
                else{
                    printf("wait() return child progress pid is %d\n",pid);
                }
                
                if(-1 == (pid = wait(NULL))){
                    printf("no child progress,and wait() return -1\n");
                }
                else{
                    printf("wait() return child progress pid is %d\n",pid);
                }

                if(-1 == (pid = wait(NULL))){
                    printf("no child progress,and wait() return -1\n");
                }
                else{
                    printf("wait() return child progress pid is %d\n",pid);
                }
            }
        }
    }
    return 0;
}

