/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:12:42 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 19:32:29 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	fork_etiquette(t_philo *philos)
{
	if ((!(philos->id % 2)) || ((philos->general->ph_count % 2
				&& philos->id == philos->general->ph_count)))
	{
		pthread_mutex_lock(philos->l_fork);
		print_event(philos, philos->id, "has taken a fork");
		pthread_mutex_lock(philos->r_fork);
		print_event(philos, philos->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->r_fork);
		print_event(philos, philos->id, "has taken a fork");
		pthread_mutex_lock(philos->l_fork);
		print_event(philos, philos->id, "has taken a fork");
	}
}

void	eating(t_philo *philos)
{
	pthread_mutex_lock(&(philos->general->eating));
	philos->last_ate = log_event();
	pthread_mutex_unlock(&(philos->general->eating));
	print_event(philos, philos->id, "is eating");
	ft_usleep(philos->general->time_to_eat, philos);
	pthread_mutex_lock(&(philos->general->eating));
	if (philos->num_of_meals != -1)
		philos->num_of_meals++;
	pthread_mutex_unlock(&(philos->general->eating));
	if (!(philos->id % 2) || ((philos->general->ph_count % 2
				&& philos->id == philos->general->ph_count)))
	{
		pthread_mutex_unlock(philos->r_fork);
		pthread_mutex_unlock(philos->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->l_fork);
		pthread_mutex_unlock(philos->r_fork);
	}
}

void	sleeping(t_philo *philos)
{
	print_event(philos, philos->id, "is sleeping");
	ft_usleep(philos->general->time_to_sleep, philos);
}

void	thinking(t_philo *philos)
{
	if (!philo_is_dead(philos))
		print_event(philos, philos->id, "is thinking");
}
