#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
int main(){

    printf("wait return :%d",wait(NULL));
    
    return 0;
}

