#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h> 
#include <sys/wait.h>
//读管道
void read_from_pipe(int fd){
    char message[100];
    read(fd,message,100);
    printf("read form pipe:%s",message);
}

//写管道

void write_to_pipe (int fd){
    char *message = "hellow.pipe\n";
    write(fd,message,strlen(message) + 1);
}
int main(){

    int fd[2];
    pid_t pid;
    int stat_val;


    if(pipe(fd)){
        printf("create pipe faild\n");
    }

    pid = fork();

    switch(pid){
    case -1:
        printf("fork error\n");
        exit(0);
    case 0:
        //子进程关闭fd1
        close(fd[1]);
        read_from_pipe(fd[0]);
        exit(0);
    default:
        close(fd[0]);
        write_to_pipe(fd[1]);
        wait(&stat_val);
        exit(0);

    }
    
    return 0;
}

