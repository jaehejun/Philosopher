/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:04:22 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 21:26:42 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	need_to_stop(t_arg *share)
{
	pthread_mutex_lock(&share->mutex);
	if (share->is_over == 1)
	{
		pthread_mutex_unlock(&share->mutex);
		return (1);
	}
	pthread_mutex_unlock(&share->mutex);
	return (0);
}

void	monitoring(t_arg *share, t_thread *philo)
{
	int		index;
	//long	starving_time;

	while (1)
	{
		index = 0;
		while (index < philo->share->philo_num)
		{
			usleep(1000);
			pthread_mutex_lock(&share->mutex);
			//starving_time = get_time() - philo[index].last_eat;
			if (get_time() - philo[index].last_eat > share->time_to_die)
			{
				share->is_over = 1;
				print_action(get_time() - share->start_time, philo[index].philo_id, "@@@died@@@");
				pthread_mutex_unlock(&share->mutex);
				return ;
			}
			if (share->full == share->num_must_eat)
			{
				share->is_over = 1;
				pthread_mutex_unlock(&share->mutex);
				return ;
			}
			pthread_mutex_unlock(&share->mutex);
			index++;
		}
	}
	return ;
}
