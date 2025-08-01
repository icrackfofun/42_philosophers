/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:50:23 by psantos-          #+#    #+#             */
/*   Updated: 2025/08/01 21:36:07 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_positive(char *str)
{
	int i;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int safe_atoi(const char *str, int *out)
{
	long result;
	int i;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	*out = (int)result;
	return (1);
}

int parse(t_shared *shared, char **av, int ac)
{
	int i;
	int tmp;

	i = 1;
	while (i < ac)
	{
		if (!is_positive(av[i]) || !safe_atoi(av[i], &tmp))
			return (0);
		if (i == 1)
			shared->n_philos = tmp;
		else if (i == 2)
			shared->time_to_die = tmp;
		else if (i == 3)
			shared->time_to_eat = tmp;
		else if (i == 4)
			shared->time_to_sleep = tmp;
		else if (i == 5)
			shared->must_eat_count = tmp;
		i++;
	}
	if (ac == 5)
		shared->must_eat_count = -1;
	if (shared->n_philos <= 0)
    	return (0);
	return (1);
}
