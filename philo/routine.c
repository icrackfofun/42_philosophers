/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:14:06 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 14:57:05 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(t_shared *shared)
{
	struct timeval	tv;
	int				ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - shared->start_time;
	return (ms);
}

static void print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared->death_lock);
	if (!philo->shared->someone_died)
	{
		pthread_mutex_lock(&philo->shared->write_lock);
		printf("%d %d %s\n", get_timestamp(philo->shared), philo->id, msg);
		pthread_mutex_unlock(&philo->shared->write_lock);
	}
	pthread_mutex_unlock(&philo->shared->death_lock);
}

int	has_someone_died(t_shared *shared)
{
	int died;

	pthread_mutex_lock(&shared->death_lock);
	died = shared->someone_died;
	pthread_mutex_unlock(&shared->death_lock);
	return (died);
}

static int pick_fork(t_philo *ph)
{
	if (ph->shared->n_philos == 1)
    {
        pthread_mutex_lock(ph->left_fork);
        print_status(ph, "has taken a fork");
        precise_sleep(ph->shared->time_to_die + 1, ph->shared);
        pthread_mutex_unlock(ph->left_fork);
        return (0);
    }
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		print_status(ph, "has taken a fork");
		pthread_mutex_lock(ph->left_fork);
		print_status(ph, "has taken a fork");
		return (1);
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		print_status(ph, "has taken a fork");
		pthread_mutex_lock(ph->right_fork);
		print_status(ph, "has taken a fork");
		return (1);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!has_someone_died(ph->shared))
	{
		print_status(ph, "is thinking");
		if (pick_fork(ph) == 0)
			return (NULL);
		print_status(ph, "is eating");
		precise_sleep(ph->shared->time_to_eat, ph->shared);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_lock(&ph->shared->death_lock);
		ph->last_meal_time = get_timestamp(ph->shared);
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->shared->death_lock);
		if (has_someone_died(ph->shared))
			break;
		print_status(ph, "is sleeping");
		precise_sleep(ph->shared->time_to_sleep, ph->shared);
	}
	return (NULL);
}
