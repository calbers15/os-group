#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Monitor monitor;

void init_monitor(int buffer_size) {
    monitor.buffer_size = buffer_size;
    monitor.buffer = malloc(buffer_size * sizeof(int));
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
    
    for (int i = 0; i < num_values; i++) {
        int value = rand() % 10 + 1; // Generate random value between 1 and 10
        
        pthread_mutex_lock(&monitor.mutex);
        while (monitor.count >= monitor.buffer_size) {
            printf("P%d: Blocked due to full buffer\n", id);
            pthread_cond_wait(&monitor.not_full, &monitor.mutex);
        }
        
        monitor.buffer[monitor.in] = value;
        printf("P%d: Writing %d to position %d\n", id, value, monitor.in);
        monitor.in = (monitor.in + 1) % monitor.buffer_size;
        monitor.count++;
        
        pthread_cond_signal(&monitor.not_empty);
        pthread_mutex_unlock(&monitor.mutex);
        
        usleep(rand() % 1000000); // Simulate some processing time
    }
    
    printf("P%d: Exiting\n", id);
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
    
    for (int i = 0; i < num_values; i++) {
        pthread_mutex_lock(&monitor.mutex);
        while (monitor.count <= 0) {
            printf("C%d: Blocked due to empty buffer\n", id);
            pthread_cond_wait(&monitor.not_empty, &monitor.mutex);
        }
        
        int value = monitor.buffer[monitor.out];
        printf("C%d: Reading %d from position %d\n", id, value, monitor.out);
        monitor.out = (monitor.out + 1) % monitor.buffer_size; // Wrap around if necessary
        monitor.count--;
        
        pthread_cond_signal(&monitor.not_full);
        pthread_mutex_unlock(&monitor.mutex);
        
        usleep(rand() % 1000000); // Simulate some processing time
    }
    
    printf("C%d: Exiting\n", id);
    pthread_exit(NULL);
}
