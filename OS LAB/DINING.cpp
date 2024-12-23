#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS]; // Semaphore for each fork
sem_t room;                    // Semaphore to limit room access

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2 + 1); // Simulate thinking time

        // Request access to the dining room
        sem_wait(&room);

        // Pick up left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up fork %d (left).\n", id, id);

        // Pick up right fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up fork %d (right).\n", id, (id + 1) % NUM_PHILOSOPHERS);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2 + 1); // Simulate eating time

        // Put down right fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down fork %d (right).\n", id, (id + 1) % NUM_PHILOSOPHERS);

        // Put down left fork
        sem_post(&forks[id]);
        printf("Philosopher %d put down fork %d (left).\n", id, id);

        // Leave the dining room
        sem_post(&room);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&room, 0, NUM_PHILOSOPHERS - 1); // Limit to NUM_PHILOSOPHERS - 1 philosophers
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1); // Each fork starts as available
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (this is an infinite simulation, so it won't terminate)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&room);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

