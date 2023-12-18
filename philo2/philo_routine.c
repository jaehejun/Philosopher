/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:27:41 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 19:22:47 by jaehejun         ###   ########.fr       */
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

int	philo_get_fork(t_philo *philo)
{
	if (check_is_over(philo) == OVER)
		return (OVER);
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->right]);
	philo->arg->fork_state[philo->left] = 1;
	philo->arg->fork_state[philo->right] = 1;
	if (check_is_over(philo) == OVER)
	{
		philo_return_fork(philo);
		return (OVER);
	}
	print_action(philo, get_time() - philo->arg->start_time, \
				"has taken a fork");
	print_action(philo, get_time() - philo->arg->start_time, \
				"has taken a fork");
	return (CONTINUE);
}

void	philo_return_fork(t_philo *philo)
{
	philo->arg->fork_state[philo->right] = 0;
	philo->arg->fork_state[philo->left] = 0;
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
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

int	philo_eat(t_philo *philo)
{
	long	eat_time;

	if (check_is_over(philo) == OVER)
	{
		philo_return_fork(philo);
		return (OVER);
	}
	print_action(philo, get_time() - philo->arg->start_time, \
				"is eating");
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	eat_time = philo->last_eat + philo->arg->time_to_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	while (get_time() < eat_time)
	{
		if (check_is_over(philo) == OVER)
		{
			philo_return_fork(philo);
			return (OVER);
		}
		usleep(500);
	}
	philo_count_eat(philo);
	return (CONTINUE);
}

int	philo_sleep(t_philo *philo)
{
	long	sleep_time;

	if (check_is_over(philo) == OVER)
		return (OVER);
	print_action(philo, get_time() - philo->arg->start_time, \
				"is sleeping");
	sleep_time = get_time() + philo->arg->time_to_sleep;
	while (get_time() < sleep_time)
	{
		if (check_is_over(philo) == OVER)
			return (OVER);
		usleep(500);
	}
	return (CONTINUE);
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d is thinking\n", get_time() - philo->arg->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	return (CONTINUE);
}

void	philo_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
	philo->arg->fork_state[philo->left] = 1;
	print_action(philo, get_time() - philo->arg->start_time, \
				"has taken a fork");
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
		usleep(200);
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

