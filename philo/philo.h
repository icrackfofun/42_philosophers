/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:27:35 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/06 15:06:51 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_shared
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	int				someone_died;
}	t_shared;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	t_shared		*shared;
}	t_philo;

//parsing
int		parse(t_shared *shared, char **av, int ac);
int		is_positive(char *str);
int		safe_atoi(const char *str, int *out);

//clean
void	clean(t_philo *philos, t_shared *shared);

//init
int		init_shared(t_shared *shared);
void	init_philos(t_philo *philos, t_shared *shared);

//routine
void	*philosopher_routine(void *arg);
int		has_someone_died(t_shared *shared);
int		get_timestamp(t_shared *shared);

//threads
int		start_threads(t_philo *philos, t_shared *shared);
void	join_threads(t_philo *philos, int n);

//monitor
void	*monitor_routine(void *arg);
int		check_philos(t_philo *philos, t_shared *shared);
int		check_philo_status(t_philo *philo, t_shared *shared, int *all_ate);
void	precise_sleep(int duration_ms, t_shared *shared);

#endif