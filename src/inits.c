/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 13:23:04 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	set_fds(t_data *d, char *infile, char *outfile)
{
	d->fds.in = open(infile, O_RDONLY, 644);
	if (d->fds.in == -1)
	{
		msg(strerror(errno), infile, STDERR_FILENO);
	}
	d->fds.out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fds.out == -1)
	{
		msg(strerror(errno), outfile, STDERR_FILENO);
	}
}

static void	alloc_pipes(t_data *d)
{
	int	i;

	d->pipes = ft_calloc((d->nb_cmds - 1) + 1, sizeof(int *));
	if (!d->pipes)
	{
		msg(strerror(errno), "d->pipes malloc", STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	i = -1;
	while (++i < (d->nb_cmds - 1))
	{
		d->pipes[i] = malloc(2 * sizeof(int));
		if (!d->pipes[i])
		{
			msg(strerror(errno), "d->pipes[i] malloc", STDERR_FILENO);
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

	i = 0;
	alloc_pipes(d);
	while (i < (d->nb_cmds - 1))
	{
		if (pipe(d->pipes[i]) == -1)
		{
			msg("Error", "could not create pipe", STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		i++;
	}
}

static void	clean_init_data(t_data *d)
{
	d->cmd = NULL;
	d->cmd_path = NULL;
	d->paths = NULL;
	d->nb_cmds = -1;
	d->pids = NULL;
	d->pipes = NULL;
	d->fds.in = -1;
	d->fds.out = -1;
}

void	init_data(t_data *d, char **av, int ac, char **env)
{
	clean_init_data(d);
	d->nb_cmds = ac - 3;
	set_fds(d, av[1], av[ac - 1]);
	d->paths = get_paths(env);
	if (!d->paths)
		exit_process(EXIT_FAILURE, d);
	d->pids = malloc(d->nb_cmds * sizeof(int));
	if (!d->pids)
	{
		msg(strerror(errno), "d->pids malloc", STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	create_pipes(d);
}
