/*******************************
Kevin Pirabaharan
kpirabah@mail.uoguelph.ca
This program solves the dinning philosophers problem
*******************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int numPhilosophers = 0;
int numTimesEaten = 0;

typedef struct
{
    int position;
    int count;
    sem_t *forks;
    sem_t *lock;
} params_t;

void initialize_semaphores(sem_t *lock, sem_t *forks, int timesForked, pthread_t *threads, int numPhilosophers);
void *philosopher(void *params);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("UNSUCCESSFUL EXECUTION\n");
        printf("Arguments should be 'Program inputFile'\n");
        printf("Program requires 2 arguements, you inputted %d!\n", argc);

        if (argc > 3)
        {
            argc = argc - 3;
            printf("You have %d too many arguments, get rid of them\n", argc);
            return 1;
        }
        else
        {
            printf("You are missing the inputs in your argument(s), please add it.\n");
            return 1;
        }
    }
    numPhilosophers = atoi(argv[1]);
    numTimesEaten = atoi(argv[2]);
    sem_t lock;
    sem_t forks[numPhilosophers];
    pthread_t philosophers[numPhilosophers];
    initialize_semaphores(&lock, forks, numPhilosophers, philosophers, numPhilosophers);
    pthread_exit(NULL);
}

void initialize_semaphores(sem_t *lock, sem_t *forks, int timesForked, pthread_t *threads, int numPhilosophers)
{
    for (int i = 0; i < timesForked; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(lock, 0, timesForked - 1);
    for (int i = 0; i < numPhilosophers; i++)
    {
        params_t *arg = malloc(sizeof(params_t));
        arg->position = i;
        arg->count = numPhilosophers;
        arg->lock = lock;
        arg->forks = forks;
        pthread_create(&threads[i], NULL, philosopher, (void *)arg);
    }
}

void *philosopher(void *params)
{
    params_t self = *(params_t *)params;
    for (int i = 0; i < numTimesEaten; i++)
    {
        printf("Philosopher %d thinking...\n", self.position + 1);
        sem_wait(self.lock);
        sem_wait(&self.forks[self.position]);
        sem_wait(&self.forks[(self.position + 1) % self.count]);
        printf("Philosopher %d eating...\n", self.position + 1);
        sem_post(&self.forks[self.position]);
        sem_post(&self.forks[(self.position + 1) % self.count]);
        sem_post(self.lock);
    }
    printf("Philosopher %d thinking...\n", self.position + 1);
    pthread_exit(NULL);
}
