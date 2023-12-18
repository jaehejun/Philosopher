#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>


//#define NUM_THREADS 4
//#define NUM_RESOURCES 4

//typedef struct {
//    int id;
//	int	*shared;
//    pthread_mutex_t* resources;
//} ThreadData;

//void* threadFunc(void* arg)
//{
//    ThreadData* data = (ThreadData*)arg;
//    int first_resource = data->id % NUM_RESOURCES;
//    int second_resource = (data->id + 1) % NUM_RESOURCES;

//	if (data->id % 2 == 1)
//		sleep(1);
//    pthread_mutex_lock(&data->resources[first_resource]);
//    printf("Thread %d locked resource %d\n", data->id, first_resource);

//    pthread_mutex_lock(&data->resources[second_resource]);
//    printf("Thread %d locked resource %d\n", data->id, second_resource);


//	data->shared[first_resource] += 1;
//	data->shared[second_resource] += 1;
//    printf("Thread %d is using resources %d and %d\n", data->id, first_resource, second_resource);

//    pthread_mutex_unlock(&data->resources[first_resource]);
//    printf("Thread %d unlocked resource %d\n", data->id, first_resource);

//    pthread_mutex_unlock(&data->resources[second_resource]);
//    printf("Thread %d unlocked resource %d\n", data->id, second_resource);

//    return NULL;
//}

//int main(void)
//{
//    pthread_t threads[NUM_THREADS];
//    pthread_mutex_t resources[NUM_RESOURCES];
//	int	shared[NUM_RESOURCES] = {0};
//    ThreadData threadData[NUM_THREADS];

//    for (int i = 0; i < NUM_RESOURCES; i++)
//	{
//        pthread_mutex_init(&resources[i], NULL);
//    }

//    for (int i = 0; i < NUM_THREADS; i++)
//	{
//        threadData[i].id = i;
//		threadData[i].shared = shared;
//        threadData[i].resources = resources;
//        pthread_create(&threads[i], NULL, threadFunc, &threadData[i]);
//    }

//    for (int i = 0; i < NUM_THREADS; i++)
//	{
//        pthread_join(threads[i], NULL);
//    }

//    for (int i = 0; i < NUM_RESOURCES; i++)
//	{
//        pthread_mutex_destroy(&resources[i]);
//    }

//	for (int i = 0; i < NUM_RESOURCES; i++)
//		printf("shared[%d]: %d\n", i, threadData[i].shared[i]);

//    return 0;
//}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
	int				id;
	int				num_must_eat;
	int				num_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*status;
	int				*philosophers_status;
	pthread_mutex_t	*print_mutex;
	long			start_time;
} Philosopher;

long get_time_in_milliseconds()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(int id, const char* action, long start_time, pthread_mutex_t* print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("%ld philo[%d] %s\n", get_time_in_milliseconds() - start_time, id, action);
	pthread_mutex_unlock(print_mutex);
}

void* philosopher_func(void *arg)
{
	Philosopher	*philosopher = (Philosopher*)arg;
	int	left_fork = philosopher->id;
	int	right_fork = (philosopher->id + 1) % philosopher->num_must_eat;

	while (1)
	{
		pthread_mutex_lock(&philosopher->forks[left_fork]);
		pthread_mutex_lock(&philosopher->forks[right_fork]);
		print_status(philosopher->id, "has taken a fork", philosopher->start_time, philosopher->print_mutex);

		print_status(philosopher->id, "is eating", philosopher->start_time, philosopher->print_mutex);
		usleep(philosopher->time_to_eat * 1000);

		pthread_mutex_unlock(&philosopher->forks[left_fork]);
		pthread_mutex_unlock(&philosopher->forks[right_fork]);

		philosopher->num_eaten++;

		if (philosopher->num_eaten >= philosopher->num_must_eat)
		{
			pthread_mutex_lock(&philosopher->status[philosopher->id]);
			philosopher->philosophers_status[philosopher->id] = 1;
			pthread_mutex_unlock(&philosopher->status[philosopher->id]);
			break;
		}

		print_status(philosopher->id, "is sleeping", philosopher->start_time, philosopher->print_mutex);

		usleep(philosopher->time_to_sleep * 1000);

		print_status(philosopher->id, "is thinking", philosopher->start_time, philosopher->print_mutex);
	}

	print_status(philosopher->id, "died", philosopher->start_time, philosopher->print_mutex);

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 6) {
		printf("ERROR!\n");
		return 1;
	}

	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int num_must_eat = atoi(argv[5]);

	pthread_t *philosophers = malloc(sizeof(pthread_t) * num_philosophers);
	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);
	pthread_mutex_t *status = malloc(sizeof(pthread_mutex_t) * num_philosophers);
	int *philosophers_status = calloc(num_philosophers, sizeof(int));
	pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	Philosopher *philosopher_data = malloc(sizeof(Philosopher) * num_philosophers);

	long start_time = get_time_in_milliseconds(); // 기준 시간 설정

	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&status[i], NULL);
	}

	for (int i = 0; i < num_philosophers; i++)
	{
		philosopher_data[i].id = i;
		philosopher_data[i].num_must_eat = num_must_eat;
		philosopher_data[i].num_eaten = 0;
		philosopher_data[i].time_to_die = time_to_die;
		philosopher_data[i].time_to_eat = time_to_eat;
		philosopher_data[i].time_to_sleep = time_to_sleep;
		philosopher_data[i].forks = forks;
		philosopher_data[i].status = status;
		philosopher_data[i].philosophers_status = philosophers_status;
		philosopher_data[i].print_mutex = &print_mutex;
		philosopher_data[i].start_time = start_time;
		pthread_create(&philosophers[i], NULL, philosopher_func, &philosopher_data[i]);
	}

	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_join(philosophers[i], NULL);
	}

	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&status[i]);
	}

	free(philosophers);
	free(forks);
	free(status);
	free(philosophers_status);
	free(philosopher_data);

	return 0;
}
