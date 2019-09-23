#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
extern int errnoi;
int main(){

    int fd;

    printf("uid study:\n");
    printf("process's uid = %d,euid = %d\n",getuid(),geteuid());


    if((fd = open("text",O_RDWR)) == -1) {
        printf("error");
        return -1;
    }
    else{
        printf("open success\n");
    }
    
    close(fd);
    
    return 0;
}

