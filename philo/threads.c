/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:18:50 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 15:08:39 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	join_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
