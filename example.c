#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "yastopwatch.h"

#define FREQ (2.4 * 1000 * 1000 * 1000)

DEF_THREADED_SW(t1);
DEF_SW(t2);
DEF_THREADED_TSC_SW(t3);
DEF_TSC_SW(t4);

void* worker1 (void* arg) {
    START_SW(t1);
    
    sleep(1);
    
    STOP_SW(t1);
    SYNC_SW(t1);

    return NULL;
}

void* worker2 (void* arg) {
    START_SW(t3);
    
    sleep(1);
    
    STOP_SW(t3);
    SYNC_SW(t3);

    return NULL;
}

int main() {
    pthread_t thr1, thr2, thr3, thr4;

    START_SW(t2);
    START_SW(t4);
    
    pthread_create(&thr1, NULL, worker1, NULL);
    pthread_create(&thr2, NULL, worker1, NULL);
    pthread_create(&thr3, NULL, worker2, NULL);
    pthread_create(&thr4, NULL, worker2, NULL);
    
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    STOP_SW(t2);
    STOP_SW(t4);

    printf("[t1] Total time: %lf\n", GET_SEC(t1));
    printf("[t1] Total count: %llu\n", GET_COUNT(t1));
    
    printf("[t2] Total time: %lf\n", GET_SEC(t2));
    printf("[t2] Total count: %llu\n", GET_COUNT(t2));

    printf("[t3] Total time: %lf\n", GET_SEC(t3));
    printf("[t3] Total count: %llu\n", GET_COUNT(t3));
    
    printf("[t4] Total time: %lf\n", GET_SEC(t4));
    printf("[t4] Total count: %llu\n", GET_COUNT(t4));
}
