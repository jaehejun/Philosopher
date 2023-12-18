/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:17:57 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 22:25:59 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*philo_routine(t_thread *philo)
{
	pthread_mutex_lock(&philo->share->start_mutex);
	pthread_mutex_unlock(&philo->share->start_mutex);

	if (philo->philo_id % 2 == 1)
		usleep(200);
	while (1)
	{
		if (philo->eat_count < philo->share->num_must_eat || philo->share->num_must_eat == -1)
		philo_eat(philo);
		//else
		//{
		//	pthread_mutex_lock(&philo->share->mutex);
		//	philo->share->full++;
		//	pthread_mutex_unlock(&philo->share->mutex);
		//}

		//if (need_to_stop(philo->share) == 1)
		//	return (NULL);

		//pthread_mutex_lock(&philo->share->mutex);
		printf("%ld %d %s\n", get_time() - philo->share->start_time, philo->philo_id, "is sleeping");
		//pthread_mutex_unlock(&philo->share->mutex);
		usleep(1000 * philo->share->time_to_sleep);

		//if (need_to_stop(philo->share) == 1)
		//	return (NULL);

		//pthread_mutex_lock(&philo->share->mutex);
		printf("%ld %d %s\n", get_time() - philo->share->start_time, philo->philo_id, "is thinking");
		//pthread_mutex_unlock(&philo->share->mutex);
		usleep(100);
		
		//if (need_to_stop(philo->share) == 1)
		//	return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_arg		*share;
	t_thread	*philo;
	int			p_cnt;
	int			join_cnt;
	int			destroy_cnt;

	if (argc < 5 || argc > 6)
	{
		printf("Unvalid parameters\n");
		return (0);
	}

	share = malloc(sizeof(t_arg));
	init_args(share, argv);
	philo = malloc(sizeof(t_thread) * share->philo_num);
	init_philo(share, philo);

	pthread_mutex_lock(&share->start_mutex);
	p_cnt = 0;
	while (p_cnt < share->philo_num)
	{
		pthread_create(&philo[p_cnt].thread, NULL, (void *)philo_routine, &philo[p_cnt]);
		p_cnt++;
	}
	pthread_mutex_unlock(&share->start_mutex);
	
	
	//monitoring(share, philo);
	
	join_cnt = 0;
	while (join_cnt < share->philo_num)
	{
		pthread_join(philo[join_cnt].thread, NULL);
		join_cnt++;
	}

	pthread_mutex_destroy(&share->mutex);
	
	destroy_cnt = 0;
	while (destroy_cnt < share->philo_num)
	{
		pthread_mutex_destroy(&share->fork_mutex[destroy_cnt]);
		destroy_cnt++;
	}
	return (0);
}
