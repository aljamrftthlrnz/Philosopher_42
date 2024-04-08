/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:55:52 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 19:46:24 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_meal_helper(t_philo *philos)
{
	if ((log_event() - philos->last_ate) >= philos->time_to_die)
	{
		print_event(philos, philos->id, "died");
		return (1);
	}
	return (0);
}

int	check_meal(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->general->ph_count)
	{
		if (check_meal_helper(&philos[i]))
		{
			pthread_mutex_lock(&(philos->general->death));
			philos->general->dead = 1;
			pthread_mutex_unlock(&(philos->general->death));
			return (1);
		}
	}
	return (0);
}

int	meal_number_check(t_philo *philos)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < philos->general->ph_count && philos->general->must_eat != -1
		&& philos[i].num_of_meals >= philos->general->must_eat)
		count++;
	if (count == philos->general->ph_count)
	{
		pthread_mutex_lock(&philos->general->ate);
		philos->general->all_ate = 1;
		pthread_mutex_unlock(&philos->general->ate);
		return (1);
	}
	return (0);
}

void	monitor(t_data *general)
{
	while (!(philo_is_dead(general->philos)))
	{
		pthread_mutex_lock(&(general->eating));
		if (check_meal(general->philos))
		{
			pthread_mutex_unlock(&(general->eating));
			break ;
		}
		else if (meal_number_check(general->philos))
		{
			pthread_mutex_unlock(&general->eating);
			break ;
		}
		pthread_mutex_unlock(&(general->eating));
		usleep(200);
	}
}
