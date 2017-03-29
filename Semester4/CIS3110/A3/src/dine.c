/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "stringy.h"

pthread_mutex_t lock;
int sharedResource, first, iterations;

void think(int id) {
    printf("philosopher %d is thinking...\n", id);
}

void eat(int id) {
    printf("philosopher %d is eating...\n", id);
}

/**
 * delegate
 * Assign the philosophers one of their two possible states: thinking or eating.
 *
 * IN: (void*) the properties struct.
 * RETURN: (void*) thread wanted it?
 * NOTE: (void*) can be cast to properties.
 **/
void* delegate(void* obj) {
    int phil = (intptr_t)obj, it = 0;

    /* Repeat for the given number of iterations */
    while (it < iterations) {
        /* Think while waiting for forks */
        think(phil);
        while (1) {
            /* Try locking the pile of forks on success -- get forks */
            if (pthread_mutex_trylock(&lock) == 0) {
                while (1) {
                    if (sharedResource > 1) {
                        sharedResource -= 2;
                        break;
                    }
                }
                /* Return access to the stack of forks */
                pthread_mutex_unlock(&lock);
                eat(phil);
                break;
            }
        }
        /* Eat for a bit */
        srand(time(NULL));
        sleep(rand() % 2);
        /* Put the forks back */
        sharedResource += 2;
        it++;
    }
    think(phil);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) printError("Format: ./dine [ num_philosophers ] [ num_of_times ]",1);

    /* Set the values */
    int numPhilosophers = atoi(argv[1]);
    sharedResource = numPhilosophers;
    pthread_t tid[numPhilosophers];
    iterations = atoi(argv[2]);

    /* Quit if we're given garbage values */
    if (numPhilosophers < 2 || iterations > 1000 || iterations < 1 ) printError("num_philosophers(2 or more) num_of_times(1-1000)",1);

    /* Init the mutx lock and unlock */
    if (pthread_mutex_init(&lock, NULL) != 0) printError("Mutex failed", 1);

    /* Create a thread for each philosopher */
    for (size_t i = 1; i <= numPhilosophers; i++) {
        /* Create the thread send the philosophers information */
        if (pthread_create(&(tid[i]), NULL, &delegate, (void*)(intptr_t)i) != 0) printError("Thread creation failed!", 1);
    }

    /* Wait for the threads */
    for (size_t i = 1; i <= numPhilosophers; i++) pthread_join(tid[i], NULL);

    /* Clean up mutex */
    pthread_mutex_destroy(&lock);

    return 0;
}
