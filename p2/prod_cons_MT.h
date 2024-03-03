#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

#include <pthread.h>

#define BUFFER_SIZE 100

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Monitor;

extern Monitor monitor;

void init_monitor();
void *producer(void *arg);
void *consumer(void *arg);

#endif