/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:06:24 by jaehejun          #+#    #+#             */
/*   Updated: 2023/12/14 15:39:22 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

void	*foo(void *arg)
{
	(void)arg;
	printf("1\n");
	usleep(1000);
	printf("2\n");
	usleep(1000);
	printf("3\n");
	usleep(1000);
	printf("4\n");
	usleep(1000);
	printf("5\n");
	usleep(1000);
	printf("6\n");
	usleep(1000);
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	int	i = 0;

	pthread_create(&t1, NULL, foo, NULL);
	while (i++ < 1000)
	{
		printf("@");
		//usleep(1);
	}
	pthread_detach(t1);
	//pthread_join(t1, NULL);
	printf("MAIN THREAD!\n");
	return 0;
}
