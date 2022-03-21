/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:55:38 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/15 18:49:24 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_memset(void *target, int char_to_set, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = target;
	while (i < n)
	{
		str[i] = (unsigned char)char_to_set;
		i++;
	}
	return (target);
}

void	*ft_calloc(size_t quantity, size_t type_size)
{
	void	*result;

	result = malloc(quantity * type_size);
	if (result == NULL)
		return (NULL);
	ft_memset(result, 0, quantity * type_size);
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}

bool	ft_contains_char(char *str, char c)
{
	ssize_t	index;

	if (!str)
		return (false);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (true);
		index++;
	}
	return (false);
}
