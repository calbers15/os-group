#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//init monitor member function utilizes structure member variables defined in header file to set up the monitor for use, based on user input.
//also intitializes the pthread functions and condition variables that will be utilized
void init_monitor(Monitor *m, int buffer_size, int numProducers, int numConsumers){
    m->buffer = (int *)malloc(buffer_size * sizeof(int));       //dynamically allocate memory for n=buffer_size of integer sized data members
    m->buffer_size = buffer_size;
    m->count = 0;
    m->in = 0;
    m->out = 0;
    m->num_consumers = numConsumers;
    m->num_producers = numProducers;
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->not_full, NULL);
    pthread_cond_init(&m->not_empty, NULL);
}

//destructor, releases all condition variables and mutex locks, as well as erases entire buffer
void destroy_monitor(Monitor *m) {
    free(m->buffer);
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->not_full);
    pthread_cond_destroy(&m->not_empty);
}

//producer function, in charge of calculating values to be entered,
//when to lock the buffer (during critical sections ie adding values),
//when to signal consumer threads that buffer is ready to be read,
//when to not write to buffer due to it being full
void *producer(void *arg) {
    srand(time(0));         //set up the time varaible for random number generation
    Monitor *m = (Monitor *)arg;    //declare *m as the argument passed into the function from main
    int max_values_write = m->buffer_size * 2;  //sets the maximum values that each producer will produce as double the buffer size (from program spec)

    static int producer_id_counter = 0; //producer_id _counter is static so that each thread has a unique id
    int producer_id;    //unique producer id for each producer thread
    pthread_mutex_lock(&m->mutex);  //lock the producer_id_counter to ensure that only one thread at a time increments it, giving a unique id for each thread
    producer_id = producer_id_counter++;
    pthread_mutex_unlock(&m->mutex);

    printf("Producer P%d entered. Producing %d values.\n", producer_id, max_values_write);
    for (int i = 0; i < max_values_write; i++) {
        pthread_mutex_lock(&m->mutex);      //lock this section of code while producer is writing value to buffer
        while(m->count >= m->buffer_size){      //if the amount of data in buffer has reached (or exceeded) buffer size, print message and wait until not full
            printf("P%d blocked due to full buffer.\n", producer_id);
            pthread_cond_wait(&m->not_full, &m->mutex);
            printf("P%d woke up, producing values.\n", producer_id);
        }

        int data = rand() % 11;     //randomizes data added to buffer from 1 to 10
        m->buffer[m->in] = data;    //input data into buffer at position [m->in]
        printf("P%d added value %d into buffer at position %d.\n", producer_id, data, m->in);
        m->in = (m->in + 1) % m->buffer_size;   //increment 
        m->count++;
        pthread_cond_signal(&m->not_empty);
        pthread_mutex_unlock(&m->mutex);
    }

    printf("P%d thread finished.\n", producer_id);
    return NULL;
}
void *consumer(void *arg) {
    Monitor *m = (Monitor *)arg;
    static int consumer_id_counter = 0;
    int consumer_id;
    pthread_mutex_lock(&m->mutex);
    consumer_id = consumer_id_counter++;
    pthread_mutex_unlock(&m->mutex);

    int num_consumers = m->num_consumers;
    int total_values = (m->buffer_size * 2) * m->num_producers;
    int values_to_read = total_values / num_consumers;
    if (consumer_id == num_consumers - 1) {
        // Last consumer reads any remaining values
        values_to_read += total_values % num_consumers;
    }

    //printf("%d / %d = %d\n", total_values, num_consumers, values_to_read); used to debug total_values issue
    printf("Consumer C%d entered. Consuming %d values.\n", consumer_id, values_to_read);

    for (int i = 0; i < values_to_read; i++) {
        pthread_mutex_lock(&m->mutex);
        while (m->count <= 0) {
            printf("Consumer C%d waiting, buffer empty.\n", consumer_id);
            pthread_cond_wait(&m->not_empty, &m->mutex);
            printf("Consumer C%d woke up, buffer not empty.\n", consumer_id);
        }
        
        int value = m->buffer[m->out];
        printf("Consumer C%d removed value %d from buffer at position %d.\n", consumer_id, value, m->out);
        m->out = (m->out + 1) % m->buffer_size;
        m->count--;

        // Signal producer if buffer was full
        pthread_cond_signal(&m->not_full);
        pthread_mutex_unlock(&m->mutex);
    }

    printf("Consumer C%d finished.\n", consumer_id);

    return NULL;
}
