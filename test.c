/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:15:26 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/06 19:51:58 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

//int	cnt;
//pthread_mutex_t	mutex;

//void	*count(void *arg)
//{
//	int		i;
//	char	*name;

//	name = (char *)arg;
//	i = 0;
	
//	pthread_mutex_lock(&mutex);
	
//	cnt = 0;
//	while (i < 10)
//	{
//		printf("%s cnt: %d\n", name, cnt);
//		cnt++;
//		i++;
//	}

//	pthread_mutex_unlock(&mutex);
//	return NULL;
//}

//int	main(void)
//{
//	pthread_t	thread[2];

//	pthread_mutex_init(&mutex, NULL);

//	pthread_create(&thread[0], NULL, count, (void *)"thread1");
//	pthread_create(&thread[1], NULL, count, (void *)"thread2");
	
//	pthread_join(thread[0], NULL);
//	pthread_join(thread[1], NULL);

//	pthread_mutex_destroy(&mutex);
//}

//int	sum;

//void	*runner(void *param)
//{
//	int	i = 1;
//	int	upper = atoi(param);

//	sum = 0;
//	printf("upper: %d\n", upper);
//	while (i <= upper)
//	{
//		sum += i;
//		i++;
//	}
//	pthread_exit(0);
//}

//int	main(int argc, char *argv[])
//{
//	pthread_t	tid;
//	pthread_attr_t	attr;

//	(void)argc;
//	pthread_attr_init(&attr);
//	pthread_create(&tid, &attr, runner, argv[1]);
//	pthread_join(tid, NULL);

//	printf("sum = %d\n", sum);
//}


//pthread_mutex_t	mutex;

//void	*routine(int *arg)
//{
	
//	pthread_mutex_lock(&mutex);
	
//	(*arg)++;
//	printf("SHARED: %d\n", *arg);
	
//	pthread_mutex_unlock(&mutex);
//	return NULL;
//}

//int	main(void)
//{
//	pthread_t	thread1;
//	pthread_t	thread2;
//	pthread_t	thread3;
//	pthread_t	thread4;
//	pthread_t	thread5;
//	int			shared_resource = 0;

//	pthread_mutex_init(&mutex, NULL);
	
//	pthread_create(&thread1, NULL, (void *)routine, &shared_resource);
//	pthread_create(&thread2, NULL, (void *)routine, &shared_resource);
//	pthread_create(&thread3, NULL, (void *)routine, &shared_resource);
//	pthread_create(&thread4, NULL, (void *)routine, &shared_resource);
//	pthread_create(&thread5, NULL, (void *)routine, &shared_resource);
	
//	pthread_join(thread1, NULL);
//	pthread_join(thread2, NULL);
//	pthread_join(thread3, NULL);
//	pthread_join(thread4, NULL);
//	pthread_join(thread5, NULL);

//	pthread_mutex_destroy(&mutex);
//	return 0;
//}

//typedef struct{
//	int	*forks;
//	pthread_mutex_t	*mutex;
//} t_arg;

//void	*thread_func(void *param)
//{
//	t_arg	*args = (t_arg *)param;

//	pthread_mutex_lock(t_arg->mutex);

//	printf("TID: %lu, shared: %d\n", pthread_self(), *(t_arg->shared));

//	pthread_mutex_unlock(t_arg->mutex);

//	return NULL;
//}

//int	main(void)
//{
//	int	*shared_resource = (int *)malloc(sizeof(int));
//	*shared_resource = 0;

//	pthread_mutex_t	mutex;

//	pthread_mutex_init(&mutex, NULL);

//	pthread_t	thread1, thread2;

//	t_arg	args = {shared_resource, &mutex};

//	pthread_create(&thread1, NULL, thread_func, &args);
//	pthread_create(&thread2, NULL, thread_func, &args);

//	pthread_join(thread1, NULL);
//	ptherad_join(thread2, NULL);

//	pthead_mutex_destroy(&mutex);

//	free(shared_resource);

//	return 0;
//}

//int	main(void)
//{
//	struct timeval	start;
//	struct timeval	now;

//	long			passed;
	
//	gettimeofday(&start, NULL);
//	printf("초 : %ld\n", start.tv_sec);
//	printf("마이크로초 : %d\n", start.tv_usec);

//	usleep(1000000);
//	gettimeofday(&now, NULL);
//	passed = (now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000);
//	printf("passed: %ld\n", passed);

//	usleep(1000000);
//	gettimeofday(&now, NULL);
//	passed = (now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000);
//	printf("passed: %ld\n", passed);

//	usleep(1000000);
//	gettimeofday(&now, NULL);
//	passed = (now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000);
//	printf("passed: %ld\n", passed);
//	return 0;
//}

typedef struct s_share
{
	pthread_mutex_t	fork_mutex[10];
	int	fork_state[10];
	long	start_time;
}	t_share;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	int	count;
	t_share	*share;
}	t_philo;

