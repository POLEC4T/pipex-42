/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miloniemaz <mniemaz@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/01 04:29:39 by miloniemaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex infile "ls -l" "wc -l" outfile

char	*get_cmd_path(t_data *d, char *cmd)
{
	char	*curr_path;
	int		i;

	if (access(cmd, X_OK) != -1)
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (d->paths[i])
	{
		curr_path = ft_strjoin(d->paths[i], cmd);
		if (access(curr_path, X_OK) != -1)
		{
			free(cmd);
			return (curr_path);
		}
		i++;
	}
	msg("command not found", cmd + 1, STDERR_FILENO);
	free(cmd);
	return (NULL);
}

static void	redirect(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		msg("Error dup2", strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		msg("Error dup2", strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void close_fds(t_data *d)
{
	close(d->fds.in);
	close(d->fds.out);
	close(d->pipe[0]);
	close(d->pipe[1]);
}
void prep_exec_cmd(t_data *d, char *str_cmd, int curr_input, int curr_output)
{
	d->cmd = ft_split(str_cmd, " ");
	if (!d->cmd)
	{
		msg("Error split", strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	d->curr_input = curr_input;
	d->curr_output = curr_output;
}

void	exec_cmd(t_data *d, char **env)
{
	d->cmd_path = get_cmd_path(d, d->cmd[0]);
	if (!d->cmd_path)
	{
		free_str_tab(d->cmd);
		free(d->cmd_path);
		close_fds(d);
		exit(EXIT_FAILURE);
	}
	redirect(d->curr_input, d->curr_output);
	close_fds(d);
	if (execve(d->cmd_path, d->cmd, env) == -1)
	{
		msg("Error execve", strerror(errno), STDERR_FILENO);
		free_str_tab(d->cmd);
		free(d->cmd_path);
		exit(EXIT_FAILURE);
	}
}


int	main(int ac, char **av, char **env)
{
	t_data	d;

	if (ac != 5)
	{
		msg("Usage: ./pipex infile cmd1 cmd2 outfile", "", STDERR_FILENO);
		return (1);
	}
	init_data(&d, av[1], av[4], env);
	secure_fork(&d.pids[0]);
	if (!d.pids[0])
	{
		prep_exec_cmd(&d, av[2], d.fds.in, d.pipe[1]);
		exec_cmd(&d, env);
		return (1);
	}
	secure_fork(&d.pids[1]);
	if (!d.pids[1])
	{
		// waitpid(d.pids[0], NULL, -1);
		prep_exec_cmd(&d, av[3], d.pipe[0], d.fds.out);
		exec_cmd(&d, env);
		return (1);
	}
	close_fds(&d);
	int status;
	waitpid(d.pids[0], &status, 0);
	waitpid(d.pids[1], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
