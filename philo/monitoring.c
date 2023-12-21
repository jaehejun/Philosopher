/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:27:01 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/21 16:47:26 by jaehejun         ###   ########.fr       */
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
		if (check_is_full(arg) == FULL)
			return ;
		p_num = -1;
		while (++p_num < arg->philo_num)
		{
			pthread_mutex_lock(&philos[p_num].last_eat_mutex);
			if (get_time() - philos[p_num].last_eat >= arg->time_to_die)
			{
				pthread_mutex_unlock(&philos[p_num].last_eat_mutex);
				pthread_mutex_lock(&arg->over_mutex);
				arg->is_over = OVER;
				pthread_mutex_unlock(&arg->over_mutex);
				pthread_mutex_lock(&arg->print_mutex);
				printf("%ld %d %s\n", get_time() - arg->start_time, \
						philos[p_num].philo_id, DIE);
				pthread_mutex_unlock(&arg->print_mutex);
				return ;
			}
			pthread_mutex_unlock(&philos[p_num].last_eat_mutex);
		}
	}
}
