/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:43:43 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/13 11:34:08 by mniemaz          ###   ########.fr       */
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
				msg("ft_split", ": ", strerror(errno), STDERR_FILENO);
				return (NULL);
			}
			return (res);
		}
		i++;
	}
	msg("Error", ": ", "PATH not found", STDERR_FILENO);
	return (NULL);
}

static char	*safe_ft_strjoin(t_data *d, char *s1, char *s2, char *to_free)
{
	char		*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		if (to_free)
			free(to_free);
		msg("ft_strjoin", ": ", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	return (res);
}

char	*get_cmd_path(t_data *d, char *cmd)
{
	char	*curr_path;
	int		i;

	if (cmd && ft_strlen(cmd) > 0 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd = safe_ft_strjoin(d, "/", cmd, NULL);
	i = -1;
	while (d->paths[++i])
	{
		curr_path = safe_ft_strjoin(d, d->paths[i], cmd, cmd);
		if (access(curr_path, X_OK) != -1)
		{
			free(cmd);
			return (curr_path);
		}
		free(curr_path);
	}
	msg("command not found", ": ", cmd + 1, STDERR_FILENO);
	free(cmd);
	return (NULL);
}
