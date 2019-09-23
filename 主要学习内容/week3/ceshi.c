#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int number = 10;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *f(void *arg){

    while(1){
        pthread_mutex_lock(&mutex);

        number++;

        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        if(number>10000)
            pthread_cond_signal(&cond);
        /* break; */
        pthread_mutex_unlock(&mutex);
        /* pthread_exit(0); */
    }    
}

void *h(void *arg){

    pthread_mutex_lock(&mutex);

    while(number < 10000)
        pthread_cond_wait(&cond,&mutex);

    printf("hhhhhhhhh%d\n",number);

    pthread_mutex_unlock(&mutex);

    /* pthread_exit(0); */
}

/* void *h(void *arg){ */
/*     while(1) */
/*     { */
/*         pthread_mutex_lock(&mutex); */
/*         number++; */
/*         pthread_mutex_unlock(&mutex); */
    /* } */
/* } */

/* void *f(void *arg){ */

/*     while(1) */
/*     { */
/*         pthread_mutex_lock(&mutex); */
/*         if(number >= 100) */
/*         { */
/*             number = 0; */
/*         } */
/*         printf("%d\n",number); */
/*         pthread_mutex_unlock(&mutex); */

/*         /1* pthread_exit(NULL); *1/ */

    /* } */
/* } */
int main(){

    pthread_t tid1,tid2;
    int status;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);


    printf("kaishi\n");
    pthread_create(&tid1,NULL,(void*)f,NULL);
    pthread_create(&tid2,NULL,(void*)h,NULL);

    pthread_join(tid1,(void*)&status);//等待一个线程的结束
    pthread_join(tid2,(void*)&status);
    printf("%d\n",number);
    
    
    
    return 0;
}

