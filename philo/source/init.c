/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:32:36 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 16:14:47 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_philos(t_data *general)
{
	int	i;

	general->philos = malloc(sizeof(t_philo) * general->ph_count);
	if (!general->philos)
	{
		return (1);
	}
	i = -1;
	while (++i < general->ph_count)
	{
		general->philos[i].id = i + 1;
		general->philos[i].l_fork = &general->forks[i];
		general->philos[i].r_fork = &general->forks[(i + 1)
			% general->ph_count];
		general->philos[i].last_ate = 0;
		general->philos[i].num_of_meals = 0;
		general->philos[i].time_to_die = general->time_to_die;
		general->philos[i].general = general;
	}
	return (0);
}

int	init_mutex(t_data *general)
{
	int	i;
	int	j;

	i = -1;
	general->forks = malloc(sizeof(pthread_mutex_t) * general->ph_count);
	if (!general->forks)
		return (1);
	while (++i < general->ph_count)
	{
		if (pthread_mutex_init(&(general->forks[i]), NULL) != 0)
		{
			j = -1;
			while (++j <= i)
				pthread_mutex_destroy(&(general->forks[j]));
			return (1);
		}
	}
	if (pthread_mutex_init(&(general->eating), NULL) != 0
		|| pthread_mutex_init(&(general->printing), NULL) != 0
		|| pthread_mutex_init(&(general->ate), NULL) != 0
		|| pthread_mutex_init(&(general->death), NULL) != 0)
		return (1);
	return (0);
}

int	init(t_data *general, char **argv)
{
	memset(general, 0, sizeof(t_data));
	general->ph_count = ft_atoi(argv[1]);
	general->time_to_die = ft_atoi(argv[2]);
	general->time_to_eat = ft_atoi(argv[3]);
	general->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		general->must_eat = ft_atoi(argv[5]);
		if (general->must_eat < 0)
			return (1);
	}
	else
		general->must_eat = -1;
	if (init_mutex(general) || init_philos(general))
		return (1);
	return (0);
}
