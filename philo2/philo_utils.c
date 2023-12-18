/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:33:47 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 19:13:05 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
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

void	print_action(t_philo *philo, long time, char *action)
{
	pthread_mutex_lock(&philo->arg->print_mutex);
	printf("%ld %d %s\n", time, philo->philo_id, action);
	pthread_mutex_unlock(&philo->arg->print_mutex);
}

//int	is_valid_number(const char *str)
//{
//	long	number;

//	number = 0;
//	while (*str != '\0')
//	{
//		if ('0' <= *str && *str <= '9')
//		{
//			number = number * 10 + (*str - '0');
//			str++;
//		}
//		else
//			return (WRONG_ARG)
//	}
//	return (number);
//}