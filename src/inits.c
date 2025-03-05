/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/05 10:49:41 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_paths(char **env)
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

void	set_fds(t_data *d, char *infile, char *outfile)
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

void clean_init_data(t_data *d)
{
	d->cmd = NULL;
	d->cmd_path = NULL;
	d->paths = NULL;
	d->nb_cmds = 0;	
}

void	init_data(t_data *d, char **av, int ac, char **env)
{
	d->nb_cmds = ac - 3;
	set_fds(d, av[1], av[ac - 1]);
	pipe(d->pipe);
	d->paths = get_paths(env);
	if (!d->paths)
	{
		close_fds(d);
		exit(EXIT_FAILURE);
	}
}
