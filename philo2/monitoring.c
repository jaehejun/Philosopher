/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:27:01 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 19:05:16 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_full(t_arg *arg)
{
	pthread_mutex_lock(&arg->full_mutex);
	if (arg->full == arg->philo_num)
	{
		pthread_mutex_lock(&arg->over_mutex);
			arg->is_over = OVER;
		pthread_mutex_unlock(&arg->over_mutex);
		pthread_mutex_unlock(&arg->full_mutex);
		return (FULL);
	}
	pthread_mutex_unlock(&arg->full_mutex);
	return (CONTINUE);
}

void	monitoring(t_arg *arg, t_philo *philos)
{
	int	p_num;

	while (1)
	{
		p_num = -1;
		if (check_is_full(arg) == FULL)
			return ;
		pthread_mutex_unlock(&arg->full_mutex);
		while (++p_num < arg->philo_num)
		{
			pthread_mutex_lock(&philos[p_num].last_eat_mutex);
			if (get_time() - philos[p_num].last_eat >= arg->time_to_die)
			{
				pthread_mutex_lock(&arg->over_mutex);
				arg->is_over = 1;
				pthread_mutex_unlock(&arg->over_mutex);
				print_action(&philos[p_num], get_time() - arg->start_time, \
				"died");
				pthread_mutex_unlock(&philos[p_num].last_eat_mutex);
				return ;
			}
			pthread_mutex_unlock(&philos[p_num].last_eat_mutex);
		}
	}
}
