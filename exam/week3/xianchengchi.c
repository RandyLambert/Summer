#include <stdio.h>

#define threadmax 1000
typedef struct node{
    //任务信息
    struct node *next;
}node;


typedef struct thread1{
    //线程信息等
    struct node *next;
}thread;


typedef struct head2{
    int num = 1123;       //线程总数
    int shenyuliang = 22; //可用线程总数
    //等等信息。。。。
    struct node * next;
}head2;

typedef struct head{
    int num = 1123;       //任务总数
    //等等信息。。。。
    struct node * next;
}head;

void init(){
    int i = 0;
    
    head headrenwu = (struct head *)malloc(struct head);
    head->next = NULL;
    
    head2 head2xiancheng = (struct head2 *)malloc(struct head2);
    head2->next = NULL;

    while(i < threadmax){
        thread1 *p1 = (thread1 *)malloc(sizeof(head2));
            
        线程信息存p1  pthread_create(&p1.num,NULL,(void *)hanshu,NULL);
        ...............
        一直循环存到链表
        创建足够线程，使线程处于等待
    }
}

void shanchu任务(int hao){

    struct node * p1,*p2;
    while(true){
        循环链表找到
    }
    p1 = 那个;
    ->next = ->next->next;
    free(p1);
}

void 添加任务(*){

    struct node * p1,*p2;
    while(true){

    }
    p1->next = 任务；

}

int main(){
    
    init();
    
    while(1){

        线程处于等待
        来任务
        jiaru()尾插法插入任务链表,边插边唤醒,没有线程可以使用就阻塞
        当没有到线程使用的极限量时
        head节点信息更新，++操作和--操作，还要用锁，唤醒线程去执行任务
        shanchu();  将执行任务从任务队列删除

    }

    销毁线程池，不是立即销毁是等待线程结束后在销毁
    
    return 0;
}

