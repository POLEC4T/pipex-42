/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/13 12:44:16 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	set_fds(t_data *d, char *infile, char *outfile)
{
	if (d->is_here_doc)
	{
		d->fds.in = open(HEREDOC_FILENAME, O_CREAT | O_RDONLY | O_TRUNC, 0644);
		if (d->fds.in == -1)
			msg(HEREDOC_FILENAME, ": ", strerror(errno), STDERR_FILENO);
	}
	else
	{
		d->fds.in = open(infile, O_RDONLY, 644);
		if (d->fds.in == -1)
			msg(infile, ": ", strerror(errno), STDERR_FILENO);
	}
	if (d->is_here_doc)
		d->fds.out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		d->fds.out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fds.out == -1)
		msg(outfile, ": ", strerror(errno), STDERR_FILENO);
}

static void	alloc_pipes(t_data *d)
{
	int	i;

	d->pipes = ft_calloc((d->nb_cmds - 1) + 1, sizeof(int *));
	if (!d->pipes)
	{
		msg("d->pipes malloc", ": ", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	i = -1;
	while (++i < (d->nb_cmds - 1))
	{
		d->pipes[i] = malloc(2 * sizeof(int));
		if (!d->pipes[i])
		{
			msg("d->pipes[i] malloc", ": ", strerror(errno), STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		d->pipes[i][READ] = -1;
		d->pipes[i][WRITE] = -1;
	}
	d->pipes[i] = NULL;
}

static void	create_pipes(t_data *d)
{
	int	i;
	int	pipe_ret;

	i = 0;
	alloc_pipes(d);
	while (i < (d->nb_cmds - 1))
	{
		pipe_ret = pipe(d->pipes[i]);
		if (pipe_ret == -1)
		{
			msg("pipe", ": ", strerror(errno), STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		i++;
	}
}

static void	clean_init_data(t_data *d)
{
	d->pipes = NULL;
	d->pids = NULL;
	d->nb_cmds = -1;
	d->is_here_doc = 0;
	d->cmd = NULL;
	d->paths = NULL;
	d->cmd_path = NULL;
	d->fds.in = -1;
	d->fds.out = -1;
}

void	init_data(t_data *d, char **av, int ac, char **env)
{
	clean_init_data(d);
	d->is_here_doc = BONUS && ft_strncmp(av[1], "here_doc", 9) == 0;
	d->nb_cmds = ac - (3 + d->is_here_doc);
	set_fds(d, av[1], av[ac - 1]);
	d->paths = get_paths(env);
	if (!d->paths)
		exit_process(EXIT_FAILURE, d);
	d->pids = malloc(d->nb_cmds * sizeof(int));
	if (!d->pids)
	{
		msg("d->pids malloc", ": ", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	create_pipes(d);
}
