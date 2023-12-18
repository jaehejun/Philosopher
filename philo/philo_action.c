/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:02:22 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 22:25:23 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_thread *philo)
{
	int	left;
	int	right;

	left = philo->philo_id - 1;
	right = philo->philo_id % philo->share->philo_num;

	pthread_mutex_lock(&philo->share->fork_mutex[left]);
	pthread_mutex_lock(&philo->share->fork_mutex[right]);
	philo->share->fork_state[left] = 1;
	philo->share->fork_state[right] = 1;

	pthread_mutex_lock(&philo->share->mutex);

	printf("%ld %d %s\n", get_time() - philo->share->start_time, philo->philo_id, "has taken a fork");
	printf("%ld %d %s\n", get_time() - philo->share->start_time, philo->philo_id, "has taken a fork");
	printf("%ld %d %s\n", get_time() - philo->share->start_time, philo->philo_id, "is eating");

	philo->last_eat = get_time();

	pthread_mutex_unlock(&philo->share->mutex);

	philo->eat_count++;

	usleep(1000 * philo->share->time_to_eat);

	philo->share->fork_state[left] = 0;
	philo->share->fork_state[right] = 0;
	pthread_mutex_unlock(&philo->share->fork_mutex[left]);
	pthread_mutex_unlock(&philo->share->fork_mutex[right]);
}

//void	philo_sleep(t_thread *philo)
//{
//	print_action(philo, "is sleeping");
//	usleep(1000 * philo->share->time_to_sleep);
//}

//void	philo_think(t_thread *philo)
//{
//	print_action(philo, "is thinking");
//	usleep(1000);
//}
