#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
pthread_mutex_t chopstick[6] ;
void get(int *left,int *right,char phi) { //通过此函数判断这个人左右是啥筷子
    switch (phi){
    case 'A':
        *left = 5;
        *right = 1;
        break;
    case 'B':
        *left = 1;
        *right = 2;
        break;
    case 'C':
        *left = 2;
        *right = 3;
        break;
    case 'D':
        *left = 3;
        *right = 4;
        break;
    case 'E':
        *left = 4;
        *right = 5;
        break;
    }
}
void *eat_think(void *arg)
{
    char phi = *(char *)arg;//
    int left,right;         //
    get(&left,&right,phi); //判断是哪一个线程，他的左右筷子分别是啥
    for(;;){
        usleep(10);
        pthread_mutex_lock(&chopstick[left]);           //线程先去获取左筷子的锁，如果拿到了继续进行
        printf("Philosopher %c fetches chopstick %d\n", phi,left); //打印那个线程拿到左边的锁
        if (pthread_mutex_trylock(&chopstick[right]) ==EBUSY){//尝试去拿右边的锁
            pthread_mutex_unlock(&chopstick[left]);//没拿到右边的锁就解开左边的锁，不要占用锁的资源
            continue;//进行下一轮
        }
        printf("Philosopher %c fetches chopstick %d\n", phi,right); //打印拿到了右边的锁
        printf("Philosopher %c is eating.\n",phi); //打印这个人成功吃饭
        usleep(10);
        pthread_mutex_unlock(&chopstick[left]); //解开左边的锁
        printf("Philosopher %c release chopstick %d\n", phi,left);//打印释放左边的锁
        pthread_mutex_unlock(&chopstick[right]);//解开右边的锁
        printf("Philosopher %c release chopstick %d\n", phi,right);//打印释放右边的锁
    }
}
int main(){
    pthread_t A,B,C,D,E; //5个哲学家
    int i;
    for (i = 0; i < 5; i++)
        pthread_mutex_init(&chopstick[i],NULL); //为五个筷子分别创建线程锁
    pthread_create(&A,NULL, eat_think, (void *)"A");
    pthread_create(&B,NULL, eat_think, (void *)"B");
    pthread_create(&C,NULL, eat_think, (void *)"C");
    pthread_create(&D,NULL, eat_think, (void *)"D");
    pthread_create(&E,NULL, eat_think, (void *)"E");
    pthread_join(A,NULL);
    pthread_join(B,NULL);
    pthread_join(C,NULL);
    pthread_join(D,NULL);
    pthread_join(E,NULL);
    return 0;
}
