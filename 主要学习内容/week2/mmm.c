#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    void * a = NULL;
    while(1){
        a = malloc(128*1024*1024);
        sleep(5);
    }
    
    return 0;
}

