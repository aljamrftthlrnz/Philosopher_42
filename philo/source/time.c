/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:07:04 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 20:28:35 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	log_event(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds, t_philo *philos)
{
	size_t	start;

	start = log_event();
	while ((log_event() - start) < milliseconds)
	{
		if ((philo_is_dead(philos)))
			break ;
		usleep(50);
	}
}

void	print_event(t_philo *philos, int id, char *msg)
{
	pthread_mutex_lock(&(philos->general->printing));
	if ((!(philo_is_dead(philos))) && (!(philo_all_ate(philos))))
		printf("%zu %d %s\n", (log_event() - philos->general->begin_simulation),
			id, msg);
	pthread_mutex_unlock(&(philos->general->printing));
}

void	time_manipulation(t_data *general, t_philo *philos)
{
	if (general->time_to_sleep >= general->time_to_eat)
		usleep(1000 * (general->time_to_sleep - general->time_to_eat) + 500);
	else
		usleep(1000 * (general->time_to_eat - general->time_to_sleep) + 500);
}
