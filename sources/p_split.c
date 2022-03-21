/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:59:40 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/15 17:01:33 by mathmart         ###   ########.fr       */
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

int	count_words(char *str, char *charset)
{
	size_t	str_len;
	int		word_counter;
	size_t	i;

	str_len = ft_strlen(str);
	word_counter = 0;
	i = 0;
	while (i < str_len)
	{
		while (i < str_len && ft_contains_char(charset, str[i]))
			i++;
		if (i < str_len)
			word_counter++;
		else
			continue ;
		while (i < str_len && !ft_contains_char(charset, str[i]))
			i++;
	}
	return (word_counter);
}

void	fill_words(char *str, char *charset, char **result)
{
	size_t	str_len;
	int		word_counter;
	size_t	i;
	size_t	temp;

	str_len = ft_strlen(str);
	word_counter = 0;
	i = 0;
	while (i < str_len)
	{
		while (i < str_len && ft_contains_char(charset, str[i]))
			i++;
		if (i < str_len)
		{
			temp = i;
			word_counter++;
		}
		else
			continue ;
		while (i < str_len && !ft_contains_char(charset, str[i]))
			i++;
		result[word_counter - 1] = ft_strndup(&str[temp], i - temp);
	}
}

char	**p_split(char *str, char *charset)
{
	char	**result;
	int		word_counter;

	if (str == NULL || charset == NULL)
		return (NULL);
	result = NULL;
	word_counter = count_words(str, charset);
	result = ft_calloc(word_counter + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	fill_words(str, charset, result);
	result[word_counter] = NULL;
	return (result);
}
