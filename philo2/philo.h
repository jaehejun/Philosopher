/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:32:59 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/18 19:20:40 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define OVER 1
# define FULL 1
# define DEAD 1
# define CONTINUE 0

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
long	get_time(void);
void	print_action(t_philo *philo, long time, char *action);


void	init_arg(t_arg *arg, int argc, char **argv);
void	init_philo(t_arg *arg, t_philo *philos);

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
