/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:10 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 19:14:32 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	input(int argc, char **argv)
{
	int		i;
	int		ms;
	char	*result;

	i = 0;
	ms = 0;
	while (++i < argc)
	{
		ms = ft_atoi(argv[i]);
		result = ft_itoa(ms);
		if (!result)
			return (1);
		if ((ms < 0) || (ms > INT_MAX || ms < INT_MIN) || (ft_strcmp(argv[i],
					result) != 0) || (ms == 0))
		{
			free(result);
			return (1);
		}
		free(result);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	general;
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (error_msg(ARGS));
	if (input(argc, argv))
		return (error_msg(INPUT));
	if (init(&general, argv))
	{
		pthread_mutex_lock(&(general.death));
		general.dead = 1;
		pthread_mutex_unlock(&(general.death));
		free_struct(&general);
		return (error_msg(INIT));
	}
	if (threads(&general))
	{
		pthread_mutex_lock(&(general.death));
		general.dead = 1;
		pthread_mutex_unlock(&(general.death));
		free_struct(&general);
		return (error_msg(THREAD));
	}
	return (0);
}
