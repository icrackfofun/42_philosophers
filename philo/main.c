/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:27:29 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/01 21:52:05 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	t_shared	shared;
	t_philo		*philos;
	pthread_t	monitor;

	if (ac != 5 && ac != 6)
		return (1);
	if (!parse(&shared, av, ac))
		return (1);
	if (!init_shared(&shared))
		return (1);
	philos = malloc(sizeof(t_philo) * shared.n_philos);
	if (!philos)
		return (1);
	init_philos(philos, &shared);
if (!start_threads(philos, &shared) || pthread_create(&monitor, NULL,
	monitor_routine, philos) != 0)
{
    clean(philos, &shared);
    return (1);
}
	pthread_join(monitor, NULL);
	join_threads(philos, shared.n_philos);
	clean(philos, &shared);
    return (0);
}