void	*philo_routine(void *arg)
{
	struct timeval	p_tv;
	long	timestamp;
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	while (philo->count < 3)
	{
		if (philo->id % 2 == 1)
			usleep(100000);

		gettimeofday(&p_tv, NULL);
		timestamp = p_tv.tv_sec * 1000 + p_tv.tv_usec / 1000 - philo->share->start_time;
		
		pthread_mutex_lock(&philo->share->fork_mutex[philo->id]);
		pthread_mutex_lock(&philo->share->fork_mutex[(philo->id + 1) % 10]);
		
		philo->share->fork_state[philo->id] = 1;
		philo->share->fork_state[(philo->id + 1) % 10] = 1;
		
		printf("%ld philo %d get fork[%d]\n", timestamp, philo->id, philo->id);
		printf("%ld philo %d get fork[%d]\n", timestamp, philo->id, (philo->id + 1) % 10);
	
		printf("%ld philo %d start EATING!\n", timestamp, philo->id);
		philo->count++;
		usleep(100000);
		
		philo->share->fork_state[philo->id] = 0;
		philo->share->fork_state[(philo->id + 1) % 10] = 0;
		
		pthread_mutex_unlock(&philo->share->fork_mutex[philo->id]);
		pthread_mutex_unlock(&philo->share->fork_mutex[(philo->id + 1) % 10]);
		
		printf("%ld philo %d return fork[%d]\n", timestamp, philo->id, philo->id);
		printf("%ld philo %d return fork[%d]\n", timestamp, philo->id, (philo->id + 1) % 10);
		usleep(1000);
		
	
	}
	return NULL;
}

//void	*philo_routine(void *arg)
//{
//	struct timeval	p_tv;
//	long	timestamp;
//	t_philo	*philo;

//	philo = (t_philo *)arg;
	
//	while (philo->count < 3)
//	{
//		// Get the id of left and right fork based on the id of philosopher
//		int left_fork = philo->id;
//		int right_fork = (philo->id + 1) % 10;

//		// Ensure that philosopher always pick up the lowest numbered fork first
//		if (philo->id % 2 == 0)
//		{
//			left_fork = (philo->id + 1) % 10;
//			right_fork = philo->id;
//		}

//		pthread_mutex_lock(&philo->share->fork_mutex[left_fork]);
//		pthread_mutex_lock(&philo->share->fork_mutex[right_fork]);
		
//		philo->share->fork_state[left_fork] = 1;
//		philo->share->fork_state[right_fork] = 1;
		
//		gettimeofday(&p_tv, NULL);
//		timestamp = p_tv.tv_sec * 1000 + p_tv.tv_usec / 1000 - philo->share->start_time;

//		//printf("%ld philo %d get fork[%d]\n", timestamp, philo->id, left_fork);
//		//printf("%ld philo %d get fork[%d]\n", timestamp, philo->id, right_fork);
	
//		printf("%ld philo %d start EATING!\n", timestamp, philo->id);
//		philo->count++;
//		usleep(100000);
		
//		philo->share->fork_state[left_fork] = 0;
//		philo->share->fork_state[right_fork] = 0;
		
//		pthread_mutex_unlock(&philo->share->fork_mutex[left_fork]);
//		pthread_mutex_unlock(&philo->share->fork_mutex[right_fork]);
		
//		//printf("%ld philo %d return fork[%d]\n", timestamp, philo->id, left_fork);
//		//printf("%ld philo %d return fork[%d]\n", timestamp, philo->id, right_fork);
//		usleep(1000);
//	}
//	return NULL;
//}


int	main(void)
{
	t_share	*arg;
	t_philo	*philo;
	struct timeval	tv;
	
	int		i;
	int		j;
	int		k;
	int		num;

	arg = (t_share *)malloc(sizeof(t_share) * 1);
	philo = (t_philo *)malloc(sizeof(t_philo) * 10);
	i = 0;
	while (i < 10)
	{
		pthread_mutex_init(&arg->fork_mutex[i], NULL);
		arg->fork_state[i] = 0;
		i++;
	}
	
	gettimeofday(&tv, NULL);
	arg->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->share = arg;

	num = 0;
	while (num < 10)
	{
		philo[num].id = num;
		philo[num].share = arg;
		philo[num].count = 0;
		num++;
	}

	j = 0;
	while (j < 10)
	{
		pthread_create(&philo[j].thread, NULL, (void *)philo_routine, &philo[j]);
		j++;
	}
	
	printf("Thread create!\n");
	
	k = 0;
	while (k < 10)
	{
		pthread_join(philo[k].thread, NULL);
		k++;
	}

	printf("Thread join!\n");
	
	i = 0;
	while (i < 10)
	{
		pthread_mutex_destroy(&arg->fork_mutex[i]);
		i++;
	}

	printf("Mutex delete!\n");
	return 0;
}