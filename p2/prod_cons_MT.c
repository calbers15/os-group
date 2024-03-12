#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


void init_monitor(Monitor *m, int buffer_size){
    m->buffer = (int *)malloc(buffer_size * sizeof(int));
    m->buffer_size = buffer_size;
    m->count = 0;
    m->in = 0;
    m->out = 0;
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->not_full, NULL);
    pthread_cond_init(&m->not_empty, NULL);
}

void destroy_monitor(Monitor *m) {
    free(m->buffer);
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->not_full);
    pthread_cond_destroy(&m->not_empty);
}


/*void *consumer(void *arg) {
    Monitor *m = (Monitor *)arg;
    int max_values_write = m->buffer_size * 2;
    static int consumer_id_counter = 0;
    int consumer_id;
    pthread_mutex_lock(&m->mutex);
    consumer_id = consumer_id_counter++;
    pthread_mutex_unlock(&m->mutex);

    /*int total_values = m->buffer_size / 2;  // Each consumer reads half of the total values
    int *num_consumers = (int *)arg;
    int values_to_read = total_values / *num_consumers;
    
    if((*num_consumers % 2) == 1){
        if (consumer_id == *num_consumers - 1) {
            // Last consumer in odd num consumer group reads any remaining values
            values_to_read += total_values % *num_consumers;
        }
    }


    int *num_consumers = *((int *)arg);
    int values_to_read = max_values_write / *num_consumers;
    


    printf("Consumer C%d entered. Consuming %d values.\n", consumer_id, values_to_read);

    for (int i = 0; i < values_to_read; i++) {
        pthread_mutex_lock(&m->mutex);
        while(m->count <= 0){
            printf("Consumer C%d waiting, buffer empty.\n", consumer_id);
            pthread_cond_wait(&m->not_empty, &m->mutex);
            printf("Consumer C%d woke up, consuming values.\n", consumer_id);
        }

        int value = m->buffer[m->out];
        printf("Consumer C%d removed value %d from buffer at position %d.\n", consumer_id, value, m->out);
        m->out = (m->out + 1) % m->buffer_size;
        m->count--;
        pthread_cond_signal(&m->not_full);
        pthread_mutex_unlock(&m->mutex);
    }

    printf("Consumer C%d finished.\n", consumer_id);

    return NULL;
}*/

void *producer(void *arg) {
    srand(time(0));
    Monitor *m = (Monitor *)arg;
    int max_values_write = m->buffer_size * 2;

    static int producer_id_counter = 0;
    int producer_id;
    pthread_mutex_lock(&m->mutex);
    producer_id = producer_id_counter++;
    pthread_mutex_unlock(&m->mutex);

    printf("Producer P%d entered. Producing %d values.\n", producer_id, max_values_write);
    for (int i = 0; i < max_values_write; i++) {
        pthread_mutex_lock(&m->mutex);
        while(m->count >= m->buffer_size){
            printf("P%d blocked due to full buffer.\n", producer_id);
            pthread_cond_wait(&m->not_full, &m->mutex);
            printf("P%d woke up, producing values.\n", producer_id);
        }

        int data = rand() % 11;
        m->buffer[m->in] = data;
        printf("P%d added value %d into buffer at position %d.\n", producer_id, data, m->in);
        m->in = (m->in + 1) % m->buffer_size;
        m->count++;
        pthread_cond_signal(&m->not_empty);
        pthread_mutex_unlock(&m->mutex);
    }

    printf("P%d thread finished.\n", producer_id);
    return NULL;\
}
void *consumer(void *arg) {
    Monitor *m = (Monitor *)arg;
    static int consumer_id_counter = 0;
    int consumer_id;
    pthread_mutex_lock(&m->mutex);
    consumer_id = consumer_id_counter++;
    pthread_mutex_unlock(&m->mutex);

    int num_consumers = *((int *)arg);
    int max_values_read = (m->buffer_size * 2) / num_consumers;
    int values_read = 0;

    printf("Consumer C%d entered. Consuming %d values.\n", consumer_id, max_values_read);

    while (values_read < max_values_read) {
        pthread_mutex_lock(&m->mutex);
        while (m->count <= 0) {
            printf("Consumer C%d waiting, buffer empty.\n", consumer_id);
            pthread_cond_wait(&m->not_empty, &m->mutex);
            printf("Consumer C%d woke up, consuming values.\n", consumer_id);
        }

        int value = m->buffer[m->out];
        printf("Consumer C%d removed value %d from buffer at position %d.\n", consumer_id, value, m->out);
        m->out = (m->out + 1) % m->buffer_size;
        m->count--;
        values_read++;
        pthread_cond_signal(&m->not_full);
        pthread_mutex_unlock(&m->mutex);
    }

    printf("Consumer C%d finished.\n", consumer_id);

    return NULL;
}

