#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADMAX    10
#define QUEUEMAX    10
/* #define */
/* #define */
/* #define */
typedef struct threadpool_task_t{

    void*(*hanshu)(void *);
    void *arg;
}threadpool_task_t;

struct threadpool_t{
    pthread_t *threadid;               //线程id
    threadpool_task_t *task_queue;        /* 任务队列 */
    int busythread;                 //正在使用线程
    int maxthread;                //最大线程

    pthread_mutex_t lock;   //锁线程结构体
    pthread_mutex_t thread_counter; //锁线程数量
    pthread_cond_t queue_notempty; //任务队列不为空
    pthread_cond_t queue_notfull;  //任务队列不为满

    int queuemax;   //任务对列最大容纳数
    bool shutdown; //线程池状态

    int queue_front;                      /* 队头 */
    int queue_rear;                       /* 队尾 */
    int queue_size;                       //对垒大小

};

void threadinit(int size){
    struct threadpool_t *pool = NULL;

    if((pool = (struct threadpool_t *)malloc(sizeof(struct threadpool_t))) == NULL){
        /* my_err("pool",__LINE__); */
    }
    

          pool->maxthread = THREADMAX;
          pool->busythread = 0;
          pool->queue_front = 0;
          pool->queue_rear = 0;
          pool->queue_size = 0;
          pool->queuemax = QUEUEMAX;
          pool->shutdown = false;


          pool->threadid = (pthread_t *)malloc(sizeof(pthread_t)*pool->maxthread);
          if(pool->threadid == NULL);
            /* my_err("threadid",__LINE__); */

          /* 启动min_thr_num个工作线程 */
      for (int i=0; i<THREADMAX; i++)
      {
         /* pool指向当前线程池  threadpool_thread函数在后面讲解 */
         /* pthread_create(&(pool->threadid[i]), NULL, threadpool_thread, (void *)pool); */
      }
}



int main(){
    
    return 0;
}

