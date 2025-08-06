/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:34:48 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 15:01:07 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_philo *philos, t_shared *shared)
{
	int	i;

	if (philos)
		free(philos);
	if (shared->forks)
	{
		i = 0;
		while (i < shared->n_philos)
		{
			pthread_mutex_destroy(&shared->forks[i++]);
		}
		free(shared->forks);
		shared->forks = NULL;
	}
	pthread_mutex_destroy(&shared->write_lock);
	pthread_mutex_destroy(&shared->death_lock);
}
