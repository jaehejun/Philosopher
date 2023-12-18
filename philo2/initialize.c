/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:25:17 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 15:33:20 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_arg(t_arg *arg, int argc, char **argv)
{
	int	p_num;

	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		arg->num_must_eat = -1;
	else
		arg->num_must_eat = ft_atoi(argv[5]);
	arg->fork_state = malloc(sizeof(int) * arg->philo_num);
	arg->fork_mutex = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	p_num = 0;
	while (p_num < arg->philo_num)
	{
		arg->fork_state[p_num] = 0;
		pthread_mutex_init(&arg->fork_mutex[p_num], NULL);
		p_num++;
	}
	pthread_mutex_init(&arg->print_mutex, NULL);
	pthread_mutex_init(&arg->full_mutex, NULL);
	pthread_mutex_init(&arg->over_mutex, NULL);
	arg->start_time = get_time();
	arg->full = 0;
	arg->is_over = 0;
}

void	init_philo(t_arg *arg, t_philo *philos)
{
	int	p_num;

	p_num = 0;
	while (p_num < arg->philo_num)
	{
		philos[p_num].philo_id = p_num + 1;
		philos[p_num].eat_count = 0;
		pthread_mutex_init(&philos[p_num].last_eat_mutex, NULL);
		philos[p_num].last_eat = arg->start_time;
		philos[p_num].left = p_num;
		philos[p_num].right = (p_num + 1) % arg->philo_num;
		philos[p_num].arg = arg;
		p_num++;
	}
}
