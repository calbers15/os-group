#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

#include <pthread.h>


typedef struct {
    int *buffer;
    int buffer_size;
    int count;
    int in;
    int out;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Monitor;


void init_monitor(Monitor *m, int buffer_size);
void *producer(void *arg);
void *consumer(void *arg);
void destroy_monitor(Monitor *m);

#endif