#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int active_producers = 0;
int producers_exited = 0;
struct Monitor monitor;

void init_monitor(int buffer_size) {
    monitor.buffer_size = buffer_size;
    monitor.buffer = malloc(buffer_size * sizeof(int)); // Allocate buffer based on buffer_size
    monitor.in = 0;
    monitor.out = 0;
    monitor.count = 0;
    pthread_mutex_init(&monitor.mutex, NULL);
    pthread_cond_init(&monitor.not_full, NULL);
    pthread_cond_init(&monitor.not_empty, NULL);
}

void *producer(void *arg) {
    int id = *((int *)arg);
    int num_values = rand() % 6 + 5; // Generate 5 to 10 values
    printf("P%d: Producing %d values\n", id, num_values);
    
    active_producers++;

    for (int i = 0; i < num_values; i++) {
        int value = rand() % 10 + 1; // Generate random value between 1 and 10
        
        pthread_mutex_lock(&monitor.mutex);
        while (monitor.count >= monitor.buffer_size) {
            printf("P%d: Blocked due to full buffer\n", id);
            pthread_cond_wait(&monitor.not_full, &monitor.mutex);
        }
        
        monitor.buffer[monitor.in] = value;
        printf("P%d: Writing %d to position %d\n", id, value, monitor.in);
        monitor.in = (monitor.in + 1) % monitor.buffer_size; // Wrap around if necessary
        monitor.count++;
        
        pthread_cond_signal(&monitor.not_empty); // Signal that buffer is not empty
        pthread_mutex_unlock(&monitor.mutex);
        
        usleep(rand() % 1000000); // Simulate some processing time
    }
    
    printf("P%d: Exiting\n", id);

    pthread_mutex_lock(&monitor.mutex);
    active_producers--;
    producers_exited = (active_producers == 0);
    pthread_mutex_unlock(&monitor.mutex);
    
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int id = *((int *)arg);
    int total_values = *((int *)arg + 1);
    int num_consumers = *((int *)arg + 2);
    
    int values_per_consumer = total_values / num_consumers;
    int extra_values = total_values % num_consumers;
    
    int num_values = values_per_consumer;
    if (id < extra_values) {
        num_values++; // Each consumer thread beyond the first 'extra_values' should consume one more value
    }
    
    printf("C%d: Consuming %d values\n", id, num_values);
    
    while (1) {
        pthread_mutex_lock(&monitor.mutex);
        while (monitor.count <= 0 && !(producers_exited && monitor.count == 0)) {
            printf("C%d: Blocked due to empty buffer or producers still active\n", id);
            pthread_cond_wait(&monitor.not_empty, &monitor.mutex);
        }
        
        if (monitor.count <= 0 && producers_exited && monitor.count == 0) {
            pthread_mutex_unlock(&monitor.mutex);
            break; // Exit if producers have exited and buffer is empty
        }
        
        int value = monitor.buffer[monitor.out];
        printf("C%d: Reading %d from position %d\n", id, value, monitor.out);
        monitor.out = (monitor.out + 1) % monitor.buffer_size; // Wrap around if necessary
        monitor.count--;
        
        pthread_cond_signal(&monitor.not_full); // Signal that buffer is not full
        pthread_mutex_unlock(&monitor.mutex);
        
        usleep(rand() % 1000000); // Simulate some processing time
    }
    
    printf("C%d: Exiting\n", id);
    pthread_exit(NULL);
}
