/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:33:47 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 18:50:54 by jaehejun         ###   ########.fr       */
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

int	check_arguments(char **argv)
{
	long	number;
	int		argc;
	int		index;

	argc = 1;
	while (argv[argc] != NULL)
	{
		number = 0;
		index = 0;
		while (argv[argc][index] != '\0')
		{
			if ('0' <= argv[argc][index] && argv[argc][index] <= '9')
				number = number * 10 + (argv[argc][index] - '0');
			else
				return (WRONG_ARG);
			index++;
		}
		if (number == 0)
			return (WRONG_ARG);
		argc++;
	}
	return (VALID);
}
