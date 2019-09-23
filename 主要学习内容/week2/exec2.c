#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
int main(){
    
    int fd;
    char buf[1000];
    /* memset(buf,0,sizeof(buf)); */
    fd = open("text",0);

    if(fd == -1){
        printf("cant open this\n");
        return -1;
    }
    
    printf("========fd = %d in test.c =======\n",fd);

    fd-=1;
    read(fd,buf,800);
    printf("===========output int test.c ====== %s",buf);
    /* write(fd,buf,800); */


    return 0;
}

