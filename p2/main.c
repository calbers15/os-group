#include "prod_cons_MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    int total_values;
    int num_consumers;
} ConsumerArgs;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <buffer_size> <num_producers> <num_consumers>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    init_monitor(buffer_size);

    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    printf("Main: started %d producer threads\n", num_producers);
    for (int i = 0; i < num_producers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        printf("Main: started producer %d\n", i);
        pthread_create(&producers[i], NULL, producer, (void *)id);
    }

    printf("Main: started %d consumer threads\n", num_consumers);
    for (int i = 0; i < num_consumers; i++) {
        ConsumerArgs *args = malloc(sizeof(ConsumerArgs));
        args->id = i;
        args->total_values = num_producers * (rand() % 6 + 5); // Total number of values
        args->num_consumers = num_consumers;
        printf("Main: started consumer %d\n", i);
        pthread_create(&consumers[i], NULL, consumer, (void *)args);
    }

    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
        printf("Main: producer %d joined\n", i);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
        printf("Main: consumer %d joined\n", i);
    }

    printf("Main: program completed\n");

    return 0;
}
