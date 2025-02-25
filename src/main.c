/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/02/25 17:41:01 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex infile "ls -l" "wc -l" outfile

char	**get_paths(char **env)
{
	char	**res;
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
		{
			res = ft_split(env[i] + 5, ":");
			if (!res)
				return (NULL);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*get_accessible_path(char **env, char *cmd)
{
	char	**paths;
	char	*curr_path;
	int		i;

	paths = get_paths(env);
	if (!paths)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		curr_path = ft_strjoin(paths[i], cmd);
		if (access(curr_path, X_OK) != -1)
		{
			free(cmd);
			return (curr_path);
		}
		i++;
	}
	free(cmd);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	int		pid;
	int		fd[2];
	char	**cmd_1;
	char	**cmd_2;
	char	*cmd_path;
	int		infile_fd;
	int		outfile_fd;

	if (ac != 5)
		return (0);
	(void)ac;
	(void)av;
	pipe(fd);
	pid = fork();
	infile_fd = open(av[1], O_RDONLY);
	outfile_fd = open(av[4], O_WRONLY | O_CREAT);
	if (!pid)
	{
		close(fd[0]);
		cmd_1 = ft_split(av[2], " ");
		if (!cmd_1)
		{
			close(fd[1]);
			exit(1);
		}
		cmd_path = get_accessible_path(env, cmd_1[0]);
		if (!cmd_path)
		{
			free_str_tab(cmd_1);
			close(fd[1]);
			exit(1);
		}
		dup2(infile_fd, STDIN_FILENO); // stdin devient infile
		dup2(fd[1], STDOUT_FILENO);    // stdout devient fd write
		close(fd[1]);
		execve(cmd_path, cmd_1, env);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, -1);
		cmd_2 = ft_split(av[3], " ");
		if (!cmd_2)
		{
			close(fd[0]);
			exit(1);
		}
		cmd_path = get_accessible_path(env, cmd_2[0]);
		if (!cmd_path)
		{
			free_str_tab(cmd_2);
			close(fd[0]);
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);       // stdin devient fd read
		dup2(outfile_fd, STDOUT_FILENO); // stdout devient outfile
		close(fd[0]);
		execve(cmd_path, cmd_2, env);
	}
	return (0);
}
