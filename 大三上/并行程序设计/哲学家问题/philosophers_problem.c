/* 本人使用了两种方式避免死锁
 *
 * 第一种：使用信号量让一次最多只有 n - 1 个哲学家进入临界区，这样必有一个哲学家能打破“死锁状态”，
 *        进而所有哲学家都能吃上饭(模式代码为 -sema )
 *            
 * 第二种：让所有哲学家按顺序吃饭，使用一个flag变量,一个锁以及一个条件变量实现，flag表示当前应该吃饭的哲学家编号，
 *        其他编号的哲学家会将自己sleep并释放锁，直到对应编号的哲学家拿到锁(模式代码为 -order )
 * 
 * 调用方式：
 *      1. 编译命令：gcc -g -Wall -std=gnu99 -o philosopher philosophers_problem.c
 *         (gcc版本：14.3.0)
 *      2. 使用：./philosopher [-mode(仅能为三个值，-normal，-sema，-order)] -n [哲学家的个数(>1)]
 * 
 *      3. 已处理所有错误输入(酒吧不能因为 null 点了 -1 份外星人就炸了对吧)
 */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <threads.h>
#include <unistd.h>
#include <semaphore.h>

// 三种模式
enum mode {
    normal, sema, order
} mode;
int thread_count;
// 资源变量
pthread_mutex_t *mutexs;

// 使用信号量时的变量
sem_t semaphore;

// 使用顺序吃饭时的变量
int flag;
pthread_mutex_t order_mutex;
pthread_cond_t cond;

// 自定义睡觉函数
void my_sleep() {
    // 睡眠时间：[0.01, 0.1]
    usleep((rand() + 10) % 101);
}

void* philosopher(void* rank) {
    int my_rank = (int)rank;
    // 该哲学家思索中
    printf("philosopher %d is thinking\n", my_rank);
    my_sleep();
    // 开始尝试拿锁
    printf("philosopher %d is trying\n", my_rank);
    switch(mode) {
        case normal :
            // 普通模式，会死锁，哲学家越多，越不容易观察到死锁现象
            pthread_mutex_lock(&mutexs[my_rank]);
            // 现代处理器速度太快，两次加锁之间需要小睡一下，不然观察不到死锁现象
            my_sleep();
            pthread_mutex_lock(&mutexs[(my_rank + 1) % thread_count]);
            // 两双筷子都拿到了，开吃
            printf("philosopher %d is eating\n", my_rank);
            my_sleep();
            pthread_mutex_unlock(&mutexs[my_rank]);
            pthread_mutex_unlock(&mutexs[(my_rank + 1) % thread_count]);
            break;
        case sema :
            // 一次最多 n - 1 个哲学家在吃饭
            sem_wait(&semaphore);
            pthread_mutex_lock(&mutexs[my_rank]);
            // 现代处理器速度太快，两次加锁之间需要小睡一下，不然无法测试实现是否正确
            my_sleep();
            pthread_mutex_lock(&mutexs[(my_rank + 1) % thread_count]);
            sem_post(&semaphore);
            // 两双筷子都拿到了，开吃
            printf("philosopher %d is eating\n", my_rank);
            my_sleep();
            pthread_mutex_unlock(&mutexs[my_rank]);
            pthread_mutex_unlock(&mutexs[(my_rank + 1) % thread_count]);
            break;
        case order :
            pthread_mutex_lock(&order_mutex);
            while (flag != my_rank) {
                pthread_cond_wait(&cond, &order_mutex);
            }
            pthread_mutex_lock(&mutexs[my_rank]);
            // 现代处理器速度太快，两次加锁之间需要小睡一下，不然无法测试实现是否正确
            my_sleep();
            pthread_mutex_lock(&mutexs[(my_rank + 1) % thread_count]);
            // 两双筷子都拿到了，开吃
            printf("philosopher %d is eating\n", my_rank);
            my_sleep();
            pthread_mutex_unlock(&mutexs[my_rank]);
            pthread_mutex_unlock(&mutexs[(my_rank + 1) % thread_count]);
            flag++;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&order_mutex);
            break;
        default:
            printf("code should not reach here!\n");
            abort();
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // 接受输入并检查输入正确性
    if (argc != 4) {
        printf("insufficient or redundant parameters\n");
        abort();
    }
    pthread_t* thread_handles;
    srand(time(NULL));
    if (strcmp("-normal", argv[1]) == 0) {
        mode = normal;
    } else if (strcmp("-sema", argv[1]) == 0) {
        mode = sema;
    } else if (strcmp("-order", argv[1]) == 0) {
        mode = order;
    } else {
        printf("invalid mode\n");
        abort();
    }
    if (strcmp("-n", argv[2])) {
        printf("invalid count\n");
        abort();
    }

    // 使用传入的参数初始化变量
    thread_count = atoi(argv[3]);
    if (thread_count <= 1) {
        printf("invalid philosopher number!\n");
        abort();
    }
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    mutexs = malloc(thread_count * sizeof(pthread_mutex_t));
    sem_init(&semaphore, 0, thread_count - 1);
    pthread_mutex_init(&order_mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int thread = 0; thread < thread_count; thread++) {
        // 创建线程并初始化锁
        pthread_create(&thread_handles[thread], NULL, philosopher, (void*)thread);
        pthread_mutex_init(&mutexs[thread], NULL);
    }

    for (int thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread],  NULL);
    }

    for (int thread = 0; thread < thread_count; thread++) {
        pthread_mutex_destroy(&mutexs[thread]);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&order_mutex);
    sem_destroy(&semaphore);
    free(thread_handles);
    free(mutexs);
    return 0;
}