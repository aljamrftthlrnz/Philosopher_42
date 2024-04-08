/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:48:26 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 20:28:29 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	one_philo(t_philo *philos)
{
	pthread_mutex_lock(philos->l_fork);
	print_event(philos, philos->id, "has taken a fork");
	pthread_mutex_lock(&(philos->general->eating));
	philos->last_ate = log_event();
	pthread_mutex_unlock(&(philos->general->eating));
	pthread_mutex_unlock(philos->l_fork);
	usleep(philos->time_to_die * 2000);
	return (0);
}

int	philo_all_ate(t_philo *philos)
{
	pthread_mutex_lock(&(philos->general->ate));
	if (philos->general->all_ate == 1)
	{
		pthread_mutex_unlock(&(philos->general->ate));
		return (1);
	}
	pthread_mutex_unlock(&(philos->general->ate));
	return (0);
}

int	philo_is_dead(t_philo *philos)
{
	pthread_mutex_lock(&philos->general->death);
	if (philos->general->dead == 1)
	{
		pthread_mutex_unlock(&philos->general->death);
		return (1);
	}
	pthread_mutex_unlock(&philos->general->death);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philos;
	t_data	*general;

	philos = (t_philo *)ptr;
	general = philos->general;
	if (general->ph_count == 1)
		one_philo(philos);
	if ((philos->id % 2 == 0))
		ft_usleep(general->time_to_eat / 2, philos);
	while (!(philo_is_dead(philos)))
	{
		fork_etiquette(philos);
		eating(philos);
		if ((philo_all_ate(philos)) || (philo_is_dead(philos)))
			break ;
		sleeping(philos);
		thinking(philos);
		if (general->ph_count % 2 != 0 && !philo_is_dead(philos))
			time_manipulation(general, philos);
	}
	return (NULL);
}

int	threads(t_data *general)
{
	int		i;
	t_philo	*philos;

	philos = general->philos;
	general->begin_simulation = log_event();
	i = 0;
	while (i < general->ph_count)
	{
		if (pthread_create(&(philos[i].thread), NULL, &routine,
				(void *)&philos[i]) != 0)
		{
			thread_creation_failed(i, general);
			return (1);
		}
		pthread_mutex_lock(&(general->eating));
		philos[i].last_ate = log_event();
		pthread_mutex_unlock(&(general->eating));
		i++;
	}
	monitor(general);
	join_threads(general);
	destroy_mutex(general);
	free_struct(general);
	return (0);
}
