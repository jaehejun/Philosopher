/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:06:38 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 22:26:47 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_arg *share, char **argv)
{
	int	p_num;

	share->philo_num = ft_atoi(argv[1]);
	share->time_to_die = ft_atoi(argv[2]);
	share->time_to_eat = ft_atoi(argv[3]);
	share->time_to_sleep = ft_atoi(argv[4]);
	share->num_must_eat = -1;
	if (argv[5] != NULL)
		share->num_must_eat = ft_atoi(argv[5]);
	share->fork_state = malloc(sizeof(int) * share->philo_num);
	share->fork_mutex = malloc(sizeof(pthread_mutex_t) * share->philo_num);
	p_num = 0;
	while (p_num < share->philo_num)
	{
		share->fork_state[p_num] = 0;
		pthread_mutex_init(&share->fork_mutex[p_num], NULL);
		p_num++;
	}
	pthread_mutex_init(&share->mutex, NULL);
	share->start_time = get_time();
	share->full = 0;
	share->is_over = 0;
}

void	init_philo(t_arg *share, t_thread *philo)
{
	int	p_num;
	
	p_num = 0;
	while (p_num < share->philo_num)
	{
		philo[p_num].philo_id = p_num + 1;
		philo[p_num].eat_count = 0;
		philo[p_num].last_eat = 0;
		philo[p_num].share = share;
		p_num++;
	}
}
