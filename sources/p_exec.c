/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:20:18 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/16 13:40:53 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	p_free_cmd_args(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->path);
}

static char	*p_get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = p_strjoin(*paths, "/");
		command = p_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	p_first_cmd(char *av[], char *envp[], t_pipe *pipex)
{
	char	*cmd;

	dup2(pipex->pipe[1], 1);
	close(pipex->pipe[0]);
	dup2(pipex->infile, 0);
	pipex->cmd_args = p_split(av[2], " ");
	cmd = p_get_cmd(pipex->cmds_paths, pipex->cmd_args[0]);
	if (!cmd)
	{
		p_free_cmd_args(pipex);
		p_exit_error(ERR_PIPE, 3, pipex);
	}
	execve(cmd, pipex->cmd_args, envp);
}

void	p_second_cmd(char *av[], char *envp[], t_pipe *pipex)
{
	char	*cmd;

	dup2(pipex->pipe[0], 0);
	close(pipex->pipe[1]);
	dup2(pipex->outfile, 1);
	pipex->cmd_args = p_split(av[3], " ");
	cmd = p_get_cmd(pipex->cmds_paths, pipex->cmd_args[0]);
	if (!cmd)
	{
		p_free_cmd_args(pipex);
		p_exit_error(ERR_PIPE, 3, pipex);
	}
	execve(cmd, pipex->cmd_args, envp);
}
