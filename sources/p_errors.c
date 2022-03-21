/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:22:07 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/16 17:31:39 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_putstr_fd(int fd, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	exit(EXIT_FAILURE);
}

void	p_exit_error(char *err, int where, t_pipe *pipex)
{
	if (where == 0)
		ft_putstr_fd(2, err);
	else if (where == 1)
	{
		close(pipex->infile);
		ft_putstr_fd(2, err);
	}
	else if (where == 2)
	{
		close(pipex->infile);
		close(pipex->outfile);
		ft_putstr_fd(2, err);
	}
	else if (where == 3)
	{
		close(pipex->infile);
		close(pipex->outfile);
		close(pipex->pipe[0]);
		close(pipex->pipe[1]);
		ft_putstr_fd(2, err);
	}
}
