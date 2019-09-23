#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
pthread_cond_t cond;

int count = 0;
void *a(void *arg){
    
    while(1){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
        
        pthread_mutex_lock(&mutex);
        printf("创建资源的线程A\n");
        /* sleep(1); */
        if(count > 0){
           pthread_cond_signal(&cond); 
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *b(void *arg){

    while(1){
        pthread_mutex_lock(&mutex);
    
        while(count <= 0){
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_lock(&mutex2);
            count--;
            pthread_mutex_unlock(&mutex2);
        }
        printf("使用资源的线程B\n");
        /* sleep(1); */
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t A,B;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&A,NULL,(void *)a,NULL);
    pthread_create(&B,NULL,(void *)b,NULL);
    
    pthread_join(A,NULL);
    pthread_join(B,NULL);
    return 0;
}

