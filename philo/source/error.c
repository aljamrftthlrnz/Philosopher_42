/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:27:58 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 19:26:42 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	join_threads(t_data *general)
{
	int	i;

	i = -1;
	while (++i < general->ph_count)
	{
		if (pthread_join(general->philos[i].thread, NULL) != 0)
			return (1);
	}
	return (0);
}

int	thread_creation_failed(int i, t_data *general)
{
	int	j;

	if (i >= 0)
	{
		pthread_mutex_lock(&(general->death));
		general->dead = 1;
		pthread_mutex_unlock(&(general->death));
		j = -1;
		while (++j <= i)
		{
			if (pthread_join(general->philos[j].thread, NULL) != 0)
				return (1);
		}
		destroy_mutex(general);
		free_struct(general);
	}
	return (0);
}

int	destroy_mutex(t_data *general)
{
	int	i;

	i = -1;
	if (general->forks != NULL)
	{
		while (++i < general->ph_count)
		{
			if (pthread_mutex_destroy(&(general->forks[i])) != 0)
				return (1);
		}
	}
	if (pthread_mutex_destroy(&(general->death)) != 0
		|| pthread_mutex_destroy(&(general->eating)) != 0
		|| pthread_mutex_destroy(&(general->printing)) != 0
		|| pthread_mutex_destroy(&(general->ate)) != 0)
		return (1);
	return (0);
}

int	free_struct(t_data *general)
{
	if (general->philos != NULL)
	{
		free(general->philos);
		general->philos = NULL;
	}
	if (general->forks != NULL)
	{
		free(general->forks);
		general->forks = NULL;
	}
	return (0);
}

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (1);
}
