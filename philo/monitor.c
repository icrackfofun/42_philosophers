/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:27:08 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 15:04:36 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_sleep(int duration_ms, t_shared *shared)
{
	int	start;

	start = get_timestamp(shared);
	while (get_timestamp(shared) - start < duration_ms)
		usleep(50);
}

static void	print_status(t_philo *philo, char *msg)
{
	int		is_died_msg;
	char	*d;
	int		i;

	is_died_msg = 1;
	d = "died";
	i = 0;
	while (msg[i] && d[i] && msg[i] == d[i])
		i++;
	if (msg[i] != d[i])
		is_died_msg = 0;
	pthread_mutex_lock(&philo->shared->write_lock);
	pthread_mutex_lock(&philo->shared->death_lock);
	if (philo->shared->someone_died && !is_died_msg)
	{
		pthread_mutex_unlock(&philo->shared->death_lock);
		pthread_mutex_unlock(&philo->shared->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->shared->death_lock);
	printf("%d %d %s\n", get_timestamp(philo->shared), philo->id, msg);
	pthread_mutex_unlock(&philo->shared->write_lock);
}

int	check_philo_status(t_philo *philo, t_shared *shared, int *all_ate)
{
	int	elapsed;
	int	last_meal;

	pthread_mutex_lock(&shared->death_lock);
	last_meal = philo->last_meal_time;
	elapsed = get_timestamp(shared) - last_meal;
	if (elapsed > shared->time_to_die)
	{
		if (!shared->someone_died)
		{
			shared->someone_died = 1;
			pthread_mutex_unlock(&shared->death_lock);
			print_status(philo, "died");
			return (1);
		}
		pthread_mutex_unlock(&shared->death_lock);
		return (1);
	}
	if (shared->must_eat_count != -1
		&& philo->meals_eaten < shared->must_eat_count)
		*all_ate = 0;
	pthread_mutex_unlock(&shared->death_lock);
	return (0);
}

int	check_philos(t_philo *philos, t_shared *shared)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < shared->n_philos)
	{
		if (check_philo_status(&philos[i], shared, &all_ate))
			return (1);
		i++;
	}
	if (shared->must_eat_count != -1 && all_ate)
	{
		pthread_mutex_lock(&shared->death_lock);
		shared->someone_died = 1;
		pthread_mutex_unlock(&shared->death_lock);
		pthread_mutex_lock(&shared->write_lock);
		printf("%d All philosophers ate at least %d times\n",
			get_timestamp(shared), shared->must_eat_count);
		pthread_mutex_unlock(&shared->write_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_shared	*shared;

	philos = (t_philo *)arg;
	shared = philos[0].shared;
	while (1)
	{
		pthread_mutex_lock(&shared->death_lock);
		if (shared->someone_died)
		{
			pthread_mutex_unlock(&shared->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&shared->death_lock);
		if (check_philos(philos, shared))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
