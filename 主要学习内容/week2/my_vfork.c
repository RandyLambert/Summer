#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int global = 4;

int main(){
    pid_t pid;
    int vari = 5;

    if((pid = vfork())<0){
        printf("vfork error\n");
        return 1;
    }
    else if(pid == 0){
        global++;
        vari++;
        printf("child changed the vari and global\n");
        _exit(0);
    }
    else{
        printf("parent didn't changed the vari and gobal\n");
    }
    printf("global = %d.vari = %d\n",global,vari);
    
    return 0;
}

