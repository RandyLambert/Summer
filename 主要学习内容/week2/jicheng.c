#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#define SIZE 1024
#define KEY 99

int shmid;
int j=5;

int main(){

    int i,*pint;
    pid_t pid;
    char *addr;

    i = 10;
    shmid = shmget(SIZE,KEY,IPC_CREAT|0777);
    pint = shmat(shmid,0,0);
    *pint = 100;
    printf("start of fork testing\n");
    pid = fork();

    i++,j++,*pint+=1;

    printf("return of fork success:pi=%d\n",pid);
    printf("i = %d,j=%d\n",i,j);
    printf("*pint=%d\n",*pint);
    return 0;
}

