/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:17:45 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 22:18:31 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_must_eat;
	int				*fork_state;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	mutex;
	long			start_time;
	int				full;
	int				is_over;
}	t_arg;

typedef struct s_thread
{
	int			philo_id;
	int			eat_count;
	long		last_eat;
	pthread_t	thread;
	t_arg		*share;
}	t_thread;

int		ft_atoi(const char *str);

long	get_time(void);
void	print_action(long timestamp, int philo_id, char *action);

void	init_args(t_arg *share, char **argv);
void	init_philo(t_arg *share, t_thread *philo);

void	*philo_routine(t_thread *philo);
void	philo_eat(t_thread *philo);
void	philo_sleep(t_thread *philo);
void	philo_think(t_thread *philo);

int		need_to_stop(t_arg *share);
void	monitoring(t_arg *share, t_thread *philo);



#endif
