/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 13:19:12 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_cmd(t_data *d, char *str_cmd)
{
	if (ft_strlen(str_cmd) == 0)
		d->cmd = empty_split();
	else
		d->cmd = ft_split(str_cmd, " ");
	if (!d->cmd)
	{
		msg("Error split", strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	d->cmd_path = get_cmd_path(d, d->cmd[0]);
	if (!d->cmd_path)
	{
		exit_process(STDERR_FILENO, d);
	}
}

void	set_curr_in_out(int i_cmds, t_data *d)
{
	int	is_first_cmd;
	int	is_last_cmd;
	int	input;
	int	output;

	is_first_cmd = i_cmds == 0;
	is_last_cmd = i_cmds == d->nb_cmds - 1;
	if (is_first_cmd)
		input = d->fds.in;
	else
		input = d->pipes[i_cmds - 1][READ];
	if (is_last_cmd)
		output = d->fds.out;
	else
		output = d->pipes[i_cmds][WRITE];
	redirect(input, output, d);
}

void	exec_cmd(t_data *d, char **env)
{
	close_fds_and_pipes(d);
	if (execve(d->cmd_path, d->cmd, env) == -1)
	{
		msg(strerror(errno), d->cmd[0], STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
}
