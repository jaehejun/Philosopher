/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:18:27 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 18:55:35 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	long	sleep_time;

	pthread_mutex_lock(&philo->arg->print_mutex);
	if (check_is_over(philo) == OVER)
	{
		pthread_mutex_unlock(&philo->arg->print_mutex);
		return (OVER);
	}
	printf("%ld %d %s\n", get_time() - philo->arg->start_time, \
			philo->philo_id, SLEEP);
	pthread_mutex_unlock(&philo->arg->print_mutex);
	sleep_time = get_time() + philo->arg->time_to_sleep;
	while (get_time() < sleep_time)
	{
		if (check_is_over(philo) == OVER)
			return (OVER);
		usleep(200);
	}
	return (CONTINUE);
}
