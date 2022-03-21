/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_paths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:42:19 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/16 13:37:06 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strndup(const char *str, size_t n)
{
	size_t	index;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_calloc(n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (str[index] && index < n)
	{
		result[index] = str[index];
		index++;
	}
	while (index <= n)
	{
		result[index] = 0;
		index++;
	}
	return (result);
}

static int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	c_index;

	c_index = 0;
	while ((s1[c_index] || s2[c_index]) && c_index < n)
	{
		if (s1[c_index] != s2[c_index])
			return ((unsigned char)s1[c_index] - (unsigned char)s2[c_index]);
		c_index++;
	}
	return (0);
}

char	*p_find_path(char **env, t_pipe *pipe)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (ft_strndup(env[i], ft_strlen(env[i])));
		i++;
	}
	p_exit_error(ERR_PATH, 3, pipe);
	return (NULL);
}

char	*p_string_rework(char *str)
{
	char	*temp;

	temp = ft_strndup(str + 5, ft_strlen(str) - 5);
	free(str);
	return (temp);
}
