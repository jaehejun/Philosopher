/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:18:08 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 18:55:49 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, THINK);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	return (CONTINUE);
}
