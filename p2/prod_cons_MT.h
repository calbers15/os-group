#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

#include <pthread.h>


struct Monitor {
    int *buffer;
    int in;
    int out;
    int count;
    int buffer_size;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
};

extern struct Monitor monitor;

void init_monitor(int buffer_size);
void *producer(void *arg);
void *consumer(void *arg);

#endif