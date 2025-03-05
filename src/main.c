/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/05 10:49:30 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex infile "ls -l" "wc -l" outfile

char	*get_cmd_path(t_data *d, char *cmd)
{
	char	*curr_path;
	int		i;

	if (cmd && ft_strlen(cmd) > 0 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (d->paths[++i])
	{
		curr_path = ft_strjoin(d->paths[i], cmd);
		if (access(curr_path, X_OK) != -1)
		{
			free(cmd);
			return (curr_path);
		}
		free(curr_path);
	}
	msg("command not found", cmd + 1, STDERR_FILENO);
	free(cmd);
	return (NULL);
}

static void	redirect(int input, int output, t_data *d)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		exit_error(EXIT_FAILURE, d);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		exit_error(EXIT_FAILURE, d);
	}
}

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
}

void	exec_cmd(t_data *d, char **env)
{
	d->cmd_path = get_cmd_path(d, d->cmd[0]);
	if (!d->cmd_path)
	{
		exit_error(STDERR_FILENO, d);
	}
	redirect(d->curr_input, d->curr_output, d);
	close_fds(d);
	if (execve(d->cmd_path, d->cmd, env) == -1)
	{
		msg(strerror(errno), d->cmd[0], STDERR_FILENO);
		exit_error(EXIT_FAILURE, d);
	}
}

void	start_children(t_data *d, char **av, char **env)
{
	int	i_pids;

	i_pids = -1;
	while (++i_pids < d->nb_cmds)
	{
		secure_fork(&d->pids[i_pids], d);
		if (!d->pids[i_pids])
		{
			if (i_pids == 0)
				d->curr_input = d->fds.in;
			else
				d->curr_input = d->pipe[0];
			if (i_pids == d->nb_cmds - 1)
				d->curr_output = d->fds.out;
			else
				d->curr_output = d->pipe[1];
			set_cmd(d, av[i_pids + 2]);
			exec_cmd(d, env);
		}
	}
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

int	main(int ac, char **av, char **env)
{
	t_data	d;
	int		status;

	if (ac != 5)
	{
		msg("Usage: ./pipex infile cmd1 cmd2 outfile", "", STDERR_FILENO);
		return (1);
	}
	init_data(&d, av, ac, env);
	start_children(&d, av, env);
	close_fds(&d);
	status = wait_children(&d);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	free_str_tab(d.paths);
	return (status);
}
