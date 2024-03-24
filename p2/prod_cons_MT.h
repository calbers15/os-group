//Cameron Albers & Austin Silva
//EECE.4811 - Operating Systems
//Michael J. Geiger, Yongshun Xu
//Project 2 - Multithreading

#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

#include <pthread.h>

//define the Monitor structure, with member variables and pthread locks and conditions
typedef struct {
    int *buffer;                //the buffer that data will be written to and read from
    int buffer_size;            //variable is user defined in init_monitor
    int count;                  //used to keep track of how many items are in buffer
    int in;                     //position that data is passed into the buffer at
    int out;                    //position that data is read from the buffer at
    int num_consumers;          //variable used to calculate the amount of data for each consumer to consume
    int num_producers;          //variable used to calculate the amount of data for each consumer to consume
    pthread_mutex_t mutex;      //mutex lock to secure critical sections of code
    pthread_cond_t not_full;    //condition signaling threads that the buffer isn't full anymore, producers can continue writing
    pthread_cond_t not_empty;   //condition signaling threads that the buffer isn't empty anymore, consumers can continue reading
} Monitor;


void init_monitor(Monitor *m, int buffer_size, int numProducers, int numConsumers); //function defined in prod_cons_MT.c
void *producer(void *arg);                                                           //function defined in prod_cons_MT.c
void *consumer(void *arg);                                                           //function defined in prod_cons_MT.c
void destroy_monitor(Monitor *m);                                                    //function defined in prod_cons_MT.c

#endif