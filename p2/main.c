//Cameron Albers & Austin Silva
//EECE.4811 - Operating Systems
//Michael J. Geiger, Yongshun Xu
//Project 2 - Multithreading

#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(int argc, char *argv[]){
    //error checking
    if(argc != 4){
        printf("Usage: %s <num_producers> <num_consumers> <buffer_size>\n", argv[0]);
        return 1;
    }

    //input formatting
    int numProducers = atoi(argv[1]);
    int numConsumers = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);

    //create array of pthread_t producers and consumers of size numProducers and numConsumers
    pthread_t producer_threads[numProducers];
    pthread_t consumer_threads[numConsumers];

    //initialize Monitor m
    Monitor m;
    init_monitor(&m, bufferSize, numProducers, numConsumers);

    //may not be necessary? keep here in case whole thing breaks :)
    srand(time(0));

    //for loops creating producers and consumers, calling producer and consumer functions prototyped in .h and defined in .c
    for(int i = 0; i < numProducers; i++){
        printf("Creating producer thread P%d\n", i);
        pthread_create(&producer_threads[i], NULL, producer, (void *)&m);
    }

    for(int i = 0; i < numConsumers; i++){
        printf("Creating consumer thread C%d\n", i);
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)&m);
    }


    //join threads once producers & consumers are finished
    for (int i = 0; i < numProducers; i++){
        pthread_join(producer_threads[i], NULL);
        printf("Producer thread P%d joined\n", i);
    }

    for (int i = 0; i < numConsumers; i++){
        pthread_join(consumer_threads[i], NULL);
        printf("Consumer thread C%d joined\n", i);
    }

    //deallocate memory space
    destroy_monitor(&m);

    printf("Program Complete\n");


    return 0;
}
