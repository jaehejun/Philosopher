/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:32:59 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/19 18:51:01 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define WRONG_ARG -1
# define CONTINUE 0
# define OVER 1
# define FULL 2
# define DEAD 3
# define VALID 4
# define EAT "is eating"
# define TAKE "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "is dead"

typedef struct s_arg
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_must_eat;
	int				*fork_state;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	long			start_time;
	pthread_mutex_t	full_mutex;
	int				full;
	pthread_mutex_t	over_mutex;
	int				is_over;
}	t_arg;

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	long			last_eat;
	int				left;
	int				right;
	pthread_t		thread;
	t_arg			*arg;
}	t_philo;

long	ft_atoi(const char *str);
int		check_arguments(char **argv);

long	get_time(void);

void	init_arg(t_arg *arg, int argc, char **argv);
void	init_philo(t_arg *arg, t_philo *philos);

void	create_philo_theads(t_arg *arg, t_philo *philos);
void	join_philo_threads(t_arg *arg, t_philo *philos);
void	destroy_mutex(t_arg *arg, t_philo *philos);
void	free_args(t_arg *arg, t_philo *philos);

void	*philo_routine(t_philo *philo);
void	philo_alone(t_philo *philo);

int		check_is_over(t_philo *philo);

int		philo_get_fork(t_philo *philo);
void	philo_return_fork(t_philo *philo);
void	philo_count_eat(t_philo *philo);

int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

void	monitoring(t_arg *arg, t_philo *philos);
int		check_is_full(t_arg *arg);

#endif
