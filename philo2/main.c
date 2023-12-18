/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:31 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 15:32:38 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void    f(void)
//{
//    system("leaks philo");
//}
	//atexit(f);

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philos;
	int		p_num;
	int		join_cnt;
	int		destroy_cnt;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: INVALID NUMBER OF ARGS!\n");
		return (0);
	}
	arg = malloc(sizeof(t_arg));
	init_arg(arg, argc, argv);
	philos = malloc(sizeof(t_philo) * arg->philo_num);
	init_philo(arg, philos);
	p_num = 0;
	while (p_num < arg->philo_num)
	{
		pthread_create(&philos[p_num].thread, NULL, (void *)philo_routine, &philos[p_num]);
		p_num++;
	}
	monitoring(arg, philos);
	join_cnt = 0;
	while (join_cnt < arg->philo_num)
	{
		pthread_join(philos[join_cnt].thread, NULL);
		join_cnt++;
	}
	destroy_cnt = 0;
	while (destroy_cnt < arg->philo_num)
	{
		pthread_mutex_destroy(&arg->fork_mutex[destroy_cnt]);
		pthread_mutex_destroy(&philos[destroy_cnt].last_eat_mutex);
		destroy_cnt++;
	}
	pthread_mutex_destroy(&arg->print_mutex);
	pthread_mutex_destroy(&arg->full_mutex);
	pthread_mutex_destroy(&arg->over_mutex);
	free(arg->fork_mutex);
	free(arg->fork_state);
	free(philos);
	free(arg);
	return 0;
}
