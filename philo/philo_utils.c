/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:14:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 21:24:14 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	number;

	sign = 1;
	number = 0;
	while (is_space(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * sign);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time_ms;
	
	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}

void	print_action(long timestamp, int philo_id, char *action)
{
	//pthread_mutex_lock(&philo->share->mutex);
	printf("%ld %d %s\n", timestamp, philo_id, action);
	//pthread_mutex_unlock(&philo->share->mutex);
}
