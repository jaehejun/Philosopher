/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:27:41 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 16:47:05 by jaehejun         ###   ########.fr       */
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

int	philo_eat(t_philo *philo)
{
	long	eat_time;


	pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
		return (OVER);
	}

	pthread_mutex_lock(&philo->arg->fork_mutex[philo->right]);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
		return (OVER);
	}

	philo->arg->fork_state[philo->left] = 1;
	philo->arg->fork_state[philo->right] = 1;

	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
	printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d is eating\n", get_time() - philo->arg->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	eat_time = philo->last_eat + philo->arg->time_to_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	while (get_time() < eat_time)
	{
		if (check_is_over(philo) == OVER)
		{
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
			return (OVER);
		}
		usleep(500);
	}
	philo->arg->fork_state[philo->right] = 0;
	philo->arg->fork_state[philo->left] = 0;
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
	pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
	philo->eat_count++;
	if (philo->eat_count == philo->arg->num_must_eat)
	{
		pthread_mutex_lock(&philo->arg->full_mutex);
		philo->arg->full++;
		pthread_mutex_unlock(&philo->arg->full_mutex);
	}
	return (CONTINUE);
}

int	philo_sleep(t_philo *philo)
{
	long	sleep_time;

	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d is sleeping\n", get_time() - philo->arg->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->arg->print_mutex);
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

void	*philo_routine(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(200);
	if (philo->arg->philo_num == OVER)
	{
		pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
		pthread_mutex_lock(&philo->arg->print_mutex);
		printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->arg->print_mutex);
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
		return (NULL);
	}
	while (1)
	{
		if (philo_eat(philo) == OVER)
			break ;
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

@@@@@@@@@@@@original@@@@@@@@@@@@@@@@

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

void	*philo_routine(t_philo *philo)
{
	long	eat_time;
	long	sleep_time;

	if (philo->philo_id % 2 == 0)
		usleep(200);

	while (1)
	{
// eat

		if (philo->arg->philo_num == 1)
		{
			pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
			pthread_mutex_lock(&philo->arg->print_mutex);
			printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
			pthread_mutex_unlock(&philo->arg->print_mutex);
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			break ;
		}
		
		
		pthread_mutex_lock(&philo->arg->fork_mutex[philo->left]);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			break ;
		}
		
		pthread_mutex_lock(&philo->arg->fork_mutex[philo->right]);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
			break ;
		}
		
		philo->arg->fork_state[philo->left] = 1;
		philo->arg->fork_state[philo->right] = 1;
		
		pthread_mutex_lock(&philo->arg->print_mutex);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
			pthread_mutex_unlock(&philo->arg->print_mutex);
			break ;
		}
		printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
		printf("%ld %d has taken a fork\n", get_time() - philo->arg->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->arg->print_mutex);

		pthread_mutex_lock(&philo->arg->print_mutex);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
			pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
			pthread_mutex_unlock(&philo->arg->print_mutex);
			break ;
		}
		printf("%ld %d is eating\n", get_time() - philo->arg->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->arg->print_mutex);

		pthread_mutex_lock(&philo->last_eat_mutex);
		philo->last_eat = get_time();
		eat_time = philo->last_eat + philo->arg->time_to_eat;
		pthread_mutex_unlock(&philo->last_eat_mutex);

		while (get_time() < eat_time)
		{
			if (check_is_over(philo) == 1)
			{
				pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);
				pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
				break ;
			}
			usleep(500);
		}

		philo->arg->fork_state[philo->right] = 0;
		philo->arg->fork_state[philo->left] = 0;
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->right]);
		pthread_mutex_unlock(&philo->arg->fork_mutex[philo->left]);

		philo->eat_count++;
		if (philo->eat_count == philo->arg->num_must_eat)
		{
			pthread_mutex_lock(&philo->arg->full_mutex);
			philo->arg->full++;
			pthread_mutex_unlock(&philo->arg->full_mutex);
		}

// sleep

		usleep(200);

		pthread_mutex_lock(&philo->arg->print_mutex);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->print_mutex);
			break ;
		}
		printf("%ld %d is sleeping\n", get_time() - philo->arg->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->arg->print_mutex);

		sleep_time = get_time() + philo->arg->time_to_sleep;
		while (get_time() < sleep_time)
		{
			if (check_is_over(philo) == 1)
				break ;
			usleep(500);
		}

// think

		usleep(200);
			
		pthread_mutex_lock(&philo->arg->print_mutex);
		if (check_is_over(philo) == 1)
		{
			pthread_mutex_unlock(&philo->arg->print_mutex);
			break ;
		}
		printf("%ld %d is thinking\n", get_time() - philo->arg->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->arg->print_mutex);

		usleep(200);
	}
	return (NULL);
}