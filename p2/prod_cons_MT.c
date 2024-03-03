#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Monitor monitor;

void init_monitor() {
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
        while (monitor.count >= BUFFER_SIZE) {
            printf("P%d: Blocked due to full buffer\n", id);
            pthread_cond_wait(&monitor.not_full, &monitor.mutex);
        }
        
        monitor.buffer[monitor.in] = value;
        printf("P%d: Writing %d to position %d\n", id, value, monitor.in);
        monitor.in = (monitor.in + 1) % BUFFER_SIZE;
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
    int num_values = 0;
    int total_values = *((int *)arg + 1);
    int values_per_consumer = total_values / *((int *)arg + 2);
    int extra_values = total_values % *((int *)arg + 2);
    
    if (id == *((int *)arg + 2) - 1)
        num_values = values_per_consumer + extra_values;
    else
        num_values = values_per_consumer;
    
    printf("C%d: Consuming %d values\n", id, num_values);
    
    for (int i = 0; i < num_values; i++) {
        pthread_mutex_lock(&monitor.mutex);
        while (monitor.count <= 0) {
            printf("C%d: Blocked due to empty buffer\n", id);
            pthread_cond_wait(&monitor.not_empty, &monitor.mutex);
        }
        
        int value = monitor.buffer[monitor.out];
        printf("C%d: Reading %d from position %d\n", id, value, monitor.out);
        monitor.out = (monitor.out + 1) % BUFFER_SIZE;
        monitor.count--;
        
        pthread_cond_signal(&monitor.not_full);
        pthread_mutex_unlock(&monitor.mutex);
        
        usleep(rand() % 1000000); // Simulate some processing time
    }
    
    printf("C%d: Exiting\n", id);
    pthread_exit(NULL);
}
