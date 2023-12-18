/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:48 by jaehejun          #+#    #+#             */
/*   Updated: 2023/11/21 14:53:53 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

//void	*t_function(void *data)
//{
//	int	id;
//	int	i = 0;
//	id = *((int *)data);

//	while (1)
//	{
//		printf("%d : %d\n", id, i);
//		i++;
//		sleep(1);
//	}
//}

//int	main(void)
//{
//	pthread_t	p_thread[2];
//	int	t_id;
//	int	status;
//	int	a = 1;
//	int	b = 2;
	
//	t_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
//	if (t_id < 0)
//	{
//		perror("thread create error: ");
//		exit(0);
//	}
//	t_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
//	if (t_id < 0)
//	{
//		perror("thread create error: ");
//		exit(0);
//	}
//	pthread_join(p_thread[0], (void **)&status);
//	pthread_join(p_thread[1], (void **)&status);
//	return 0;
//}


//void	*thread_function(void *data)
//{
//	int	*num = (int *)data;
//	int	*ret = malloc(sizeof(int));

//	printf("Num: %d\n", *num);
//	sleep(1);
//	*ret = *num * *num;
//	printf("thread function end\n");
//	return (ret);
//}

//int	main(void)
//{
//	pthread_mutex_t	fork;
//	pthread_t	philo;
//	int	thr_id;
//	int	result;
//	int	a = 200;

//	thr_id = pthread_create(&philo, NULL, thread_function, (void *)&a);
//	if (thr_id < 0)
//	{
//		perror("thread create error");
//		exit(0);
//	}
//	pthread_join(philo, (void *)&result);
//	printf("thread join: %d\n", result);
//	printf("Main() 종료\n");
//	return 0;
//}

//pthread_t		tid[2];
//int				counter;
//pthread_mutex_t	fork1;

//void	*trythis(void *arg)
//{
//	(void)arg;
//	pthread_mutex_lock(&fork1);
	
//	unsigned long	i = 0;
//	counter += 1;
//	printf("\n Job %d has started\n", counter);
//	for (i = 0; i < 1000; i++)
//		;
//	printf("\n Job %d has finished\n", counter);
//	pthread_mutex_unlock(&fork1);
//	return NULL;
//}

//int	main(void)
//{
//	int	i = 0;
//	int	error;

//	if (pthread_mutex_init(&fork1, NULL) != 0)
//	{
//		printf("\n mutex init has failed\n");
//		return 1;
//	}
//	while (i < 2)
//	{
//		error = pthread_create(&tid[i], NULL, &trythis, NULL);
//		if (error != 0)
//			printf("\nThread can't be created :[%s]", strerror(error));
//		i++;
//	}
//	pthread_join(tid[0], NULL);
//	pthread_join(tid[1], NULL);
//	pthread_mutex_destroy(&fork1);

//	return 0;
//}


pthread_mutex_t	forks[5];

void	eat(int philo_index)
{
	int	left = philo_index;
	int	right = (philo_index + 1) % 5;
	
	pthread_mutex_lock(&forks[left]);
	pthread_mutex_lock(&forks[right]);

	printf("Philo %d is eating...\n", philo_index);

	pthread_mutex_unlock(&forks[left]);
	pthread_mutex_unlock(&forks[right]);
	
	printf("Philo %d finished eating\n", philo_index);
}

int	main(void)
{
	pthread_t	philo[5];
	int			i = 0;

	while (i < 5)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;

	while (i < 5)
	{
		pthread_create(&philo[i], NULL, (void* (*)(void*))eat, (void *)&i);
		i++;
	}
	i = 0;

	while (i < 5)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	i = 0;

	while (i < 5)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}

	return 0;
}