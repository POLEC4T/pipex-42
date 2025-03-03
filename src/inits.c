/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miloniemaz <mniemaz@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/01 04:26:21 by miloniemaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char **	get_paths(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			res = ft_split(env[i] + 5, ":");
			if (!res)
			{
				msg("Error ft_split", strerror(errno), STDERR_FILENO);
				return (NULL);
			}
			return (res);
		}
		i++;
	}
	msg("Error", "PATH not found", STDERR_FILENO);
	return (NULL);
}

void set_fds(t_data *d, char *infile, char *outfile)
{
	d->fds.in = open(infile, O_RDONLY, 644);
	if (d->fds.in == -1)
	{
		msg("Error opening infile", strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	d->fds.out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void init_data(t_data *d, char *infile, char *outfile, char **env)
{
    d->cmd = NULL;
    d->cmd_path = NULL;
    set_fds(d, infile, outfile);
	pipe(d->pipe);
	d->paths = get_paths(env);
	if (!d->paths)
	{
		close(d->fds.in);
		close(d->fds.out);
		close(d->pipe[0]);
		close(d->pipe[1]);
		exit(EXIT_FAILURE);
	}
	d->pids[0] = 0;
	d->pids[1] = 0;
}
