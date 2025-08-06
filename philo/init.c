/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:18:30 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 15:01:56 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared(t_shared *shared)
{
	int				i;
	struct timeval	tv;

	shared->forks = malloc(sizeof(pthread_mutex_t) * shared->n_philos);
	if (!shared->forks)
		return (0);
	i = 0;
	while (i < shared->n_philos)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&shared->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&shared->death_lock, NULL) != 0)
		return (0);
	gettimeofday(&tv, NULL);
	shared->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	shared->someone_died = 0;
	return (1);
}

void	init_philos(t_philo *philos, t_shared *shared)
{
	int	i;
	int	now;

	i = 0;
	while (i < shared->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = shared->start_time;
		philos[i].shared = shared;
		philos[i].left_fork = &shared->forks[i];
		philos[i].right_fork = &shared->forks[(i + 1) % shared->n_philos];
		i++;
	}
	now = get_timestamp(shared);
	i = 0;
	while (i < shared->n_philos)
		philos[i++].last_meal_time = now;
}
