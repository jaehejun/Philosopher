/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:27:41 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 18:55:23 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_over(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->over_mutex);
	if (philo->arg->is_over == OVER)
	{
		pthread_mutex_unlock(&philo->arg->over_mutex);
		return (OVER);
	}
	pthread_mutex_unlock(&philo->arg->over_mutex);
	return (CONTINUE);
}

void	philo_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
	philo->arg->fork_state[philo->left] = 1;
	pthread_mutex_lock(&philo->arg->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, TAKE);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	philo->arg->fork_state[philo->left] = 0;
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(200);
	if (philo->arg->philo_num == 1)
	{
		philo_alone(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo_get_fork(philo) == OVER)
			break ;
		if (philo_eat(philo) == OVER)
			break ;
		philo_return_fork(philo);
		usleep(200);
		if (philo_sleep(philo) == OVER)
			break ;
		usleep(200);
		if (philo_think(philo) == OVER)
			break ;
		usleep(200);
	}
	return (NULL);
}
