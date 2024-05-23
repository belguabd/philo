#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int NUM_PHILOSOPHERS;
int TIME_TO_DIE;
int TIME_TO_EAT;
int TIME_TO_SLEEP;

pthread_mutex_t *forks;
pthread_t *philosophers;
pthread_t monitor_thread;
time_t *last_meal_times;
int *is_dead;
int keep_running = 1;

void *philosopher(void *num);
void *monitor(void *args);
void think(int id);
void eat(int id);
void sleep_philosopher(int id);

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
        return 1;
    }

    NUM_PHILOSOPHERS = atoi(argv[1]);
    TIME_TO_DIE = atoi(argv[2]);
    TIME_TO_EAT = atoi(argv[3]);
    TIME_TO_SLEEP = atoi(argv[4]);

    forks = malloc(NUM_PHILOSOPHERS * sizeof(pthread_mutex_t));
    philosophers = malloc(NUM_PHILOSOPHERS * sizeof(pthread_t));
    last_meal_times = malloc(NUM_PHILOSOPHERS * sizeof(time_t));
    is_dead = malloc(NUM_PHILOSOPHERS * sizeof(int));

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        last_meal_times[i] = time(NULL);
        is_dead[i] = 0;
    }

    pthread_create(&monitor_thread, NULL, monitor, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    keep_running = 0;
    pthread_join(monitor_thread, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    free(forks);
    free(philosophers);
    free(last_meal_times);
    free(is_dead);

    return 0;
}

void *philosopher(void *num)
{
    int id = *(int *)num;
    free(num);

    while (1)
    {
        if (is_dead[id])
        {
            pthread_exit(NULL);
        }

        think(id);

        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;

        // Picking up forks
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        eat(id);
        last_meal_times[id] = time(NULL); // Update last meal time

        // Putting down forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);

        sleep_philosopher(id);
    }
}

void *monitor(void *args)
{
    while (keep_running)
    {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        {
            if (!is_dead[i] && time(NULL) - last_meal_times[i] > TIME_TO_DIE)
            {
                printf("Philosopher %d has died of starvation.\n", i);
                is_dead[i] = 1;
            }
        }
        usleep(100000); // Sleep for 100 milliseconds
    }
    return NULL;
}

void think(int id)
{
    printf("Philosopher %d is thinking.\n", id);
    sleep(TIME_TO_EAT); // Simulate thinking time
}

void eat(int id)
{
    printf("Philosopher %d is eating.\n", id);
    sleep(TIME_TO_EAT); // Simulate eating time
}

void sleep_philosopher(int id)
{
    printf("Philosopher %d is sleeping.\n", id);
    sleep(TIME_TO_SLEEP); // Simulate sleeping time
}
