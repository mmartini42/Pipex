/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:11:16 by mathmart          #+#    #+#             */
/*   Updated: 2022/03/16 13:39:44 by mathmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <strings.h>
# include <fcntl.h>

# define ARGS_ERRORS "Error args !"
# define ERR_INFILE "Error infile"
# define ERR_OUTFILE "Error outfile"
# define ERR_PIPE "Error pipe"
# define ERR_PATH "Error path"

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd_args;
	char	**cmds_paths;
}				t_pipe;

/* Errors */
void	p_exit_error(char *err, int where, t_pipe *pipex);

/* Utils */
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t quantity, size_t type_size);
char	**p_split(char *str, char *charset);
bool	ft_contains_char(char *str, char c);
char	*p_strjoin(char const *s1, char const *s2);

/* Path */
char	*p_find_path(char **env, t_pipe *pipe);
char	*p_string_rework(char *str);

/* Execve */
void	p_first_cmd(char *av[], char *envp[], t_pipe *pipex);
void	p_second_cmd(char *av[], char *envp[], t_pipe *pipex);

#endif
