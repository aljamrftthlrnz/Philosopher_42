/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:50:42 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/03 15:56:59 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg < 58)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	result;
	size_t	sign;
	size_t	i;
	char	*ptr;

	ptr = (char *)str;
	result = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(ptr[i]))
	{
		result = result * 10 + ptr[i] - '0';
		i++;
	}
	return (sign * result);
}

static int	count_int(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		counter;
	int		index;

	counter = count_int(n);
	index = n;
	string = malloc(count_int(n) + 1);
	if (!string)
		return (NULL);
	while (counter > 0)
	{
		if (n < 0)
			string[counter - 1] = n % 10 * -1 + '0';
		else
			string[counter - 1] = n % 10 + '0';
		n = n / 10;
		counter--;
	}
	if (index < 0)
		string[0] = '-';
	string[count_int(index)] = '\0';
	return (string);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
