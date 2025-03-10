/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 13:00:30 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	exit_process(int error_status, t_data *data)
{
	if (data)
	{
		close_fds_and_pipes(data);
		if (data->cmd != NULL)
			free_tab((void **)data->cmd);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		if (data->paths != NULL)
			free_tab((void **)data->paths);
		if (data->pids != NULL)
			free(data->pids);
		if (data->pipes != NULL)
			free_tab((void **)data->pipes);
		if (data->is_here_doc)
			unlink(HEREDOC_FILENAME);
		if (data->err_file_names != NULL)
			free_tab((void **)data->err_file_names);
	}
	exit(error_status);
}
