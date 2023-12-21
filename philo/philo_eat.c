/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:50 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 19:00:44 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->right]);
	philo->arg->fork_state[philo->left] = 1;
	philo->arg->fork_state[philo->right] = 1;
	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		philo_return_fork(philo);
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, TAKE);
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, TAKE);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	return (CONTINUE);
}

void	philo_return_fork(t_philo *philo)
{
	philo->arg->fork_state[philo->right] = 0;
	philo->arg->fork_state[philo->left] = 0;
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
}

static int	take_time_for_eat(long eat_time, t_philo *philo)
{
	while (get_time() < eat_time)
	{
		if (check_is_over(philo) == OVER)
		{
			philo_return_fork(philo);
			return (OVER);
		}
		usleep(200);
	}
	return (CONTINUE);
}

int	philo_eat(t_philo *philo)
{
	long	eat_time;

	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		philo_return_fork(philo);
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, EAT);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	eat_time = philo->last_eat + philo->arg->time_to_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (take_time_for_eat(eat_time, philo) == OVER)
		return (OVER);
	philo_count_eat(philo);
	return (CONTINUE);
}

void	philo_count_eat(t_philo *philo)
{
	philo->eat_count++;
	if (philo->eat_count == philo->arg->num_must_eat)
	{
		pthread_mutex_lock(&philo->arg->full_mutex);
		philo->arg->full++;
		pthread_mutex_unlock(&philo->arg->full_mutex);
	}
}
