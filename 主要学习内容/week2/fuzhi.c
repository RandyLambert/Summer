#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int rfd,wfd;
char c;
int main(int argc,char *argv[]){

    if(argc!=3){
        printf("usage input chanshu cuwu\n");
        return 1;
    }

    if((rfd = open(argv[1],O_RDONLY)) == 0){
        printf("open error\n");
        return 1;
    }

    if((wfd = creat(argv[2],0666))==-1){
        printf("creat error\n");
        return 1;
    }

    fork();
    for(;;){
        if(read(rfd,&c,1)!=1)
            return 1;
        write(wfd,&c,1);
    }

    return 0;
}

