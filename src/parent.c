/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 14:56:53 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	start_children(t_data *d, char **av, char **env)
{
	int	i_cmds;

	i_cmds = -1;
	while (++i_cmds < d->nb_cmds)
	{
		secure_fork(&d->pids[i_cmds], d);
		if (!d->pids[i_cmds])
		{
			set_curr_in_out(i_cmds, d);
			set_cmd(d, av[i_cmds + 2]);
			exec_cmd(d, env);
		}
		if (i_cmds > 0)
			close(d->pipes[i_cmds - 1][READ]);
		if (i_cmds < d->nb_cmds - 1)
			close(d->pipes[i_cmds][WRITE]);
	}
	close_fds_in_out(d);
}

int	wait_children(t_data *d)
{
	int	status;
	int	i_pids;

	i_pids = -1;
	while (++i_pids < d->nb_cmds)
	{
		waitpid(d->pids[i_pids], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
