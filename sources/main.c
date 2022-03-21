/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:15:50 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/16 16:58:20 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	p_first_step(int ac, char **av, t_pipe *pipe)
{
	if (ac != 5)
		p_exit_error(ARGS_ERRORS, 0, pipe);
	pipe->infile = open(av[1], O_RDONLY);
	if (pipe->infile < 0)
		p_exit_error(ERR_INFILE, 0, pipe);
	pipe->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipe->outfile < 0)
		p_exit_error(ERR_OUTFILE, 1, pipe);
}

static void	p_second_step(t_pipe *pipex, char *envp[])
{
	pipex->path = p_find_path(envp, pipex);
	pipex->cmds_paths = p_split(pipex->path, ":");
	pipex->cmds_paths[0] = p_string_rework(pipex->cmds_paths[0]);
}

static void	p_final_step(t_pipe *pipex)
{
	size_t	i;

	close(pipex->infile);
	close(pipex->outfile);
	i = 0;
	while (pipex->cmds_paths[i])
	{
		free(pipex->cmds_paths[i]);
		i++;
	}
	free(pipex->cmds_paths);
	free(pipex->path);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipe	pipex;

	p_first_step(ac, av, &pipex);
	if (pipe(pipex.pipe) < 0)
		p_exit_error(ERR_PIPE, 2, &pipex);
	p_second_step(&pipex, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		p_first_cmd(av, envp, &pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		p_second_cmd(av, envp, &pipex);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	p_final_step(&pipex);
	return (0);
}
