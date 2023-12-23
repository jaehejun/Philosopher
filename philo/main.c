/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:31 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/23 17:43:03 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_theads(t_arg *arg, t_philo *philos)
{
	int	p_num;

	p_num = 0;
	while (p_num < arg->philo_num)
	{
		pthread_create(&philos[p_num].thread, NULL, (void *)philo_routine, \
						&philos[p_num]);
		p_num++;
	}
}

void	join_philo_threads(t_arg *arg, t_philo *philos)
{
	int	p_num;

	p_num = 0;
	while (p_num < arg->philo_num)
	{
		pthread_join(philos[p_num].thread, NULL);
		p_num++;
	}
}

void	destroy_mutex(t_arg *arg, t_philo *philos)
{
	int	p_num;

	p_num = 0;
	while (p_num < arg->philo_num)
	{
		pthread_mutex_destroy(&arg->fork_mutex[p_num]);
		pthread_mutex_destroy(&philos[p_num].last_eat_mutex);
		p_num++;
	}
	pthread_mutex_destroy(&arg->print_mutex);
	pthread_mutex_destroy(&arg->full_mutex);
	pthread_mutex_destroy(&arg->over_mutex);
}

void	free_args(t_arg *arg, t_philo *philos)
{
	free(arg->fork_mutex);
	free(arg->fork_state);
	free(philos);
	free(arg);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: INVALID NUMBER OF ARGS!\n");
		return (0);
	}
	if (check_arguments(argv) == WRONG_ARG)
	{
		printf("ERROR: WRONG ARGUMNETS!\n");
		return (0);
	}
	arg = malloc(sizeof(t_arg) * 1);
	init_arg(arg, argc, argv);
	philos = malloc(sizeof(t_philo) * arg->philo_num);
	init_philo(arg, philos);
	create_philo_theads(arg, philos);
	monitoring(arg, philos);
	join_philo_threads(arg, philos);
	destroy_mutex(arg, philos);
	free_args(arg, philos);
	return (0);
}
