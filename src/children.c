/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 14:12:08 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief redirects the standard error output to the file
 * d->err_file_names[i_cmds]
 * @details there is one file for each command
 */
static void	redirects_stderr(t_data *d, int i_cmds)
{
	int	err_fd;

	err_fd = open(d->err_file_names[i_cmds], O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (err_fd == -1)
	{
		msg(d->err_file_names[i_cmds], ": ", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	if (dup2(err_fd, STDERR_FILENO) == -1)
	{
		close(err_fd);
		msg("dup2", ": ", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	close(err_fd);
}

/**
 * @brief set the command to execute and its path
 * @example set_cmd(d, "ls -l") => d->cmd = ["ls", "-l", NULL]
 * @details if str_cmd is "", d->cmd is set to ["", NULL]
 */
static void	set_cmd(t_data *d, char *str_cmd)
{
	if (ft_strlen(str_cmd) == 0)
		d->cmd = empty_split();
	else
		d->cmd = ft_split(str_cmd, " ");
	if (!d->cmd)
	{
		msg("ft_split: ", strerror(errno), "", STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	d->cmd_path = get_cmd_path(d, d->cmd[0]);
	if (!d->cmd_path)
	{
		exit_process(127, d);
	}
}

static void	set_curr_in_out(int i_cmds, t_data *d)
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

static void	exec_cmd(t_data *d, char **env)
{
	if (execve(d->cmd_path, d->cmd, env) == -1)
	{
		msg(strerror(errno), ": ", d->cmd[0], STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
}

void	process_child(t_data *d, char **av, char **env, int i_cmds)
{
	redirects_stderr(d, i_cmds);
	set_curr_in_out(i_cmds, d);
	set_cmd(d, av[2 + d->is_here_doc + i_cmds]);
	close_fds_and_pipes(d);
	exec_cmd(d, env);
}
