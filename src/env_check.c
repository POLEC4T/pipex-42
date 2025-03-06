/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:43:43 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/05 11:44:18 by mniemaz          ###   ########.fr       */
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
