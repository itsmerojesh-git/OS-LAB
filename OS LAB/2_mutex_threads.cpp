
//Write a program to avoid the race condition in Critical Section.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

// Shared variable
int shared_counter = 0;

// Mutex for synchronizing access to the critical section
pthread_mutex_t mutex;

void* increment_counter(void* arg) {
for (int i = 0; i < 10; ++i) {
// Lock the mutex before entering the critical section
pthread_mutex_lock(&mutex);

// Critical section
int temp = shared_counter;
printf("Thread %d: Joining the Critical section\n", *(int*)arg);
shared_counter = temp + 1;
printf("Thread %d: Going to leave Critical section\n", *(int*)arg);

// Unlock the mutex after leaving the critical section
pthread_mutex_unlock(&mutex);

// Simulate some work outside the critical section
sleep(1);
}
return NULL;
}

int main() {
pthread_t threads[NUM_THREADS];
int thread_ids[NUM_THREADS] = {0, 1};

// Initialize the mutex
pthread_mutex_init(&mutex, NULL);

// Create threads
for (int i = 0; i < NUM_THREADS; ++i) {
pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
}

// Wait for all threads to finish
for (int i = 0; i < NUM_THREADS; ++i) {
pthread_join(threads[i], NULL);
}

// Destroy the mutex
pthread_mutex_destroy(&mutex);

return 0;
}


