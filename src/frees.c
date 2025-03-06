/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 12:53:44 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	exit_process(int error_status, t_data *data)
{
	int	i;

	if (data)
	{
		close_fds_and_pipes(data);
		if (data->cmd != NULL)
			free_str_tab(data->cmd);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		if (data->paths != NULL)
			free_str_tab(data->paths);
		if (data->pids != NULL)
			free(data->pids);
		if (data->pipes != NULL)
		{
			i = -1;
			while (data->pipes[++i])
				free(data->pipes[i]);
			free(data->pipes);
		}
	}
	exit(error_status);
}
