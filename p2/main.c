#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(int argc, char *argv[]){
    
    if(argc != 4){
        printf("Usage: %s <num_producers> <num_consumers> <buffer_size>\n", argv[0]);
        return 1;
    }

    int numProducers = atoi(argv[1]);
    int numConsumers = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);

    pthread_t producer_threads[numProducers];
    pthread_t consumer_threads[numConsumers];

    Monitor m;
    init_monitor(&m, bufferSize, numProducers, numConsumers);

    srand(time(0));

    for(int i = 0; i < numProducers; i++){
        printf("Creating producer thread P%d\n", i);
        pthread_create(&producer_threads[i], NULL, producer, (void *)&m);
    }

    for(int i = 0; i < numConsumers; i++){
        printf("Creating consumer thread C%d\n", i);
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)&m);
    }

    for (int i = 0; i < numProducers; i++){
        pthread_join(producer_threads[i], NULL);
        printf("Producer thread P%d joined\n", i);
    }

    for (int i = 0; i < numConsumers; i++){
        pthread_join(consumer_threads[i], NULL);
        printf("Consumer thread C%d joined\n", i);
    }

    destroy_monitor(&m);

    printf("Program Complete\n");


    return 0;
}
