#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *thread(void *arg){
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new threaed id = %u\n",newthid);
    return NULL;

}
int main(){
    
    pthread_t thid;

    printf("main thread ,id is %u\n",pthread_self()); //打印主线程id
    if(pthread_create(&thid,NULL,(void*)thread,NULL) != 0){
        printf("thread creation failed\n");
        exit(1);
    }
    sleep(1);
    exit(0);
    
}

